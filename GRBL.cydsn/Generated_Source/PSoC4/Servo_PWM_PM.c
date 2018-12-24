/*******************************************************************************
* File Name: Servo_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Servo_PWM.h"

static Servo_PWM_backupStruct Servo_PWM_backup;


/*******************************************************************************
* Function Name: Servo_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Servo_PWM_SaveConfig(void) 
{

    #if(!Servo_PWM_UsingFixedFunction)
        #if(!Servo_PWM_PWMModeIsCenterAligned)
            Servo_PWM_backup.PWMPeriod = Servo_PWM_ReadPeriod();
        #endif /* (!Servo_PWM_PWMModeIsCenterAligned) */
        Servo_PWM_backup.PWMUdb = Servo_PWM_ReadCounter();
        #if (Servo_PWM_UseStatus)
            Servo_PWM_backup.InterruptMaskValue = Servo_PWM_STATUS_MASK;
        #endif /* (Servo_PWM_UseStatus) */

        #if(Servo_PWM_DeadBandMode == Servo_PWM__B_PWM__DBM_256_CLOCKS || \
            Servo_PWM_DeadBandMode == Servo_PWM__B_PWM__DBM_2_4_CLOCKS)
            Servo_PWM_backup.PWMdeadBandValue = Servo_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Servo_PWM_KillModeMinTime)
             Servo_PWM_backup.PWMKillCounterPeriod = Servo_PWM_ReadKillTime();
        #endif /* (Servo_PWM_KillModeMinTime) */

        #if(Servo_PWM_UseControl)
            Servo_PWM_backup.PWMControlRegister = Servo_PWM_ReadControlRegister();
        #endif /* (Servo_PWM_UseControl) */
    #endif  /* (!Servo_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_PWM_RestoreConfig(void) 
{
        #if(!Servo_PWM_UsingFixedFunction)
            #if(!Servo_PWM_PWMModeIsCenterAligned)
                Servo_PWM_WritePeriod(Servo_PWM_backup.PWMPeriod);
            #endif /* (!Servo_PWM_PWMModeIsCenterAligned) */

            Servo_PWM_WriteCounter(Servo_PWM_backup.PWMUdb);

            #if (Servo_PWM_UseStatus)
                Servo_PWM_STATUS_MASK = Servo_PWM_backup.InterruptMaskValue;
            #endif /* (Servo_PWM_UseStatus) */

            #if(Servo_PWM_DeadBandMode == Servo_PWM__B_PWM__DBM_256_CLOCKS || \
                Servo_PWM_DeadBandMode == Servo_PWM__B_PWM__DBM_2_4_CLOCKS)
                Servo_PWM_WriteDeadTime(Servo_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Servo_PWM_KillModeMinTime)
                Servo_PWM_WriteKillTime(Servo_PWM_backup.PWMKillCounterPeriod);
            #endif /* (Servo_PWM_KillModeMinTime) */

            #if(Servo_PWM_UseControl)
                Servo_PWM_WriteControlRegister(Servo_PWM_backup.PWMControlRegister);
            #endif /* (Servo_PWM_UseControl) */
        #endif  /* (!Servo_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Servo_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Servo_PWM_Sleep(void) 
{
    #if(Servo_PWM_UseControl)
        if(Servo_PWM_CTRL_ENABLE == (Servo_PWM_CONTROL & Servo_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            Servo_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Servo_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (Servo_PWM_UseControl) */

    /* Stop component */
    Servo_PWM_Stop();

    /* Save registers configuration */
    Servo_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Servo_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_PWM_Wakeup(void) 
{
     /* Restore registers values */
    Servo_PWM_RestoreConfig();

    if(Servo_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Servo_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
