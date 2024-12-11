/*
 * MPU6050.h
 *
 *  Created on: Jul 30, 2024
 *      Author: joshu
 */

#ifndef MPU6050_H_
#define MPU6050_H_
#include "I2Cx.h"


//REGISTROS DEL MPU-6050
#define MPU6050_CONFIG (0x1A)  //Registro de configuracion para la sincronizacion de la trama y la configuracion de filtro paso bajas. R/W
#define MPU6050_GYRO_CONFIG (0x1B) //Registro de configuracion del giroscopio. R/W
#define MPU6050_ACCEL_CONFIG (0x1C) //Registro de configuracion del acelerometro. R/W
#define MPU6050_FIFO_EN (0x23) // Registro de habilitacion de FIFO. R/W
#define MPU6050_I2C_MST_CTRL (0x24) // Registro de control del maestro I2C. R/W
#define MPU6050_I2C_SLV0_ADDR (0x25) //Secuencia de transferencia de datos para el esclavo 0. R/W
#define MPU6050_I2C_SLV0_REG (0x26)
#define MPU6050_I2C_SLV0_CTRL (0x27)
#define MPU6050_I2C_SLV1_ADDR (0x28) //Secuencia de transferencia de datos para el esclavo 1. R/W
#define MPU6050_I2C_SLV1_REG (0x29)
#define MPU6050_I2C_SLV1_CTRL (0x2A)
#define MPU6050_I2C_SLV2_ADDR (0x2B) //Secuencia de transferencia de datos para el esclavo 2. R/W
#define MPU6050_I2C_SLV2_REG (0x2C)
#define MPU6050_I2C_SLV2_CTRL (0x2D)
#define MPU6050_I2C_SLV3_ADDR (0x2E) //Secuencia de transferencia de datos para el esclavo 3. R/W
#define MPU6050_I2C_SLV3_REG (0x2F)
#define MPU6050_I2C_SLV3_CTRL (0x30)
#define MPU6050_I2C_SLV4_ADDR (0x31) //Secuencia de transferencia de datos para el esclavo 4. R/W
#define MPU6050_I2C_SLV4_REG (0x32)
#define MPU6050_I2C_SLV4_DO (0x33)
#define MPU6050_I2C_SLV4_CTRL (0x34)
#define MPU6050_I2C_SLV4_DI (0x35)
#define MPU6050_I2C_MST_STATUS (0x36) //Estado de la interrupcion. R
#define MPU6050_INT_PIN_CFG (0x37) //Comportamiento de las se'ales de interrupcion. R/W
#define MPU6050_INT_ENABLE (0x38) // Habilita la generacion de interrupcion. R/W
#define MPU6050_INT_STATUS (0x3A) //Muestra el estado de interrupcion de cada fuente. R
#define MPU6050_ACCEL_XOUT_H (0x3B) //Mediciones del acelerometro. R
#define MPU6050_ACCEL_XOUT_L (0x3C)
#define MPU6050_ACCEL_YOUT_H (0x3D)
#define MPU6050_ACCEL_YOUT_L (0x3E)
#define MPU6050_ACCEL_ZOUT_H (0x3F)
#define MPU6050_ACCEL_ZOUT_L (0x40)
#define MPU6050_TEMP_OUT_H (0x41)
#define MPU6050_TEMP_OUT_L (0x42)
#define MPU6050_GYRO_XOUT_H (0x43) //Mediciones del giroscopio. R
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x47
#define MPU6050_GYRO_ZOUT_L 0x48
#define MPU6050_EXT_SENS_DATA_00 0x49 //Guarda datos de lectura de sensores externos. R
#define MPU6050_EXT_SENS_DATA_01 0x4A
#define MPU6050_EXT_SENS_DATA_02 0x4B
#define MPU6050_EXT_SENS_DATA_03 0x4C
#define MPU6050_EXT_SENS_DATA_04 0x4D
#define MPU6050_EXT_SENS_DATA_05 0x4E
#define MPU6050_EXT_SENS_DATA_06 0x4F
#define MPU6050_EXT_SENS_DATA_07 0x50
#define MPU6050_EXT_SENS_DATA_08 0x51
#define MPU6050_EXT_SENS_DATA_09 0x52
#define MPU6050_EXT_SENS_DATA_10 0x53
#define MPU6050_EXT_SENS_DATA_11 0x54
#define MPU6050_EXT_SENS_DATA_12 0x55
#define MPU6050_EXT_SENS_DATA_13 0x56
#define MPU6050_EXT_SENS_DATA_14 0x57
#define MPU6050_EXT_SENS_DATA_15 0x58
#define MPU6050_EXT_SENS_DATA_16 0x59
#define MPU6050_EXT_SENS_DATA_17 0x5A
#define MPU6050_EXT_SENS_DATA_18 0x5B
#define MPU6050_EXT_SENS_DATA_19 0x5C
#define MPU6050_EXT_SENS_DATA_20 0x5D
#define MPU6050_EXT_SENS_DATA_21 0x5E
#define MPU6050_EXT_SENS_DATA_22 0x5F
#define MPU6050_EXT_SENS_DATA_23 0x60
#define MPU6050_I2C_SLV0_DO 0x63 //Contiene el dato de salida escrito en el esclavo cuando esta en modo escritura. R/W
#define MPU6050_I2C_SLV1_DO 0x64
#define MPU6050_I2C_SLV2_DO 0x65
#define MPU6050_I2C_SLV3_DO 0x66
#define MPU6050_I2C_MST_DELAY_CTRL 0x67 //Especifica el tiempo de la sombra de datos del sensor externo. R/W
#define MPU6050_SIGNAL_PATH_RESET 0x68 // W.
#define MPU6050_USER_CTRL (0x6A)// R/W.
#define MPU6050_PWR_MGMT_1 0x6B // Registro que permite configurar el modo de potencia y habilita el oscilador interno R/W.
#define MPU6050_PWR_MGMT_2 (0x6C) //R/W.
#define MPU6050_FIFO_COUNT_H (0x72) // R.
#define MPU6050_FIFO_COUNT_L (0x73) // R.
#define MPU6050_FIFO_R_W (0x74) // R/W.
#define MPU6050_WHO_AM_I (0x75) // R.

#define AddressMPU6050 0x68 ///Direccion del MPU-6050


/*********************************************
        DECLARACION DE FUNCIONES
**********************************************/
void MPU6050_Init(void);


int16_t MPU6050_Read(uint8_t Register);

void MPU6050_Init(void){
    I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_PWR_MGMT_1, 0x00);
    I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_ACCEL_CONFIG, 0X00); //Configura el acelerometro a +-2g
    I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_GYRO_CONFIG, 0X00); //Configura giroscopio a +- 250°/s
    I2C_Tx_2Bytes(I2C3, AddressMPU6050, 0x19, 0X07);
    I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_CONFIG, 0x01);
    //I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_CONFIG, 0x01);
   // I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_ACCEL_CONFIG, 0X00);
    //I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_FIFO_EN, 0XFF);
     I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_FIFO_EN, 0xFF);
    I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_USER_CTRL, 0x40);
}

int16_t MPU6050_Read(uint8_t Register){

	int16_t Data;
I2C_Tx_1Byte (I2C3, AddressMPU6050, Register);
Data = I2C_Rx_1Byte(I2C3, AddressMPU6050);

//I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_USER_CTRL, 0x04);
//I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_FIFO_EN, 0x08);
//I2C_Tx_2Bytes(I2C3, AddressMPU6050, MPU6050_USER_CTRL, 0x40);

return Data;
}



#endif /* MPU6050_H_ */
