/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_UART_OUT_H)
#define CY_SCB_PVT_UART_OUT_H

#include "UART_OUT.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_OUT_SetI2CExtClkInterruptMode(interruptMask) UART_OUT_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_OUT_ClearI2CExtClkInterruptSource(interruptMask) UART_OUT_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_OUT_GetI2CExtClkInterruptSource()                (UART_OUT_INTR_I2C_EC_REG)
#define UART_OUT_GetI2CExtClkInterruptMode()                  (UART_OUT_INTR_I2C_EC_MASK_REG)
#define UART_OUT_GetI2CExtClkInterruptSourceMasked()          (UART_OUT_INTR_I2C_EC_MASKED_REG)

#if (!UART_OUT_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_OUT_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_OUT_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_OUT_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_OUT_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_OUT_GetExtSpiClkInterruptSource()                 (UART_OUT_INTR_SPI_EC_REG)
    #define UART_OUT_GetExtSpiClkInterruptMode()                   (UART_OUT_INTR_SPI_EC_MASK_REG)
    #define UART_OUT_GetExtSpiClkInterruptSourceMasked()           (UART_OUT_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_OUT_CY_SCBIP_V1) */

#if(UART_OUT_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_OUT_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_OUT_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_OUT_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_OUT_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_OUT_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_OUT_CUSTOM_INTR_HANDLER) */
#endif /* (UART_OUT_SCB_IRQ_INTERNAL) */

extern UART_OUT_BACKUP_STRUCT UART_OUT_backup;

#if(UART_OUT_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_OUT_scbMode;
    extern uint8 UART_OUT_scbEnableWake;
    extern uint8 UART_OUT_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_OUT_mode;
    extern uint8 UART_OUT_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_OUT_rxBuffer;
    extern uint8   UART_OUT_rxDataBits;
    extern uint32  UART_OUT_rxBufferSize;

    extern volatile uint8 * UART_OUT_txBuffer;
    extern uint8   UART_OUT_txDataBits;
    extern uint32  UART_OUT_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_OUT_numberOfAddr;
    extern uint8 UART_OUT_subAddrSize;
#endif /* (UART_OUT_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_OUT_SCB_MODE_I2C_CONST_CFG || \
        UART_OUT_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_OUT_IntrTxMask;
#endif /* (! (UART_OUT_SCB_MODE_I2C_CONST_CFG || \
              UART_OUT_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_OUT_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_OUT_SCB_MODE_I2C_RUNTM_CFG     (UART_OUT_SCB_MODE_I2C      == UART_OUT_scbMode)
    #define UART_OUT_SCB_MODE_SPI_RUNTM_CFG     (UART_OUT_SCB_MODE_SPI      == UART_OUT_scbMode)
    #define UART_OUT_SCB_MODE_UART_RUNTM_CFG    (UART_OUT_SCB_MODE_UART     == UART_OUT_scbMode)
    #define UART_OUT_SCB_MODE_EZI2C_RUNTM_CFG   (UART_OUT_SCB_MODE_EZI2C    == UART_OUT_scbMode)
    #define UART_OUT_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_OUT_SCB_MODE_UNCONFIG == UART_OUT_scbMode)

    /* Defines wakeup enable */
    #define UART_OUT_SCB_WAKE_ENABLE_CHECK       (0u != UART_OUT_scbEnableWake)
#endif /* (UART_OUT_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_OUT_CY_SCBIP_V1)
    #define UART_OUT_SCB_PINS_NUMBER    (7u)
#else
    #define UART_OUT_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_OUT_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_OUT_H) */


/* [] END OF FILE */
