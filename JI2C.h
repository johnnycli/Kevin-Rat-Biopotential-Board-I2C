/* ========================================
 *
 * Copyright Johnny Chiahao Li, Columbia University, 2019
 * Version 5.3
 *
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

//ICM-20948 Address
#define ACCEL_ADDR (0x68) //Accelerometer address I2C 1101000

//ICM-20948 Config Registers
#define ACC_WHO_AM_I (0x00u)
#define PWR_MGMT_1 (0x06u)
#define PWR_MGMT_2 (0x07u)
#define INT_ENABLE_1 (0x17u)
#define GYRO_CONFIG_1 (0x01u)
#define ACCEL_CONFIG_1 (0x14u)

//User Bank Registers
#define REG_BANK_SEL (0x7Fu)
#define BANK0 (0x00u)
#define BANK1 (0x10u)
#define BANK2 (0x32u)
#define BANK3 (0x48u)

//Accel Registers
#define ACCEL_XOUT_H (0x2Du)
#define ACCEL_XOUT_L (0x2Eu)
#define ACCEL_YOUT_H (0x2Fu)
#define ACCEL_YOUT_L (0x30u)
#define ACCEL_ZOUT_H (0x31u)
#define ACCEL_ZOUT_L (0x32u)

//Gyro Registers
#define GYRO_XOUT_H (0x33u)
#define GYRO_XOUT_L (0x34u)
#define GYRO_YOUT_H (0x35u)
#define GYRO_YOUT_L (0x36u)
#define GYRO_ZOUT_H (0x37u)
#define GYRO_ZOUT_L (0x38u)

//===================================================================
//ADS1015IDGST Address
#define ADC_ADDR (0x48u) //ADC 7-bit address I2C    1001000
#define ADC_ADDR_WR (0x90u) //ADC address write I2C 10010000 (For manual)
#define ADC_ADDR_RD (0x91u) //ADC address read I2C  10010001 (For manual)

//ADS1015IDGST Address Pointer Registers
#define CONVERSION_REG (0x00u)
#define CONFIG_REG (0x01u)
#define LO_THRESH_REG (0x02u)
#define HI_THRESH_REG (0x03u)


//===================================================================
//Register reading function
uint8 accel_ReadReg(uint8 Reg);
uint16 ADC_ReadReg();

//Register writing function
void accel_WriteReg(uint8 Reg, uint8 Config);
void ADC_WriteReg(uint8 ConfigU, uint8 ConfigL);

//===================================================================
//MANUAL ADC READ/WRITE. DOESN'T WORK RIGHT NOW FOR SOME REASONS.
//ADC Manual Read/Write
uint16 ADC_Manual_Read();
void ADC_Manual_Write(uint8 ConfigU, uint8 ConfigL);

/* [] END OF FILE */
