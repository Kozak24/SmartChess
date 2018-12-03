/*******************************************************************************
* File Name: BLE_Call_PM.c
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

#include "BLE_Call.h"

static BLE_Call_BACKUP_STRUCT BLE_Call_backup;


/*******************************************************************************
* Function Name: BLE_Call_SaveConfig
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
void BLE_Call_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BLE_Call_Sleep
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
void BLE_Call_Sleep(void)
{
    if(0u != (BLE_Call_BLOCK_CONTROL_REG & BLE_Call_MASK))
    {
        BLE_Call_backup.enableState = 1u;
    }
    else
    {
        BLE_Call_backup.enableState = 0u;
    }

    BLE_Call_Stop();
    BLE_Call_SaveConfig();
}


/*******************************************************************************
* Function Name: BLE_Call_RestoreConfig
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
void BLE_Call_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BLE_Call_Wakeup
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
void BLE_Call_Wakeup(void)
{
    BLE_Call_RestoreConfig();

    if(0u != BLE_Call_backup.enableState)
    {
        BLE_Call_Enable();
    }
}


/* [] END OF FILE */
