/*
 * CANx.h
 *
 *  Created on: Oct 23, 2024
 *      Author: joshu
 */

#ifndef CANX_H_
#define CANX_H_
#include "stm32l4xx.h"
#include <stdbool.h>
//Simplified Definitions for filters
#define Mask_mode				        (0U)
#define List_mode	         			(1U)
#define Dual_16bit				        (0U)
#define Single_32bit	      			(1U)
#define Fifo_0				            (0U)
#define Fifo_1	         	     		(1U)

#define    CAN_LEC_NO_ERROR 	 0x0       // No Error
#define    CAN_LEC_STUFF_ERROR 	 0x1    // Error de bit dominante
#define     CAN_LEC_FORM_ERROR 	 0x2     // Error de bit recesivo
#define    CAN_LEC_ACK_ERROR 	 0x3      // Error de paridad
#define    CAN_LEC_CRC_ERROR 	 0x4      // Error de CRC
#define    CAN_LEC_BIT_ERROR 	 0x5      // Error de formato
#define    CAN_LEC_OTHER_ERROR 	 0x6    // Error de reconocimiento
#define    CAN_LEC_RESERVED 	 0x7        // Reservado



void RCC_En_CANx(CAN_TypeDef *port);
void CANx_Init(CAN_TypeDef *port);
void CANx_BitTiming_500Kz(CAN_TypeDef *port);
void CAN_FilterInit (CAN_TypeDef *port, bool Mode, bool Scale, bool Fifo, uint8_t BitIndex); //CAN1, Mode , Scale, FIFO, Localidad
void CAN_SetFilterValue(CAN_TypeDef *port, uint32_t ID, uint32_t Mask, uint8_t BitIndex);  //CAN1, ID , MSK, Localidad
void CAN_MailboxConfig(CAN_TypeDef *port, bool ExtendedID, uint32_t ID, bool Remote, uint8_t mailboxIndex); //CAN1, ExtededID, IDE, RTR, Localidad
void CAN_SendData(CAN_TypeDef *port, uint8_t DLC, uint64_t data, uint8_t mailboxIndex); //CAN1, DLC , DATA, Localidad
void CAN_RequestTransmission(CAN_TypeDef *port, uint8_t mailboxIndex);
void CANx_EnFIFO0Ints(CAN_TypeDef * port);
void CANx_EnFIFO1Ints(CAN_TypeDef * port);
void CAN1_Rx0_FIFOx(CAN_TypeDef *port, CAN_FIFOMailBox_TypeDef *fifo);
void CAN1_Rx1_FIFOx(CAN_TypeDef *port, CAN_FIFOMailBox_TypeDef *fifo);

uint8_t CANx_GetLEC(CAN_TypeDef * port);
#endif /* CANX_H_ */
