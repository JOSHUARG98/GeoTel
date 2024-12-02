/*
 * UARTx.c
 *
 *  Created on: Nov 7, 2024
 *      Author: joshu
 */


#include <stdint.h>
#include<stdbool.h>
#include "stm32l4xx.h"
#include "USARTx.h"
#include "NVIC.h"

char *A;
char buffer[255];

void RCC_En_USARTx(USART_TypeDef *port){
	if(port == USART2){
		SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_USART2EN);
	}
	if(port == USART3){
		SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_USART3EN);
	}
	if(port == UART4){
		SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_UART4EN );
	}
}


void USARTx_CONF(USART_TypeDef *USARTx_, uint16_t USARTx_BRR_MSI, uint8_t USARTx_Pos_IRQn, uint8_t USARTx_Prio_IRQn){

	A = buffer;
	CLEAR_BIT(USARTx_->CR1, 0xFF);	//LIMPIAMOS Y DESHABILITAMOS CONFIGURACIÓN DE USART3
	SET_BIT(USARTx_->BRR, USARTx_BRR_MSI);	//SE CONFIGURA UN BAUD RATE

	SET_BIT(USARTx_->CR1, 0x0C);	//HABILITAMOS TX Y RX
	/*#####CONFIGURACIÓN PARA INDICADORES DE BANDERAS EN USART3 CON CR1#####*/
	SET_BIT(USARTx_->CR1, 0x020);	//ENMASCARAMOS BANDERA INDICADORA EN LA RECEPCIÓN DE DATOS, BIT 5

	/*#####ÚLTIMA CONFIGURACIÓN PARA USART3#####*/
	SET_BIT(USARTx_->CR1, 0x01);	//HABILITAMOS LA CONEXIÓN EN USART3

	switch(USARTx_Pos_IRQn){
/*	case USART1_IRQn:
		NVIC_SetCFGR(USART1_IRQn, USARTx_Prio_IRQn);//ACTIVA INTERRUPCIÓN USART1
		break;
	case USART2_IRQn:
		NVIC_SetCFGR(USART2_IRQn, USARTx_Prio_IRQn);//ACTIVA INTERRUPCIÓN USART2
		break;*/
	case USART3_IRQn:
		NVIC_Enable(USART3_IRQn, USARTx_Prio_IRQn);//ACTIVA INTERRUPCIÓN USART3
		break;
	case UART4_IRQn:
		NVIC_Enable(UART4_IRQn, USARTx_Prio_IRQn);//ACTIVA INTERRUPCIÓN UART4
		break;
	default:
		break;
	}
}

// Función de interrupción por UART
void USART3_IRQHandler(void){
	//CADA QUE SE ACTIVE LA BANDERA DE INTERRUPCIÓN DE LA RECEPCIÓN,SE VA A HACER LO SIGUIENTE:
	*A++ = USART3->RDR;
	//LIMPIAMOS BANDERA PARA SALIR DE INTERRUPCIÓN
	CLEAR_BIT(USART3->RQR, 0x08);
	//UART4->TDR = *A++;
}

// Función que envía un dato por UART
void sendStringUARTx(USART_TypeDef *USARTx_, register const char *msg){

    while(*msg)
    {
    	USARTx_->TDR = *msg++;
    	while(!(USARTx_->ISR & 0x080));
    }
}
// Función que envía una cadena por UART

// Función que envía un solo byte (8 bits) por UART
void sendByteUARTx(USART_TypeDef *USARTx_, uint8_t data) {
    // Cargar el byte en el registro de transmisión (TDR)
    USARTx_->TDR = data;

    // Esperar a que la transmisión esté completa (espera hasta que el bit TXE esté listo)
    while (!(USARTx_->ISR & 0x080));
}
