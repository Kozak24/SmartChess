/*******************************************************************************
* File Name: Pseudo_Direction_Z.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pseudo_Direction_Z_H) /* Pins Pseudo_Direction_Z_H */
#define CY_PINS_Pseudo_Direction_Z_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pseudo_Direction_Z_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Pseudo_Direction_Z_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Pseudo_Direction_Z_Read(void);
void    Pseudo_Direction_Z_Write(uint8 value);
uint8   Pseudo_Direction_Z_ReadDataReg(void);
#if defined(Pseudo_Direction_Z__PC) || (CY_PSOC4_4200L) 
    void    Pseudo_Direction_Z_SetDriveMode(uint8 mode);
#endif
void    Pseudo_Direction_Z_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pseudo_Direction_Z_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Pseudo_Direction_Z_Sleep(void); 
void Pseudo_Direction_Z_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Pseudo_Direction_Z__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Pseudo_Direction_Z_DRIVE_MODE_BITS        (3)
    #define Pseudo_Direction_Z_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pseudo_Direction_Z_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Pseudo_Direction_Z_SetDriveMode() function.
         *  @{
         */
        #define Pseudo_Direction_Z_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Pseudo_Direction_Z_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Pseudo_Direction_Z_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Pseudo_Direction_Z_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Pseudo_Direction_Z_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Pseudo_Direction_Z_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Pseudo_Direction_Z_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Pseudo_Direction_Z_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Pseudo_Direction_Z_MASK               Pseudo_Direction_Z__MASK
#define Pseudo_Direction_Z_SHIFT              Pseudo_Direction_Z__SHIFT
#define Pseudo_Direction_Z_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pseudo_Direction_Z_SetInterruptMode() function.
     *  @{
     */
        #define Pseudo_Direction_Z_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Pseudo_Direction_Z_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Pseudo_Direction_Z_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Pseudo_Direction_Z_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Pseudo_Direction_Z__SIO)
    #define Pseudo_Direction_Z_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Pseudo_Direction_Z__PC) && (CY_PSOC4_4200L)
    #define Pseudo_Direction_Z_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Pseudo_Direction_Z_USBIO_DISABLE              ((uint32)(~Pseudo_Direction_Z_USBIO_ENABLE))
    #define Pseudo_Direction_Z_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Pseudo_Direction_Z_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Pseudo_Direction_Z_USBIO_ENTER_SLEEP          ((uint32)((1u << Pseudo_Direction_Z_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Pseudo_Direction_Z_USBIO_SUSPEND_DEL_SHIFT)))
    #define Pseudo_Direction_Z_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Pseudo_Direction_Z_USBIO_SUSPEND_SHIFT)))
    #define Pseudo_Direction_Z_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Pseudo_Direction_Z_USBIO_SUSPEND_DEL_SHIFT)))
    #define Pseudo_Direction_Z_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Pseudo_Direction_Z__PC)
    /* Port Configuration */
    #define Pseudo_Direction_Z_PC                 (* (reg32 *) Pseudo_Direction_Z__PC)
#endif
/* Pin State */
#define Pseudo_Direction_Z_PS                     (* (reg32 *) Pseudo_Direction_Z__PS)
/* Data Register */
#define Pseudo_Direction_Z_DR                     (* (reg32 *) Pseudo_Direction_Z__DR)
/* Input Buffer Disable Override */
#define Pseudo_Direction_Z_INP_DIS                (* (reg32 *) Pseudo_Direction_Z__PC2)

/* Interrupt configuration Registers */
#define Pseudo_Direction_Z_INTCFG                 (* (reg32 *) Pseudo_Direction_Z__INTCFG)
#define Pseudo_Direction_Z_INTSTAT                (* (reg32 *) Pseudo_Direction_Z__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Pseudo_Direction_Z_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Pseudo_Direction_Z__SIO)
    #define Pseudo_Direction_Z_SIO_REG            (* (reg32 *) Pseudo_Direction_Z__SIO)
#endif /* (Pseudo_Direction_Z__SIO_CFG) */

/* USBIO registers */
#if !defined(Pseudo_Direction_Z__PC) && (CY_PSOC4_4200L)
    #define Pseudo_Direction_Z_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Pseudo_Direction_Z_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Pseudo_Direction_Z_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Pseudo_Direction_Z_DRIVE_MODE_SHIFT       (0x00u)
#define Pseudo_Direction_Z_DRIVE_MODE_MASK        (0x07u << Pseudo_Direction_Z_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Pseudo_Direction_Z_H */


/* [] END OF FILE */
