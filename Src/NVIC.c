/*
 * NVIC.c
 *
 *  Created on: Oct 31, 2024
 *      Author: joshu
 */

#include "stm32l4xx.h"
#include <stdint.h>
#include<stdbool.h>
#include "NVIC.h"

void NVIC_Enable(uint32_t irq_num, uint8_t priority) {
    if (irq_num >= 84) {
        // El número de interrupción es inválido, dado que el microcontrolador solo tiene 84 interrupciones
        return;
    }

    // Calcular el índice del registro ISER y el bit correspondiente
    uint32_t iser_index = irq_num / 32;
    uint32_t iser_bit = irq_num % 32;

    // Activar la interrupción correspondiente en NVIC_ISER
    NVIC->ISER[iser_index] = (1 << iser_bit);

    // Configurar la prioridad en el registro NVIC_IPR
    NVIC->IP[irq_num] = (priority & 0xF) << 4; // La prioridad usa 4 bits más significativos

    // La función no limpia en ICER, pero si quieres limpiar el bit usa:
    // NVIC->ICER[iser_index] = (1 << iser_bit); // Esto es opcional si necesitas desactivar
}

/*
void NVIC_ClearPending(uint32_t irq_num) {
    if (irq_num >= 84) {
        // El número de interrupción es inválido, dado que el microcontrolador solo tiene 84 interrupciones
        return;
    }

    // Calcular el índice del registro ICPR y el bit correspondiente
    uint32_t icpr_index = irq_num / 32;
    uint32_t icpr_bit = irq_num % 32;

    // Limpiar el estado pendiente de la interrupción correspondiente en NVIC_ICPR
    NVIC->ICPR[icpr_index] = (1 << icpr_bit);
}
*/


/*

void NVIC_SetCFGR(uint8_t position, uint8_t priority){
	uint8_t div1 = position / 32, div2 = position / 4;
	//unsigned int * NVIC_ICERn = ( ( unsigned int * ) (NVIC_BASE + NVIC_ICER + (0x04*div1)) )  ;
	//unsigned int * NVIC_ISERn = ( ( unsigned int * ) (NVIC_BASE + NVIC_ISER + (0x04*div1)) )  ;
	//unsigned int * NVIC_IPRn = ( (  unsigned int * ) (NVIC_BASE + NVIC_IPR + (0x04*div2)) )  ;

	while(div1>0){
		position -= 32;
		div1--;
	}
	div1=4;
	while(div1 > 0){
		div2 = ((10 * (position - div1 + 1)) / 4) ;//Obtenemos el valor con decimales
		div2 = div2 - (10 * ((position - div1 + 1) / 4));//Recuperamos el decimal
		if(div2){//No corresponde a la posición
			div1--; //Seguimos bucando coincidencia
		}
		else{//Coincidencia de posición
			div2 = div1 - 1;//Recuperamos la posición
			div1 = 0;
		}
	}

	SET_BIT(NVIC->ISER,position);

	//NVIC->ISER |= (1 << position); // Habilita la interrupción
	NVIC->IP[position] = ((priority << 4) & 0xF0); // Coloca la prioridad en la posición correcta
	//NVIC->IP |= ((priority << (div2 * 8)) << 4);//Coloca Prioridad 4*x+3; x= 8 y 7 I2C1

}
*/
