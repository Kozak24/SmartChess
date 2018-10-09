/*******************************************************************************
* File Name: Limit_Pins.h  
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

#if !defined(CY_PINS_Limit_Pins_ALIASES_H) /* Pins Limit_Pins_ALIASES_H */
#define CY_PINS_Limit_Pins_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Limit_Pins_0			(Limit_Pins__0__PC)
#define Limit_Pins_0_PS		(Limit_Pins__0__PS)
#define Limit_Pins_0_PC		(Limit_Pins__0__PC)
#define Limit_Pins_0_DR		(Limit_Pins__0__DR)
#define Limit_Pins_0_SHIFT	(Limit_Pins__0__SHIFT)
#define Limit_Pins_0_INTR	((uint16)((uint16)0x0003u << (Limit_Pins__0__SHIFT*2u)))

#define Limit_Pins_1			(Limit_Pins__1__PC)
#define Limit_Pins_1_PS		(Limit_Pins__1__PS)
#define Limit_Pins_1_PC		(Limit_Pins__1__PC)
#define Limit_Pins_1_DR		(Limit_Pins__1__DR)
#define Limit_Pins_1_SHIFT	(Limit_Pins__1__SHIFT)
#define Limit_Pins_1_INTR	((uint16)((uint16)0x0003u << (Limit_Pins__1__SHIFT*2u)))

#define Limit_Pins_2			(Limit_Pins__2__PC)
#define Limit_Pins_2_PS		(Limit_Pins__2__PS)
#define Limit_Pins_2_PC		(Limit_Pins__2__PC)
#define Limit_Pins_2_DR		(Limit_Pins__2__DR)
#define Limit_Pins_2_SHIFT	(Limit_Pins__2__SHIFT)
#define Limit_Pins_2_INTR	((uint16)((uint16)0x0003u << (Limit_Pins__2__SHIFT*2u)))

#define Limit_Pins_3			(Limit_Pins__3__PC)
#define Limit_Pins_3_PS		(Limit_Pins__3__PS)
#define Limit_Pins_3_PC		(Limit_Pins__3__PC)
#define Limit_Pins_3_DR		(Limit_Pins__3__DR)
#define Limit_Pins_3_SHIFT	(Limit_Pins__3__SHIFT)
#define Limit_Pins_3_INTR	((uint16)((uint16)0x0003u << (Limit_Pins__3__SHIFT*2u)))

#define Limit_Pins_4			(Limit_Pins__4__PC)
#define Limit_Pins_4_PS		(Limit_Pins__4__PS)
#define Limit_Pins_4_PC		(Limit_Pins__4__PC)
#define Limit_Pins_4_DR		(Limit_Pins__4__DR)
#define Limit_Pins_4_SHIFT	(Limit_Pins__4__SHIFT)
#define Limit_Pins_4_INTR	((uint16)((uint16)0x0003u << (Limit_Pins__4__SHIFT*2u)))

#define Limit_Pins_5			(Limit_Pins__5__PC)
#define Limit_Pins_5_PS		(Limit_Pins__5__PS)
#define Limit_Pins_5_PC		(Limit_Pins__5__PC)
#define Limit_Pins_5_DR		(Limit_Pins__5__DR)
#define Limit_Pins_5_SHIFT	(Limit_Pins__5__SHIFT)
#define Limit_Pins_5_INTR	((uint16)((uint16)0x0003u << (Limit_Pins__5__SHIFT*2u)))

#define Limit_Pins_INTR_ALL	 ((uint16)(Limit_Pins_0_INTR| Limit_Pins_1_INTR| Limit_Pins_2_INTR| Limit_Pins_3_INTR| Limit_Pins_4_INTR| Limit_Pins_5_INTR))


#endif /* End Pins Limit_Pins_ALIASES_H */


/* [] END OF FILE */
