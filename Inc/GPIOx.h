/*
 * GPIOx.h
 *
 *  Created on: Jul 29, 2024
 *      Author: joshu
 */

#ifndef GPIOX_H_
#define GPIOX_H_

#include "stm32l4xx.h"

void GPIOx_InitAF(GPIO_TypeDef *Port_, uint8_t Pin_, uint8_t OTYPER_, uint8_t OSPEEDR_, uint8_t AFR_, bool PUR);
void GPIOx_InitIO(GPIO_TypeDef *Port_, uint8_t Pin_, uint8_t IO, bool PUR);
void RCC_EnPort(GPIO_TypeDef *port);
void SystCLK_SetMSI(uint8_t MSI_clkSel);






#endif /* GPIOX_H_ */
