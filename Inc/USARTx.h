/*
 * UARTx.h
 *
 *  Created on: Nov 7, 2024
 *      Author: joshu
 */

#ifndef UARTX_H_
#define UARTX_H_
#include "stm32l4xx.h"

#define USART1_CLK_Init	1
#define USART2_CLK_Init	2
#define USART3_CLK_Init	3
#define UART4_CLK_Init	4

/*PUERTOS Y PINES (orden en Tx y Rx):
 * USART1 PUERTOS Y PINES:
 * PA, pines 9 y 10. PB, pines 6 y 7
 * USART2 PUERTOS Y PINES:
 * PA, pines 2 y 3. PD, pines 5 y 6
 * USART3 PUERTOS Y PINES:
 * PB, pines 10 y 11. PC, pines 4 y 5. PC, pines 10 y 11. PD, pines 8 y 9
 * UART4 PUERTOS Y PINES:
 * PC, pines 10 y 11
 * */

#define GPIO_AFR_AFSEL_USART1_2_3	0x7 //AFL = 0x7
#define GPIO_AFR_AFSEL_UART4	0X8 	//AFH = 0x1 ó 0x8

#define USARTx_BRR_MSI_100kHz	0x000A
#define USARTx_BRR_MSI_200kHz	0x0014
#define USARTx_BRR_MSI_400KHz	0x0029
#define USARTx_BRR_MSI_800KHz	0x0053
#define USARTx_BRR_MSI_1MHz	0x0068
#define USARTx_BRR_MSI_2MHz	0x00D0
#define USARTx_BRR_MSI_4MHz	0x01A0
#define USARTx_BRR_MSI_8MHz	0x0341
#define USARTx_BRR_MSI_16MHz	0x0682
#define USARTx_BRR_MSI_24MHz	0x09C4
#define USARTx_BRR_MSI_32MHz	0x0D05
#define USARTx_BRR_MSI_48MHz	0x1388

// Función de interrupción por UART

// Función que inicializa UART
void RCC_En_USARTx(USART_TypeDef *port);
void USARTx_CONF(USART_TypeDef *USARTx_, uint16_t USARTX_BRR_MSI, uint8_t USARTx_NUM_IRQ, uint8_t USARTx_Prio_IRQ);

// Función que envía un dato por UART
void sendStringUARTx(USART_TypeDef *USARTx_, register const char *msg);
// Función que envía una cadena por UART


void sendByteUARTx(USART_TypeDef *USARTx_, uint8_t data);


#endif /* UARTX_H_ */
