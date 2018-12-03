/*******************************************************************************
* File Name: Step_Pulse_Clock.h
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

#if !defined(CY_CLOCK_Step_Pulse_Clock_H)
#define CY_CLOCK_Step_Pulse_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Step_Pulse_Clock_StartEx(uint32 alignClkDiv);
#define Step_Pulse_Clock_Start() \
    Step_Pulse_Clock_StartEx(Step_Pulse_Clock__PA_DIV_ID)

#else

void Step_Pulse_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Step_Pulse_Clock_Stop(void);

void Step_Pulse_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Step_Pulse_Clock_GetDividerRegister(void);
uint8  Step_Pulse_Clock_GetFractionalDividerRegister(void);

#define Step_Pulse_Clock_Enable()                         Step_Pulse_Clock_Start()
#define Step_Pulse_Clock_Disable()                        Step_Pulse_Clock_Stop()
#define Step_Pulse_Clock_SetDividerRegister(clkDivider, reset)  \
    Step_Pulse_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define Step_Pulse_Clock_SetDivider(clkDivider)           Step_Pulse_Clock_SetDividerRegister((clkDivider), 1u)
#define Step_Pulse_Clock_SetDividerValue(clkDivider)      Step_Pulse_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Step_Pulse_Clock_DIV_ID     Step_Pulse_Clock__DIV_ID

#define Step_Pulse_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Step_Pulse_Clock_CTRL_REG   (*(reg32 *)Step_Pulse_Clock__CTRL_REGISTER)
#define Step_Pulse_Clock_DIV_REG    (*(reg32 *)Step_Pulse_Clock__DIV_REGISTER)

#define Step_Pulse_Clock_CMD_DIV_SHIFT          (0u)
#define Step_Pulse_Clock_CMD_PA_DIV_SHIFT       (8u)
#define Step_Pulse_Clock_CMD_DISABLE_SHIFT      (30u)
#define Step_Pulse_Clock_CMD_ENABLE_SHIFT       (31u)

#define Step_Pulse_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Step_Pulse_Clock_CMD_DISABLE_SHIFT))
#define Step_Pulse_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Step_Pulse_Clock_CMD_ENABLE_SHIFT))

#define Step_Pulse_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define Step_Pulse_Clock_DIV_FRAC_SHIFT (3u)
#define Step_Pulse_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define Step_Pulse_Clock_DIV_INT_SHIFT  (8u)

#else 

#define Step_Pulse_Clock_DIV_REG        (*(reg32 *)Step_Pulse_Clock__REGISTER)
#define Step_Pulse_Clock_ENABLE_REG     Step_Pulse_Clock_DIV_REG
#define Step_Pulse_Clock_DIV_FRAC_MASK  Step_Pulse_Clock__FRAC_MASK
#define Step_Pulse_Clock_DIV_FRAC_SHIFT (16u)
#define Step_Pulse_Clock_DIV_INT_MASK   Step_Pulse_Clock__DIVIDER_MASK
#define Step_Pulse_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Step_Pulse_Clock_H) */

/* [] END OF FILE */
