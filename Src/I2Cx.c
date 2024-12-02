/*
 * I2Cx.c
 *
 *  Created on: Jul 29, 2024
 *      Author: joshu
 */

#include "stm32l4xx.h"
#include <stdint.h>
#include<stdbool.h>



void I2C_delay(uint32_t T)
{
	while(T--);
}


void RCC_En_I2C(I2C_TypeDef *port){
	if(port == I2C1){
		SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_I2C1EN);
	}
	if(port == I2C3){
		SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_I2C3EN);
	}
}




void I2C_Init(I2C_TypeDef *Port){
	CLEAR_BIT(Port->CR1,I2C_CR1_PE);
	//CONFIGURA I2C EN Fast-mode (FM)
	SET_BIT(Port->TIMINGR,(1 << (28))); //Configura el preescalador PRESC[3:0]
	SET_BIT(Port->TIMINGR,(0x9 << (0))); //Configura el SCLL del registro TIMINGR
	SET_BIT(Port->TIMINGR,(0x3 << (8))); //Configura el SCLH del registro TIMINGR
	SET_BIT(Port->TIMINGR,(0x2 << (16))); //Configura el SDADEL del registro TIMINGR
	SET_BIT(Port->TIMINGR,(0x3 << (20))); //Configura el SCLDEL del registro TIMINGR
	//SET_BIT(Port->I2C_CR1,I2C_CR1_TXDMAEN); //Habilitar modo DMA para las transmisiones
	//SET_BIT(Port->I2C_CR1,I2C_CR1_RXDMAEN); //Habilitar modo DMA para las transmisiones
	SET_BIT(Port->CR1,I2C_CR1_ANFOFF); //Habilitar modo DMA para las transmisiones
    SET_BIT(Port->CR1,I2C_CR1_PE); //Habilita bit PE del registro CR1
}

void I2C_Tx_1Byte (I2C_TypeDef *Port, uint8_t Adress, uint8_t Byte_0){
	int timeout = 1000;  // Valor de timeout ajustable
	CLEAR_BIT(Port->CR2,I2C_CR2_ADD10); //Limpiar el bit ADD10 para utilizar direccion de esclavo de 7 bits
	CLEAR_BIT(Port->CR2,0xFF); // Carga la dirección del esclavo
	SET_BIT(Port->CR2,(Adress << (1))); // Carga la dirección del esclavo
	CLEAR_BIT(Port->CR2, I2C_CR2_RD_WRN); //Escritura
	SET_BIT(Port->CR2,(0x01 << (16)));  //Numero de BYTES
	CLEAR_BIT(Port->CR2, I2C_CR2_AUTOEND);  //Habilitar condición de stop automatica
	SET_BIT(Port->CR2, I2C_CR2_START); //Comienza transmisión
	while((Port->ISR & I2C_ISR_TXIS) == 0){
	    if(--timeout == 0) {
	        // Gestionar el error: puede reiniciar el bus o informar un error
	        break;
	    }
	}
	Port->TXDR = Byte_0;
	I2C_delay(50);
	//SET_BIT(Port->I2C_CR2, I2C_CR2_STOP); //Condicion de stop
	SET_BIT(Port->ICR, I2C_ICR_STOPCF); //Limpia bandaera de deteccion de condicion de stop
	CLEAR_BIT(Port->CR1,I2C_CR1_PE); //Deshabilita bit PE del registro CR1 para desactivar el periferico
	SET_BIT(Port->CR1,I2C_CR1_PE); //Habilita bit PE del registro CR1 para activar el periferico

}

int16_t I2C_Rx_1Byte (I2C_TypeDef *Port, uint8_t Adress){
	int timeout = 1000;  // Valor de timeout ajustable
	int16_t ACEL_XOUT;
	uint8_t ACCEL_XOUT_H;
	uint8_t ACCEL_XOUT_L;
	CLEAR_BIT(Port->CR2,I2C_CR2_ADD10); //Limpiar el bit ADD10 para utilizar direccion de esclavo de 7 bits
	SET_BIT(Port->CR2,I2C_CR2_HEAD10R); //Limpiar el bit ADD10 para utilizar direccion de esclavo de 7 bits
	CLEAR_BIT(Port->CR2,0xFF); // Carga la dirección del esclavo
	SET_BIT(Port->CR2,(Adress << (1))); // Carga la dirección del esclavo
	SET_BIT(Port->CR2, I2C_CR2_RD_WRN); //lectura
	SET_BIT(Port->CR2,(0x02 << (16)));  //Numero de BYTES
	CLEAR_BIT(Port->CR2,I2C_CR2_AUTOEND);  //Habilitar condición de stop automatica
	SET_BIT(Port->CR2, I2C_CR2_START); //Comienza transmisión

	while((Port->ISR & I2C_ISR_RXNE) == 0){
	    if(--timeout == 0) {
	        // Gestionar el error: puede reiniciar el bus o informar un error
	        break;
	    }
	}
	timeout = 1000;
	ACCEL_XOUT_H=Port->RXDR;  //Leo valor que envia MPU
	I2C_delay(100);
	while((Port->ISR & I2C_ISR_RXNE) == 0){
	    if(--timeout == 0) {
	        // Gestionar el error: puede reiniciar el bus o informar un error
	        break;
	    }
	}
	timeout = 1000;
	ACCEL_XOUT_L=Port->RXDR;  //Leo valor que envia MPU
	I2C_delay(100);
	SET_BIT(Port->CR2, I2C_CR2_STOP); //Condicion de stop
	SET_BIT(Port->ICR, I2C_ICR_STOPCF); //Limpia bandaera de deteccion de condicion de stop
	SET_BIT(Port->ICR, I2C_ICR_NACKCF); //Limpia bandaera de deteccion de condicion de stop
	CLEAR_BIT(Port->CR1,I2C_CR1_PE); //Deshabilita bit PE del registro CR1 para desactivar el periferico
	SET_BIT(Port->CR1,I2C_CR1_PE); //Habilita bit PE del registro CR1 para activar el periferico
	ACEL_XOUT = ACCEL_XOUT_H <<8 |ACCEL_XOUT_L;
	return ACEL_XOUT;
}

void I2C_Tx_2Bytes (I2C_TypeDef *Port, uint8_t Adress, uint8_t Byte_0, uint8_t Byte_1){
CLEAR_BIT(Port->CR2,I2C_CR2_ADD10); //Limpiar el bit ADD10 para utilizar direccion de esclavo de 7 bits
CLEAR_BIT(Port->CR2,0xFF); // Carga la dirección del esclavo
SET_BIT(Port->CR2,(Adress << (1))); // Carga la dirección del esclavo
CLEAR_BIT(Port->CR2, I2C_CR2_RD_WRN); //Escritura
SET_BIT(Port->CR2,(0x02 << (16)));  //Numero de BYTES
CLEAR_BIT(Port->CR2, I2C_CR2_AUTOEND);  //Habilitar condición de stop automatica
SET_BIT(Port->CR2, I2C_CR2_START); //Comienza transmisión
while((Port->ISR&I2C_ISR_TXIS)==0){};
Port->TXDR = Byte_0;
I2C_delay(100);
while((Port->ISR&I2C_ISR_TXIS)==0){};
Port->TXDR = Byte_1;
I2C_delay(100);
SET_BIT(Port->CR2, I2C_CR2_STOP); //Condicion de stop
SET_BIT(Port->ICR, I2C_ICR_STOPCF); //Limpia bandaera de deteccion de condicion de stop
CLEAR_BIT(Port->CR1,I2C_CR1_PE); //Deshabilita bit PE del registro CR1 para desactivar el periferico
SET_BIT(Port->CR1,I2C_CR1_PE); //Habilita bit PE del registro CR1 para activar el periferico
}



void I2C_Tx_3Bytes (I2C_TypeDef *Port, uint8_t Adress, uint8_t Byte_0, uint8_t Byte_1, uint8_t Byte_2){
CLEAR_BIT(Port->CR2,I2C_CR2_ADD10); //Limpiar el bit ADD10 para utilizar direccion de esclavo de 7 bits
SET_BIT(Port->CR2,(Adress << (1))); // Carga la dirección del esclavo
CLEAR_BIT(Port->CR2, I2C_CR2_RD_WRN); //Escritura
SET_BIT(Port->CR2,(0x03 << (16)));  //Numero de BYTES
CLEAR_BIT(Port->CR2, I2C_CR2_AUTOEND);  //Habilitar condición de stop automatica
SET_BIT(Port->CR2, I2C_CR2_START); //Comienza transmisión
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_0); //Comienza transmisión
I2C_delay(100);
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_1); //Comienza transmisión
I2C_delay(100);
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_2); //Comienza transmisión
I2C_delay(100);
SET_BIT(Port->CR2, I2C_CR2_STOP); //Condicion de stop
SET_BIT(Port->ICR, I2C_ICR_STOPCF); //Limpia bandaera de deteccion de condicion de stop
CLEAR_BIT(Port->CR1,I2C_CR1_PE); //Deshabilita bit PE del registro CR1 para desactivar el periferico
SET_BIT(Port->CR1,I2C_CR1_PE); //Habilita bit PE del registro CR1 para activar el periferico
}

void I2C_Tx_4Bytes (I2C_TypeDef *Port, uint8_t Adress, uint8_t Byte_0, uint8_t Byte_1, uint8_t Byte_2, uint8_t Byte_3){
CLEAR_BIT(Port->CR2,I2C_CR2_ADD10); //Limpiar el bit ADD10 para utilizar direccion de esclavo de 7 bits
SET_BIT(Port->CR2,(Adress << (1))); // Carga la dirección del esclavo
CLEAR_BIT(Port->CR2, I2C_CR2_RD_WRN); //Escritura
SET_BIT(Port->CR2,(0x04 << (16)));  //Numero de BYTES
CLEAR_BIT(Port->CR2, I2C_CR2_AUTOEND);  //Habilitar condición de stop automatica
SET_BIT(Port->CR2, I2C_CR2_START); //Comienza transmisión
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_0); //Comienza transmisión
I2C_delay(100);
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_1); //Comienza transmisión
I2C_delay(100);
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_2); //Comienza transmisión
I2C_delay(100);
while((Port->ISR&I2C_ISR_TXIS)==0){};
SET_BIT(Port->TXDR, Byte_3); //Comienza transmisión
I2C_delay(100);
SET_BIT(Port->CR2, I2C_CR2_STOP); //Condicion de stop
SET_BIT(Port->ICR, I2C_ICR_STOPCF); //Limpia bandaera de deteccion de condicion de stop
CLEAR_BIT(Port->CR1,I2C_CR1_PE); //Deshabilita bit PE del registro CR1 para desactivar el periferico
SET_BIT(Port->CR1,I2C_CR1_PE); //Habilita bit PE del registro CR1 para activar el periferico
}
