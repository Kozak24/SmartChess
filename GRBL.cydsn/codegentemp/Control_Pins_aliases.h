/*******************************************************************************
* File Name: Control_Pins.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Control_Pins_ALIASES_H) /* Pins Control_Pins_ALIASES_H */
#define CY_PINS_Control_Pins_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Control_Pins_0			(Control_Pins__0__PC)
#define Control_Pins_0_PS		(Control_Pins__0__PS)
#define Control_Pins_0_PC		(Control_Pins__0__PC)
#define Control_Pins_0_DR		(Control_Pins__0__DR)
#define Control_Pins_0_SHIFT	(Control_Pins__0__SHIFT)
#define Control_Pins_0_INTR	((uint16)((uint16)0x0003u << (Control_Pins__0__SHIFT*2u)))

#define Control_Pins_1			(Control_Pins__1__PC)
#define Control_Pins_1_PS		(Control_Pins__1__PS)
#define Control_Pins_1_PC		(Control_Pins__1__PC)
#define Control_Pins_1_DR		(Control_Pins__1__DR)
#define Control_Pins_1_SHIFT	(Control_Pins__1__SHIFT)
#define Control_Pins_1_INTR	((uint16)((uint16)0x0003u << (Control_Pins__1__SHIFT*2u)))

#define Control_Pins_2			(Control_Pins__2__PC)
#define Control_Pins_2_PS		(Control_Pins__2__PS)
#define Control_Pins_2_PC		(Control_Pins__2__PC)
#define Control_Pins_2_DR		(Control_Pins__2__DR)
#define Control_Pins_2_SHIFT	(Control_Pins__2__SHIFT)
#define Control_Pins_2_INTR	((uint16)((uint16)0x0003u << (Control_Pins__2__SHIFT*2u)))

#define Control_Pins_3			(Control_Pins__3__PC)
#define Control_Pins_3_PS		(Control_Pins__3__PS)
#define Control_Pins_3_PC		(Control_Pins__3__PC)
#define Control_Pins_3_DR		(Control_Pins__3__DR)
#define Control_Pins_3_SHIFT	(Control_Pins__3__SHIFT)
#define Control_Pins_3_INTR	((uint16)((uint16)0x0003u << (Control_Pins__3__SHIFT*2u)))

#define Control_Pins_4			(Control_Pins__4__PC)
#define Control_Pins_4_PS		(Control_Pins__4__PS)
#define Control_Pins_4_PC		(Control_Pins__4__PC)
#define Control_Pins_4_DR		(Control_Pins__4__DR)
#define Control_Pins_4_SHIFT	(Control_Pins__4__SHIFT)
#define Control_Pins_4_INTR	((uint16)((uint16)0x0003u << (Control_Pins__4__SHIFT*2u)))

#define Control_Pins_5			(Control_Pins__5__PC)
#define Control_Pins_5_PS		(Control_Pins__5__PS)
#define Control_Pins_5_PC		(Control_Pins__5__PC)
#define Control_Pins_5_DR		(Control_Pins__5__DR)
#define Control_Pins_5_SHIFT	(Control_Pins__5__SHIFT)
#define Control_Pins_5_INTR	((uint16)((uint16)0x0003u << (Control_Pins__5__SHIFT*2u)))

#define Control_Pins_INTR_ALL	 ((uint16)(Control_Pins_0_INTR| Control_Pins_1_INTR| Control_Pins_2_INTR| Control_Pins_3_INTR| Control_Pins_4_INTR| Control_Pins_5_INTR))


#endif /* End Pins Control_Pins_ALIASES_H */


/* [] END OF FILE */
