/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef ble_control_h
    #define ble_control_h

#include "project.h"
    
CY_ISR( BLE_Call_Int_Handler );

void readCommand();

void updateCommandStatus();

// Function to process BLE events
void BleCallBack(uint32 event, void* eventParam);
    
// Function that converts BLE command to GCODE
void convert_command_to_gcode();

//Function for validation array
int validate_array();

#endif

/* [] END OF FILE */
