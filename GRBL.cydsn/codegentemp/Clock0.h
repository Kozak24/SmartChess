/*******************************************************************************
* File Name: Clock0.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock0_H)
#define CY_CLOCK_Clock0_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clock0_StartEx(uint32 alignClkDiv);
#define Clock0_Start() \
    Clock0_StartEx(Clock0__PA_DIV_ID)

#else

void Clock0_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clock0_Stop(void);

void Clock0_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock0_GetDividerRegister(void);
uint8  Clock0_GetFractionalDividerRegister(void);

#define Clock0_Enable()                         Clock0_Start()
#define Clock0_Disable()                        Clock0_Stop()
#define Clock0_SetDividerRegister(clkDivider, reset)  \
    Clock0_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock0_SetDivider(clkDivider)           Clock0_SetDividerRegister((clkDivider), 1u)
#define Clock0_SetDividerValue(clkDivider)      Clock0_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clock0_DIV_ID     Clock0__DIV_ID

#define Clock0_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clock0_CTRL_REG   (*(reg32 *)Clock0__CTRL_REGISTER)
#define Clock0_DIV_REG    (*(reg32 *)Clock0__DIV_REGISTER)

#define Clock0_CMD_DIV_SHIFT          (0u)
#define Clock0_CMD_PA_DIV_SHIFT       (8u)
#define Clock0_CMD_DISABLE_SHIFT      (30u)
#define Clock0_CMD_ENABLE_SHIFT       (31u)

#define Clock0_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clock0_CMD_DISABLE_SHIFT))
#define Clock0_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clock0_CMD_ENABLE_SHIFT))

#define Clock0_DIV_FRAC_MASK  (0x000000F8u)
#define Clock0_DIV_FRAC_SHIFT (3u)
#define Clock0_DIV_INT_MASK   (0xFFFFFF00u)
#define Clock0_DIV_INT_SHIFT  (8u)

#else 

#define Clock0_DIV_REG        (*(reg32 *)Clock0__REGISTER)
#define Clock0_ENABLE_REG     Clock0_DIV_REG
#define Clock0_DIV_FRAC_MASK  Clock0__FRAC_MASK
#define Clock0_DIV_FRAC_SHIFT (16u)
#define Clock0_DIV_INT_MASK   Clock0__DIVIDER_MASK
#define Clock0_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clock0_H) */

/* [] END OF FILE */
