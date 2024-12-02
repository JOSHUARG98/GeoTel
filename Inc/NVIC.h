/*
 * NVIC.h
 *
 *  Created on: Oct 31, 2024
 *      Author: joshu
 */

#ifndef NVIC_H_
#define NVIC_H_
#include "stm32l4xx.h"

void NVIC_Enable(uint32_t irq_num, uint8_t priority);
//void NVIC_ClearPending(uint32_t irq_num);


#endif /* NVIC_H_ */
