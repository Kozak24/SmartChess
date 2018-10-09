/*******************************************************************************
* File Name: Stepper_Pins.h  
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

#if !defined(CY_PINS_Stepper_Pins_ALIASES_H) /* Pins Stepper_Pins_ALIASES_H */
#define CY_PINS_Stepper_Pins_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Stepper_Pins_0			(Stepper_Pins__0__PC)
#define Stepper_Pins_0_PS		(Stepper_Pins__0__PS)
#define Stepper_Pins_0_PC		(Stepper_Pins__0__PC)
#define Stepper_Pins_0_DR		(Stepper_Pins__0__DR)
#define Stepper_Pins_0_SHIFT	(Stepper_Pins__0__SHIFT)
#define Stepper_Pins_0_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__0__SHIFT*2u)))

#define Stepper_Pins_1			(Stepper_Pins__1__PC)
#define Stepper_Pins_1_PS		(Stepper_Pins__1__PS)
#define Stepper_Pins_1_PC		(Stepper_Pins__1__PC)
#define Stepper_Pins_1_DR		(Stepper_Pins__1__DR)
#define Stepper_Pins_1_SHIFT	(Stepper_Pins__1__SHIFT)
#define Stepper_Pins_1_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__1__SHIFT*2u)))

#define Stepper_Pins_2			(Stepper_Pins__2__PC)
#define Stepper_Pins_2_PS		(Stepper_Pins__2__PS)
#define Stepper_Pins_2_PC		(Stepper_Pins__2__PC)
#define Stepper_Pins_2_DR		(Stepper_Pins__2__DR)
#define Stepper_Pins_2_SHIFT	(Stepper_Pins__2__SHIFT)
#define Stepper_Pins_2_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__2__SHIFT*2u)))

#define Stepper_Pins_3			(Stepper_Pins__3__PC)
#define Stepper_Pins_3_PS		(Stepper_Pins__3__PS)
#define Stepper_Pins_3_PC		(Stepper_Pins__3__PC)
#define Stepper_Pins_3_DR		(Stepper_Pins__3__DR)
#define Stepper_Pins_3_SHIFT	(Stepper_Pins__3__SHIFT)
#define Stepper_Pins_3_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__3__SHIFT*2u)))

#define Stepper_Pins_4			(Stepper_Pins__4__PC)
#define Stepper_Pins_4_PS		(Stepper_Pins__4__PS)
#define Stepper_Pins_4_PC		(Stepper_Pins__4__PC)
#define Stepper_Pins_4_DR		(Stepper_Pins__4__DR)
#define Stepper_Pins_4_SHIFT	(Stepper_Pins__4__SHIFT)
#define Stepper_Pins_4_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__4__SHIFT*2u)))

#define Stepper_Pins_5			(Stepper_Pins__5__PC)
#define Stepper_Pins_5_PS		(Stepper_Pins__5__PS)
#define Stepper_Pins_5_PC		(Stepper_Pins__5__PC)
#define Stepper_Pins_5_DR		(Stepper_Pins__5__DR)
#define Stepper_Pins_5_SHIFT	(Stepper_Pins__5__SHIFT)
#define Stepper_Pins_5_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__5__SHIFT*2u)))

#define Stepper_Pins_6			(Stepper_Pins__6__PC)
#define Stepper_Pins_6_PS		(Stepper_Pins__6__PS)
#define Stepper_Pins_6_PC		(Stepper_Pins__6__PC)
#define Stepper_Pins_6_DR		(Stepper_Pins__6__DR)
#define Stepper_Pins_6_SHIFT	(Stepper_Pins__6__SHIFT)
#define Stepper_Pins_6_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__6__SHIFT*2u)))

#define Stepper_Pins_7			(Stepper_Pins__7__PC)
#define Stepper_Pins_7_PS		(Stepper_Pins__7__PS)
#define Stepper_Pins_7_PC		(Stepper_Pins__7__PC)
#define Stepper_Pins_7_DR		(Stepper_Pins__7__DR)
#define Stepper_Pins_7_SHIFT	(Stepper_Pins__7__SHIFT)
#define Stepper_Pins_7_INTR	((uint16)((uint16)0x0003u << (Stepper_Pins__7__SHIFT*2u)))

#define Stepper_Pins_INTR_ALL	 ((uint16)(Stepper_Pins_0_INTR| Stepper_Pins_1_INTR| Stepper_Pins_2_INTR| Stepper_Pins_3_INTR| Stepper_Pins_4_INTR| Stepper_Pins_5_INTR| Stepper_Pins_6_INTR| Stepper_Pins_7_INTR))


#endif /* End Pins Stepper_Pins_ALIASES_H */


/* [] END OF FILE */
