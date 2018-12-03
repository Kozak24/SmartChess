/*******************************************************************************
* File Name: TempTimer_PM.c
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

#include "TempTimer.h"

static TempTimer_BACKUP_STRUCT TempTimer_backup;


/*******************************************************************************
* Function Name: TempTimer_SaveConfig
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
void TempTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TempTimer_Sleep
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
void TempTimer_Sleep(void)
{
    if(0u != (TempTimer_BLOCK_CONTROL_REG & TempTimer_MASK))
    {
        TempTimer_backup.enableState = 1u;
    }
    else
    {
        TempTimer_backup.enableState = 0u;
    }

    TempTimer_Stop();
    TempTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: TempTimer_RestoreConfig
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
void TempTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TempTimer_Wakeup
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
void TempTimer_Wakeup(void)
{
    TempTimer_RestoreConfig();

    if(0u != TempTimer_backup.enableState)
    {
        TempTimer_Enable();
    }
}


/* [] END OF FILE */
