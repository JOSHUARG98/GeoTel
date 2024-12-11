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

#define BUFFER_SIZE 250 // Tamaño máximo del buffer

volatile char rxBuffer[BUFFER_SIZE]; // Arreglo para guardar los datos recibidos
volatile uint16_t writeIndex = 0;      // Índice para guardar el próximo dato recibido

char *A;
char buffer[255];
char north[20];
char west[20];

int ind=0;
int Q=0;
int candado=0;
int limsup=0;
int liminf=0;



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
	/*
	//CADA QUE SE ACTIVE LA BANDERA DE INTERRUPCIÓN DE LA RECEPCIÓN,SE VA A HACER LO SIGUIENTE:
	*A++ = USART3->RDR;
	//LIMPIAMOS BANDERA PARA SALIR DE INTERRUPCIÓN
	CLEAR_BIT(USART3->RQR, 0x08);
	//UART4->TDR = *A++;
	 * */

	    // Leer el dato recibido desde el registro RDR
	    uint8_t receivedData = USART3->RDR;

	    // Guardar el dato en el arreglo
	    if (writeIndex < BUFFER_SIZE) {
	        rxBuffer[writeIndex++] = receivedData;
	    } else {
	        // Si el buffer está lleno, limpiar el buffer
	        for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
	            rxBuffer[i] = 0; // Limpia cada posición del buffer
	        }

	        // Reiniciar el índice y guardar el dato recibido en la primera posición
	        writeIndex = 0;
	       // rxBuffer[writeIndex++] = receivedData;
	    }

	    // Limpiar la bandera para salir de la interrupción
	    CLEAR_BIT(USART3->RQR, 0x08);

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

// Función que envía un mensaje por UART según el caso seleccionado
void GPS_PET(uint8_t caseN) {
    switch(caseN) {
        case 1:
        	writeIndex = 0;
	        delay(1000000);
	        sendStringUARTx(USART3, "AT+QGPSLOC? \r\n\0");
	        for (uint16_t j = 100; j < 200; j++) {
	            rxBuffer[j] = 0; // Limpia cada posición del buffer
	        }
	        delay(1000000);
	        ind=0;
	        for(Q=36;Q<=45;Q++){
	            north[ind]=rxBuffer[Q];
	            ind++;
	        }
	        ind=0;
            for(Q=47;Q<=56;Q++){
                west[ind]=rxBuffer[Q];
                //printf("%c , %c",west[Q-47], rxBuffer[Q]);
                ind++;
            }

            break;
        case 2:
        	writeIndex = 100;
	        delay(1000000);
	        //sendStringUARTx(USART3, "AT+QGPSLOC? \r\n\0");
	        for (uint16_t k = 0; k < 100; k++) {
	            rxBuffer[k] = 0; // Limpia cada posición del buffer
	        }

	        break;
        default:
            break;
    }
}


void busqueda(){
     Q=0;
     candado=0;
     limsup=0;
     liminf=0;
     ind=0;

    //BUSQUEDA DE W
     /*
    while(candado==0){
        if(rxBuffer[limsup]==87 || limsup==100){
            candado=1;
            break;
        }
        limsup++;
    }

    candado=0;

    //BUSQUEDA DE ,
    if(limsup!=100){
        liminf=limsup;
        while(candado==0){
            if(rxBuffer[liminf]==',' || liminf==0){
                candado=1;
                break;
            }//FIN IF
            liminf--;

        }//FIN WHILE
    liminf+=1;
    }//FIN IF
    */

    //CONDICION DE QUE NO ESTA LIMPIO EL ARREGLO
    //if(liminf!=0 || limsup!=100){
        //GUARDAR VALORES WEST
            for(Q=47;Q<=56;Q++){
                west[0]=rxBuffer[47];
                //printf("%c , %c",west[Q-47], rxBuffer[Q]);
                liminf++;
            }


    //NUEVO LIMITE SUPERIOR
            /*
        limsup=liminf-2;
        liminf=limsup-1;
        candado=0;

        //BUSQUEDA LIMITE INFERIOR
        while(candado==0){
            if(rxBuffer[liminf]==','){
                candado=1;
                break;
            }
            liminf--;
        }
        liminf+=1;

        //GUARDAR VALORES NORT
         *
         */
        ind=0;
        for(Q=36;Q<=45;Q++){
            north[ind]=(char)rxBuffer[Q];
            ind++;
        }

    //}//FIN IF
}
