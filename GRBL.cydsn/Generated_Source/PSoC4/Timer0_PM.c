/*******************************************************************************
* File Name: Timer0_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Timer0.h"

static Timer0_BACKUP_STRUCT Timer0_backup;


/*******************************************************************************
* Function Name: Timer0_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer0_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Timer0_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer0_Sleep(void)
{
    if(0u != (Timer0_BLOCK_CONTROL_REG & Timer0_MASK))
    {
        Timer0_backup.enableState = 1u;
    }
    else
    {
        Timer0_backup.enableState = 0u;
    }

    Timer0_Stop();
    Timer0_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer0_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer0_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Timer0_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer0_Wakeup(void)
{
    Timer0_RestoreConfig();

    if(0u != Timer0_backup.enableState)
    {
        Timer0_Enable();
    }
}


/* [] END OF FILE */
