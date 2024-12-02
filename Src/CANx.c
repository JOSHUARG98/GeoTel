/*
 * CANx.c
 *
 *  Created on: Oct 23, 2024
 *      Author: joshu
 */

#include "stm32l4xx.h"
#include <stdint.h>
#include<stdbool.h>

#include "CANx.h"

void RCC_En_CANx(CAN_TypeDef *port){
		if(port == CAN1){
			SET_BIT(RCC->APB1ENR1,RCC_APB1ENR1_CAN1EN);
		}
}

void CANx_Init(CAN_TypeDef *port){
	SET_BIT(port->MCR, CAN_MCR_RESET);//Reset FORZAMOS a entrar a modo sleep
	while(port->MCR & CAN_MCR_RESET) {}; //Esperamos a que el bit RESET se limpie
	SET_BIT(port->MCR, CAN_MCR_INRQ);//Solicitamos entrar a modo inicializacion
	while((port->MSR & CAN_MSR_INAK)==0){};//Esperamos a que el bit INAK sea set
	CLEAR_BIT(port->MCR, CAN_MCR_SLEEP);//Solicitamos Apagagar modo sleep
	while(port->MSR & CAN_MSR_SLAK) {}; //Esperamos a que el bit SLAK se limpie ****ENTRAMOS A MODO INICIALIZACION TRAS ackmowledge de sleep off

	CLEAR_BIT(port->MCR, CAN_MCR_TXFP);// Inicializas el arbitraje, es decir la prioridad de cada mensaje es por identificador
	CLEAR_BIT(port->MCR, CAN_MCR_RFLM);//La FIFO no se bloquea al haber estado de OVERRUN
	SET_BIT(port->MCR, CAN_MCR_NART);//Activamos la retransmisión automática.
	//Modificar, si no se desea retransmitir NART=1.
	CLEAR_BIT(port->MCR, CAN_MCR_AWUM);//AQUI SALIMOS DE MODO SLEEP POR SOFTWARE, EN UN FUTURO CONSIDERAR CAMBIARLOS A MODO HARDWARE PARA MODOS DE BAJO CONSUMO (CARRO PRENDIDO?)
	CLEAR_BIT(port->MCR, CAN_MCR_ABOM);//SALIDA DE BUSS OFF POR SOFTWARE
	CLEAR_BIT(port->MCR, CAN_MCR_TTCM);//Desactivamos funcion solo disponible para RTOS
	CLEAR_BIT(port->MCR, CAN_MCR_RESET);//
	CLEAR_BIT(port->MCR, CAN_MCR_DBF);//Activa funcionamiento en modo debug
}

void CANx_BitTiming_500Kz (CAN_TypeDef *port){

	//SET_BIT(port->BTR , (CAN_BTR_LBKM)); //Descomentar si se quieren hacer pruebas en modo loopback
	//SET_BIT(port->Register->BTR , (CAN_SILENT));
	CLEAR_BIT(port->BTR , (CAN_BTR_BRP));//limpia  BRP
	CLEAR_BIT(port->BTR , (CAN_BTR_TS1));//limpia TS1
	CLEAR_BIT(port->BTR , (CAN_BTR_TS2));//limpia TS2

	SET_BIT(port->BTR , ((0x1UL)<<CAN_BTR_BRP_Pos));//fija Baud rate
	SET_BIT(port->BTR , ((11U)<<CAN_BTR_TS1_Pos));//configura tS1
	SET_BIT(port->BTR , ((0x2UL)<<CAN_BTR_TS2_Pos));//configura tS2
}


void CAN_FilterInit (CAN_TypeDef *port, bool Mode, bool Scale, bool Fifo, uint8_t BitIndex){
	CLEAR_BIT(port->FA1R, (1 << BitIndex)); //Desactivo el filtro del Bit index
	SET_BIT(port->MSR,CAN_FMR_FINIT);//modo inicialización en los filtros

    // Configuramos el bit correspondiente utilizando BitIndex para configurar modo lista o mascara
    if (Mode) {
    	SET_BIT(port->FM1R, (1 << BitIndex)); // Si Mode es verdadero, establecemos el bit en BitIndex
    } else {
    	CLEAR_BIT(port->FM1R, (1 << BitIndex)); // Si Mode es falso, limpiamos el bit en BitIndex
    }

 // Configuramos el bit correspondiente utilizando BitIndex para configurar la escala
    if (Scale) {
        SET_BIT(port->FS1R, (1 << BitIndex)); // Si Mode es verdadero, establecemos el bit en BitIndex
    } else {
        CLEAR_BIT(port->FS1R, (1 << BitIndex));// Si Mode es falso, limpiamos el bit en BitIndex
    }

    // Configuramos el bit correspondiente utilizando BitIndex para asignar a FIFO0 o FIFO1
     if (Fifo) {
         SET_BIT(port->FFA1R, (1 << BitIndex));// Si Mode es verdadero, establecemos el bit en BitIndex
     } else {
         CLEAR_BIT(port->FFA1R, (1 << BitIndex));// Si Mode es falso, limpiamos el bit en BitIndex FFA1R
     }

     SET_BIT(port->FA1R, (1 << BitIndex)); //Acitva el filtro del Bit index
   //  CLEAR_BIT(port->FMR,CAN_FMR_FINIT);//fin de modo inicialización
}

void CAN_SetFilterValue(CAN_TypeDef *port, uint32_t ID, uint32_t Mask, uint8_t BitIndex){

    SET_BIT(port->FMR, CAN_FMR_FINIT); // Activamos el modo de inicialización de filtros
    CLEAR_BIT(port->FA1R, (1 << BitIndex));// Desactivamos temporalmente el filtro correspondiente

    // Configuramos los registros de filtro y máscara

    port->sFilterRegister[BitIndex].FR1 &= ~(0xFFFFFFFF);  // Limpia bits antes de escribir
    port->sFilterRegister[BitIndex].FR2 &= ~(0xFFFFFFFF);  // Limpia bits antes de escribir

    port->sFilterRegister[BitIndex].FR1 = (ID & 0x7FF) << 21;  // Ajustar ID en bits 21 al 31
    port->sFilterRegister[BitIndex].FR2 = (Mask & 0x7FF) << 21; // Ajustar Mask en bits 21 al 31

    // Reactivamos el filtro y salimos del modo de inicialización
    SET_BIT(port->FA1R, (1 << BitIndex));
  //  CLEAR_BIT(port->FMR, CAN_FMR_FINIT);
}

void CAN_MailboxConfig(CAN_TypeDef *port, bool ExtendedID, uint32_t ID, bool Remote, uint8_t mailboxIndex){

	port->sTxMailBox[mailboxIndex].TIR &= ~(0xFFFFFFFF); //Limplia el registro TIR del milebox correspondiente

    if (mailboxIndex > 2) {//Si se usa la funcion con un index superior a 2 sale de la funcion ya que solo tenemos 3 mailbox
        return;
    }
    // Configuramos el bit correspondiente utilizando isExtendedID para configurar IDE y cargar el identificador
    if (ExtendedID) {
        port->sTxMailBox[mailboxIndex].TIR = (ID << 3) | (1 << 2); // ID extendida: ID en bits 31:3, IDE en bit 2
    } else {
        port->sTxMailBox[mailboxIndex].TIR = (ID << 21); // ID estándar: ID en bits 31:21, IDE desactivado
    }

    // Configuramos RTR para indicar si es trama de datos o remota
    if (Remote) {
        SET_BIT(port->sTxMailBox[mailboxIndex].TIR, CAN_TI0R_RTR); // Activa bit RTR para trama remota
    } else {
        CLEAR_BIT(port->sTxMailBox[mailboxIndex].TIR, CAN_TI0R_RTR); // Desactiva bit RTR para trama de datos
    }
}


void CAN_SendData(CAN_TypeDef *port, uint8_t DLC, uint64_t data, uint8_t mailboxIndex) {

	port->sTxMailBox[mailboxIndex].TDTR &= ~(0xFFFFFFFF); //Limpia valores de TDTR
	port->sTxMailBox[mailboxIndex].TDLR &= ~(0xFFFFFFFF); //Limpia valores de TDLR
	port->sTxMailBox[mailboxIndex].TDHR &= ~(0xFFFFFFFF); //Limpia calores de TDHR
    if (mailboxIndex > 2) {
        return;
    }
    port->sTxMailBox[mailboxIndex].TDTR = DLC & 0xF;
    port->sTxMailBox[mailboxIndex].TDLR = data & 0xFFFFFFFF;
    port->sTxMailBox[mailboxIndex].TDHR = (data >> 32) & 0xFFFFFFFF;
}

void CAN_RequestTransmission(CAN_TypeDef *port, uint8_t mailboxIndex) {
    if (mailboxIndex > 2) {
        return; // Verifica que el índice del mailbox esté dentro del rango permitido
    }
    if (mailboxIndex == 0) {
        while ((port->TSR & (1 << CAN_TSR_TME0_Pos)) == 0) {}
    } else if (mailboxIndex == 1) {
        while ((port->TSR & (1 << CAN_TSR_TME1_Pos)) == 0) {}
    } else if (mailboxIndex == 2) {
        while ((port->TSR & (1 << CAN_TSR_TME2_Pos)) == 0) {}
    }
    SET_BIT(port->sTxMailBox[mailboxIndex].TIR, CAN_TI0R_TXRQ); // Activa el bit TXRQ para solicitar la transmisión
}


bool CAN_CheckAndClearFlags(CAN_TypeDef *port, uint8_t mailboxIndex) {
    bool flag = false;
    // Selecciona y verifica las banderas correspondientes al mailboxIndex
    switch(mailboxIndex) {
        case 0:
            while (!(port->TSR & (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_ALST0 | CAN_TSR_TERR0)));
            if ((port->TSR & CAN_TSR_TXOK0) && !(port->TSR & (CAN_TSR_ALST0 | CAN_TSR_TERR0))) {
            	flag = true;
            }
            port->TSR |= CAN_TSR_RQCP0; // Limpia la bandera RQCP0
            break;
        case 1:
            while (!(port->TSR & (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_ALST1 | CAN_TSR_TERR1)));
            if ((port->TSR & CAN_TSR_TXOK1) && !(port->TSR & (CAN_TSR_ALST1 | CAN_TSR_TERR1))) {
            	flag = true;
            }
            port->TSR |= CAN_TSR_RQCP1;// Limpia la bandera RQCP1
            break;

        case 2:
            while (!(port->TSR & (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_ALST2 | CAN_TSR_TERR2)));
            if ((port->TSR & CAN_TSR_TXOK2) && !(port->TSR & (CAN_TSR_ALST2 | CAN_TSR_TERR2))) {
            	flag = true;
            }
            port->TSR |= CAN_TSR_RQCP2; // Limpia la bandera RQCP2
            break;

        default:
            return false; // Índice de mailbox inválido
    }

    return flag;
}


void CANx_EnFIFO1Ints(CAN_TypeDef * port){
	SET_BIT(port->IER, CAN_IER_FMPIE1|CAN_IER_FFIE1|CAN_IER_FOVIE1);
}

void CANx_EnFIFO0Ints(CAN_TypeDef * port){
	SET_BIT(port->IER, CAN_IER_FMPIE0|CAN_IER_FFIE0|CAN_IER_FOVIE0);
}



uint8_t CANx_GetLEC(CAN_TypeDef * port){
	uint8_t lec = (port->ESR & CAN_ESR_LEC_Msk) >> CAN_ESR_LEC_Pos; // Leer y desplazar campo LEC
	return lec;
}


void CAN1_Rx0_FIFOx(CAN_TypeDef *port, CAN_FIFOMailBox_TypeDef *fifo) {
    if (port->RF0R & CAN_RF0R_FMP0) { // Nuevo mensaje en FIFO
        // Verificar el Last Error Code (LEC)
        if (CANx_GetLEC(port) == CAN_LEC_NO_ERROR) { // No hubo errores en la recepción
            // Copiar los datos del FIFO a la estructura fifo
            fifo->RIR = port->sFIFOMailBox[0].RIR;      // Identificador del mensaje
            fifo->RDTR = port->sFIFOMailBox[0].RDTR;    // Código de longitud de datos y FMI
            fifo->RDLR = port->sFIFOMailBox[0].RDLR;    // Datos (Low)
            fifo->RDHR = port->sFIFOMailBox[0].RDHR;    // Datos (High)
        } else {
            // Manejo del error: descartar el mensaje y liberar el FIFO
            SET_BIT(port->RF0R, CAN_RF0R_RFOM0);
            return; // Salir de la función sin llenar la estructura
        }
        // Liberar el FIFO para el siguiente mensaje
        SET_BIT(port->RF0R, CAN_RF0R_RFOM0);

    } else if (port->RF0R & CAN_RF0R_FULL0) { // FIFO lleno
        // Copiar los datos del FIFO a la estructura fifo
        fifo->RIR = port->sFIFOMailBox[0].RIR;
        fifo->RDTR = port->sFIFOMailBox[0].RDTR;
        fifo->RDLR = port->sFIFOMailBox[0].RDLR;
        fifo->RDHR = port->sFIFOMailBox[0].RDHR;
        // Liberar el FIFO para evitar la pérdida de datos
        SET_BIT(port->RF0R, CAN_RF0R_RFOM0);

    } else if (port->RF0R & CAN_RF0R_FOVR0) { // Sobrecarga en el FIFO
        // Manejar el estado de sobrecarga y limpiar el bit de sobrecarga
        CLEAR_BIT(port->RF0R, CAN_RF0R_FOVR0);
        // Copiar los datos del FIFO a la estructura fifo
        fifo->RIR = port->sFIFOMailBox[0].RIR;
        fifo->RDTR = port->sFIFOMailBox[0].RDTR;
        fifo->RDLR = port->sFIFOMailBox[0].RDLR;
        fifo->RDHR = port->sFIFOMailBox[0].RDHR;
        // Liberar el FIFO
        SET_BIT(port->RF0R, CAN_RF0R_RFOM0);
    }
}


void CAN1_Rx1_FIFOx(CAN_TypeDef *port, CAN_FIFOMailBox_TypeDef *fifo) {
    if (port->RF1R & CAN_RF1R_FMP1) { // Nuevo mensaje en FIFO
        // Verificar el Last Error Code (LEC)
        if (CANx_GetLEC(port) == CAN_LEC_NO_ERROR) { // No hubo errores en la recepción
            // Copiar los datos del FIFO a la estructura fifo
            fifo->RIR = port->sFIFOMailBox[1].RIR;      // Identificador del mensaje
            fifo->RDTR = port->sFIFOMailBox[1].RDTR;    // Código de longitud de datos y FMI
            fifo->RDLR = port->sFIFOMailBox[1].RDLR;    // Datos (Low)
            fifo->RDHR = port->sFIFOMailBox[1].RDHR;    // Datos (High)
        } else {
            // Manejo del error: descartar el mensaje y liberar el FIFO
            SET_BIT(port->RF1R, CAN_RF1R_RFOM1);
            return; // Salir de la función sin llenar la estructura
        }
        // Liberar el FIFO para el siguiente mensaje
        SET_BIT(port->RF1R, CAN_RF1R_RFOM1);

    } else if (port->RF1R & CAN_RF1R_FULL1) { // FIFO lleno
        // Copiar los datos del FIFO a la estructura fifo
        fifo->RIR = port->sFIFOMailBox[1].RIR;
        fifo->RDTR = port->sFIFOMailBox[1].RDTR;
        fifo->RDLR = port->sFIFOMailBox[1].RDLR;
        fifo->RDHR = port->sFIFOMailBox[1].RDHR;
        // Liberar el FIFO para evitar la pérdida de datos
        SET_BIT(port->RF1R, CAN_RF1R_RFOM1);

    } else if (port->RF1R & CAN_RF1R_FOVR1) { // Sobrecarga en el FIFO
        // Manejar el estado de sobrecarga y limpiar el bit de sobrecarga
        CLEAR_BIT(port->RF1R, CAN_RF1R_FOVR1);
        // Copiar los datos del FIFO a la estructura fifo
        fifo->RIR = port->sFIFOMailBox[1].RIR;
        fifo->RDTR = port->sFIFOMailBox[1].RDTR;
        fifo->RDLR = port->sFIFOMailBox[1].RDLR;
        fifo->RDHR = port->sFIFOMailBox[1].RDHR;
        // Liberar el FIFO
        SET_BIT(port->RF0R, CAN_RF1R_RFOM1);
    }
}






