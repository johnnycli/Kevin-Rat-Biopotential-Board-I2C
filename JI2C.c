/* ========================================
 *
 * Copyright Johnny Chiahao Li, Columbia University, 2019
 * Version 6.2
 *
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <JI2C.h>
//ACCEL
//=======================================================================================

//Takes target register and return 1 byte data.
uint8 accel_ReadReg(uint8 Reg){
    //Buffer containing the target register.
    uint8 Write_Buf[1]={0};
    Write_Buf[0]=Reg;
    
    //Buffer to store read value
    uint8 Read_Buf[1]={0};
    
    //Write register to read to salve device
    I2C_I2CMasterWriteBuf(ACCEL_ADDR, (uint8*)Write_Buf,1,I2C_I2C_MODE_NO_STOP);
    while((I2C_I2CMasterStatus()& I2C_I2C_MSTAT_WR_CMPLT)==0){}
    
    
    //Read register value and return data.
    I2C_I2CMasterReadBuf(ACCEL_ADDR,(uint8*)Read_Buf,1,I2C_I2C_MODE_REPEAT_START);
    while((I2C_I2CMasterStatus()& I2C_I2C_MSTAT_RD_CMPLT)==0){}
        
    return Read_Buf[0];
}

//Takes target register and write 1 byte config.
void accel_WriteReg(uint8 Reg, uint8 Config){
    
    //Crete uint8 buffer array of 2 for cofig register address and 2 bytes of data.
    uint8 Write_Buf[2]={0};
    Write_Buf[0]=Reg;
    Write_Buf[1]=Config;
    
    //Write to slave register to be altered.
    I2C_I2CMasterWriteBuf(ACCEL_ADDR,(uint8*)Write_Buf,2,I2C_I2C_MODE_COMPLETE_XFER);    
    //False loop       
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}


    //Exit method.
    return;
}
//ADC
//=======================================================================================
//Select conversion register by default and return uint16 data that is the combination result of the H byte and L byte.
uint16 ADC_ReadReg(){
    //Buffer to store read value
    uint8 Read_Buf[2]={0};
    
    uint8 PReg[1]={0};
    PReg[0]= CONVERSION_REG;
    I2C_I2CMasterWriteBuf(ADC_ADDR,(uint8*)PReg,1,I2C_I2C_MODE_COMPLETE_XFER);
    
    //False loop       
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    
    //Read register value and return data.
    I2C_I2CMasterReadBuf(ADC_ADDR,(uint8*)Read_Buf,2,I2C_I2C_MODE_REPEAT_START);
    while((I2C_I2CMasterStatus()& I2C_I2C_MSTAT_RD_CMPLT)==0){}
    I2C_I2CMasterSendStop(100UL);
    
    uint16 Read_Res=(Read_Buf[0] << 8) | Read_Buf[1];
    
    return Read_Res;
}

//Select configuration register by default and writes two bytes of configurations.
void ADC_WriteReg(uint8 ConfigU, uint8 ConfigL){
    uint8 PReg[1]={0};
    PReg[0]= CONFIG_REG;
    I2C_I2CMasterWriteBuf(ADC_ADDR,(uint8*)PReg,1,I2C_I2C_MODE_NO_STOP);
    
    //False loop       
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    
    //Crete uint8 buffer array of 2 for cofig register address and 2 bytes of data.
    uint8 Write_Buf[2]={0};  
    Write_Buf[0]=ConfigU;
    Write_Buf[1]=ConfigL;
   
    //Write to the config register with data in the buffer.
    I2C_I2CMasterWriteBuf(ADC_ADDR,(uint8*)Write_Buf,2,I2C_I2C_MODE_REPEAT_START);    
    //False loop       
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    
    I2C_I2CMasterSendStop(100UL);
    //Exit method.
    return;
}

//ADC Manual. Doesn't work at the moment.
//=======================================================================================

uint16 ADC_Manual_Read(){
    uint8 Read_Buf_H[1]={0};
    uint8 Read_Buf_L[1]={0};
    uint32 timeout = 100UL;
    uint32 status;
    
    //Frame 1 (ADC Address)
    status = I2C_I2CMasterSendStart(ADC_ADDR,I2C_I2C_WRITE_XFER_MODE,timeout);
    
    //Frame 2 (Move pointer to Conversion Register)
    status = I2C_I2CMasterWriteByte(CONVERSION_REG,timeout);
    
    //Frame 3 (Essentially a restart without a NAK)
    status = I2C_I2CMasterSendStop(timeout);
    status = I2C_I2CMasterSendStart(ADC_ADDR,I2C_I2C_READ_XFER_MODE,timeout);
    
    //Frame 4 (Read high byte)
    status = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA,(uint8*)Read_Buf_H,timeout);
    
    //Frame 5 (Read low byte send NAK for stop)
    status = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA,(uint8*)Read_Buf_L,timeout);
    
    //Send Stop
    status = I2C_I2CMasterSendStop(timeout);
        
    uint16 Res=(Read_Buf_H[0] << 8) | Read_Buf_L[0];
    return Res;
}

void ADC_Manual_Write(uint8 ConfigU, uint8 ConfigL){
    
    uint8 Write_Buf[3]={CONFIG_REG,ConfigU,ConfigL};    
    
    uint32 timeout = 100UL;
    
    //Frame 1 (Generate start and send in slave address with write)
    uint32 status = I2C_I2CMasterSendStart(ADC_ADDR,I2C_I2C_WRITE_XFER_MODE,timeout);
    
    
    if(I2C_I2C_MSTR_NO_ERROR==status){
        
        for(int i=0; i<3; i++){
            //Frame 2,3,4
            status = I2C_I2CMasterWriteByte(Write_Buf[i],timeout);
            if(I2C_I2C_MSTR_NO_ERROR!= status){
                break;
            }
        }
        if((I2C_I2C_MSTR_NO_ERROR==status)||(I2C_I2C_MSTR_ERR_LB_NAK==status)){
            //Send Stop
            I2C_I2CMasterSendStop(timeout);
        }
    }

    
    
    return;
}



/* [] END OF FILE */
