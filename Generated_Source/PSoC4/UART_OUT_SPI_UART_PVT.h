/***************************************************************************//**
* \file UART_OUT_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_UART_OUT_H)
#define CY_SCB_SPI_UART_PVT_UART_OUT_H

#include "UART_OUT_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_OUT_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_OUT_rxBufferHead;
    extern volatile uint32  UART_OUT_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART_OUT_rxBufferOverflow;
    /** @} globals */
#endif /* (UART_OUT_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_OUT_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_OUT_txBufferHead;
    extern volatile uint32  UART_OUT_txBufferTail;
#endif /* (UART_OUT_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_OUT_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_OUT_rxBufferInternal[UART_OUT_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_OUT_INTERNAL_RX_SW_BUFFER) */

#if (UART_OUT_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_OUT_txBufferInternal[UART_OUT_TX_BUFFER_SIZE];
#endif /* (UART_OUT_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_OUT_SpiPostEnable(void);
void UART_OUT_SpiStop(void);

#if (UART_OUT_SCB_MODE_SPI_CONST_CFG)
    void UART_OUT_SpiInit(void);
#endif /* (UART_OUT_SCB_MODE_SPI_CONST_CFG) */

#if (UART_OUT_SPI_WAKE_ENABLE_CONST)
    void UART_OUT_SpiSaveConfig(void);
    void UART_OUT_SpiRestoreConfig(void);
#endif /* (UART_OUT_SPI_WAKE_ENABLE_CONST) */

void UART_OUT_UartPostEnable(void);
void UART_OUT_UartStop(void);

#if (UART_OUT_SCB_MODE_UART_CONST_CFG)
    void UART_OUT_UartInit(void);
#endif /* (UART_OUT_SCB_MODE_UART_CONST_CFG) */

#if (UART_OUT_UART_WAKE_ENABLE_CONST)
    void UART_OUT_UartSaveConfig(void);
    void UART_OUT_UartRestoreConfig(void);
#endif /* (UART_OUT_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_OUT_SetPins() */
#define UART_OUT_UART_RX_PIN_ENABLE    (UART_OUT_UART_RX)
#define UART_OUT_UART_TX_PIN_ENABLE    (UART_OUT_UART_TX)

/* UART RTS and CTS position to be used in  UART_OUT_SetPins() */
#define UART_OUT_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_OUT_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_OUT_SpiUartEnableIntRx(intSourceMask)  UART_OUT_SetRxInterruptMode(intSourceMask)
#define UART_OUT_SpiUartEnableIntTx(intSourceMask)  UART_OUT_SetTxInterruptMode(intSourceMask)
uint32  UART_OUT_SpiUartDisableIntRx(void);
uint32  UART_OUT_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_OUT_H) */


/* [] END OF FILE */
