/* ========================================
 *
 * Copyright Johnny Chiahao Li, Columbia University, 2019
 * Version 3.5
 *
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <JI2C.h>

void Stack_Handler(uint32 eventCode, void *eventParam)
{
    switch(eventCode)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
    }
}
int main(void)
{   
    //Starts BLE Handeling
    CyBle_Start(Stack_Handler);
    CyGlobalIntEnable; 
    
    /*
    //Starts UART
    UART_OUT_Start();
    UART_OUT_Init();
    */
    
    //Enabling I2C and the interrupts
    I2C_Start();    
      
    //Debugging variables
    volatile uint16 MasterStatus;
    volatile uint8 checkWrite;
    
    //Define variables to hold data. Volatile so it does not get eliminated by the optimizer from the watchlit.
    volatile uint8 deviceID;
    volatile uint8 XoutH;
    volatile uint8 XoutL;
    
    volatile uint8 ACCEL_X_L;
    volatile uint8 ACCEL_X_H;
    volatile uint8 ACCEL_Y_L;
    volatile uint8 ACCEL_Y_H;
    volatile uint8 ACCEL_Z_L;
    volatile uint8 ACCEL_Z_H;
    
    volatile double ACCEL_X;
    volatile double ACCEL_Y;
    volatile double ACCEL_Z;
    
    volatile uint8 GYRO_X_L;
    volatile uint8 GYRO_X_H;
    volatile uint8 GYRO_Y_L;
    volatile uint8 GYRO_Y_H;
    volatile uint8 GYRO_Z_L;
    volatile uint8 GYRO_Z_H;
    
    volatile double GYRO_X;
    volatile double GYRO_Y;
    volatile double GYRO_Z;
    
    //Variable to catch ADC output (2 bytes)
    volatile uint8 ADC_Data_H;
    volatile uint8 ADC_Data_L;
    
    
    //Accel User Bank 0 to perform reset.
    accel_WriteReg(REG_BANK_SEL,BANK0); 
    MasterStatus = I2C_I2CMasterStatus();
    checkWrite = accel_ReadReg(PWR_MGMT_1);
    //Start by resetting power management 1
    accel_WriteReg(PWR_MGMT_1,0x80u);
    //Delay for restart
    CyDelay(0x01u);
    checkWrite = accel_ReadReg(PWR_MGMT_1);
    //Auto set clock
    accel_WriteReg(PWR_MGMT_1,0x01u);
    checkWrite = accel_ReadReg(PWR_MGMT_1);
    
    checkWrite = accel_ReadReg(REG_BANK_SEL);
    //Accel User Bank 2 to configure GYRO
    accel_WriteReg(REG_BANK_SEL,BANK2);
    checkWrite = accel_ReadReg(REG_BANK_SEL);
    
    //LPF Disabled. Gyro Full Scale Select +-250dps (131 division).
    accel_WriteReg(GYRO_CONFIG_1,0x00u);
    //Debug point 1
    checkWrite = accel_ReadReg(GYRO_CONFIG_1);
    
    //±4g Full Scale (8192 Division)
    accel_WriteReg(ACCEL_CONFIG_1,0x06u);
    checkWrite = accel_ReadReg(ACCEL_CONFIG_1);
    
    //Accel User Bank 0 to configure the rest and to allow reading of accel and gyro in Bank 0.
    accel_WriteReg(REG_BANK_SEL,BANK0); 
    
    MasterStatus = I2C_I2CMasterStatus();
    
    //Enable all accel and gyro
    accel_WriteReg(PWR_MGMT_2,0x00u);
    MasterStatus = I2C_I2CMasterStatus();

    //Write checks
    checkWrite = accel_ReadReg(PWR_MGMT_1);
    checkWrite = accel_ReadReg(PWR_MGMT_2);

    //Reset config to default
    //ADC_Manual_Write(0x84u,0x83u);
    ADC_WriteReg(0x84u,0x83u);
    for(;;)
    {
        //BLE Processes
        CyBle_ProcessEvents();
        
        //===================================================================================================
        //Accelerometer Section 
       
        //Testing the accel device ID
        deviceID = accel_ReadReg(ACC_WHO_AM_I);//Expect 0xEA
        
        //ACCEL Aquisition
        ACCEL_X_L = accel_ReadReg(ACCEL_XOUT_L);
        ACCEL_X_H = accel_ReadReg(ACCEL_XOUT_H);
        ACCEL_Y_L = accel_ReadReg(ACCEL_YOUT_L);
        ACCEL_Y_H = accel_ReadReg(ACCEL_YOUT_H);
        ACCEL_Z_L = accel_ReadReg(ACCEL_ZOUT_L);
        ACCEL_Z_H = accel_ReadReg(ACCEL_ZOUT_H);
        
        ACCEL_X = ((ACCEL_X_H << 8) | ACCEL_X_L)/2048.0;
        ACCEL_Y = ((ACCEL_Y_H << 8) | ACCEL_Y_L)/2048.0;
        ACCEL_Z = ((ACCEL_Z_H << 8) | ACCEL_Z_L)/2048.0;
        
        
        //GYRO Aquisition
        GYRO_X_L = accel_ReadReg(GYRO_XOUT_L);
        GYRO_X_H = accel_ReadReg(GYRO_XOUT_H);
        GYRO_Y_L = accel_ReadReg(GYRO_YOUT_L);
        GYRO_Y_H = accel_ReadReg(GYRO_YOUT_H);
        GYRO_Z_L = accel_ReadReg(GYRO_ZOUT_L);
        GYRO_Z_H = accel_ReadReg(GYRO_ZOUT_H);
        
        GYRO_X = ((GYRO_X_H << 8) | GYRO_X_L)/131.0;
        GYRO_Y = ((GYRO_Y_H << 8) | GYRO_Y_L)/131.0;
        GYRO_Z = ((GYRO_Z_H << 8) | GYRO_Z_L)/131.0;
     
        //Random delay intented for limiting data collection rate.
        CyDelay(0x64);
        
        //===================================================================================================
        //ADC Section
        
        //Read conversion result. Using manual read. (Doesn't work yet)
        //volatile uint16 ADC_Data_Buffer = ADC_Manual_Read();
        
        //Read conversion result. (Raw data)
        volatile uint16 ADC_Data_Buffer = ADC_ReadReg();
        
       
        
    }
}

/* [] END OF FILE */
