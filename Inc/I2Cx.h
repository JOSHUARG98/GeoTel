/*
 * I2Cx.h
 *
 *  Created on: Jul 29, 2024
 *      Author: joshu
 */

#ifndef I2CX_H_
#define I2CX_H_
#include "stm32l4xx.h"


void I2C_delay(uint32_t T);
void RCC_En_I2C(I2C_TypeDef *port);
void I2C_Init(I2C_TypeDef *port);
void I2C_Tx_1Byte (I2C_TypeDef *port, uint8_t Adress, uint8_t Byte_0);
void I2C_Tx_2Bytes (I2C_TypeDef *port, uint8_t Adress, uint8_t Byte_0, uint8_t Byte_1);
void I2C_Tx_3Bytes (I2C_TypeDef *Port, uint8_t Adress, uint8_t Byte_0, uint8_t Byte_1, uint8_t Byte_2);
void I2C_Tx_4Bytes (I2C_TypeDef *Port, uint8_t Adress, uint8_t Byte_0, uint8_t Byte_1, uint8_t Byte_2, uint8_t Byte_3);

int16_t I2C_Rx_1Byte (I2C_TypeDef *Port, uint8_t Adress);

#endif /* I2CX_H_ */
