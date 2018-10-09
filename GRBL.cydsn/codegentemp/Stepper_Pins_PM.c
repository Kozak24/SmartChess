/*******************************************************************************
* File Name: Stepper_Pins.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Stepper_Pins.h"

static Stepper_Pins_BACKUP_STRUCT  Stepper_Pins_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Stepper_Pins_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Stepper_Pins_SUT.c usage_Stepper_Pins_Sleep_Wakeup
*******************************************************************************/
void Stepper_Pins_Sleep(void)
{
    #if defined(Stepper_Pins__PC)
        Stepper_Pins_backup.pcState = Stepper_Pins_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Stepper_Pins_backup.usbState = Stepper_Pins_CR1_REG;
            Stepper_Pins_USB_POWER_REG |= Stepper_Pins_USBIO_ENTER_SLEEP;
            Stepper_Pins_CR1_REG &= Stepper_Pins_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Stepper_Pins__SIO)
        Stepper_Pins_backup.sioState = Stepper_Pins_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Stepper_Pins_SIO_REG &= (uint32)(~Stepper_Pins_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Stepper_Pins_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Stepper_Pins_Sleep() for an example usage.
*******************************************************************************/
void Stepper_Pins_Wakeup(void)
{
    #if defined(Stepper_Pins__PC)
        Stepper_Pins_PC = Stepper_Pins_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Stepper_Pins_USB_POWER_REG &= Stepper_Pins_USBIO_EXIT_SLEEP_PH1;
            Stepper_Pins_CR1_REG = Stepper_Pins_backup.usbState;
            Stepper_Pins_USB_POWER_REG &= Stepper_Pins_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Stepper_Pins__SIO)
        Stepper_Pins_SIO_REG = Stepper_Pins_backup.sioState;
    #endif
}


/* [] END OF FILE */
