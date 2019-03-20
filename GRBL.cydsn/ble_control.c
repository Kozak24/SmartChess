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

#include "project.h"
#include "grbl.h"
#include "stdio.h"

uint8 commandArrayLength = 5;
uint8 commandArray[5];

uint8 counter;

void readCommand()
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return;
    }

    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_COMMAND_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &commandArray;
    tempHandle.value.len = 5;
    CyBle_GattsReadAttributeValue(&tempHandle, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
}


int validate_array()
{
    int status = 0;
    if(commandArray[0] >= 65 && commandArray[0] <= 72
       && commandArray[3] >= 65 && commandArray[3] <= 72) {
        status = 1;
    } else {
        status = 0;
    }
    
    if(commandArray[1] >= 49 && commandArray[1] <= 56
       && commandArray[4] >= 49 && commandArray[4] <= 56) {
        status = 1;
    } else {
        status = 0;
    }
       
    return status;    
}

void convert_command_to_gcode()
{    
    char buffer[2];
    
    CyBle_ProcessEvents();
    switch(commandArray[0]) {
        case 'a':
            buffer[0] = '1';
            break;
        case 'b':
            buffer[0] = '2';
            break;
        case 'c':
            buffer[0] = '3';
            break;
        case 'd':
            buffer[0] = '4';
            break;
        case 'e':
            buffer[0] = '5';
            break;
        case 'f':
            buffer[0] = '6';
            break;
        case 'g':
            buffer[0] = '7';
            break;
        case 'h':
            buffer[0] = '8';
            break;
        default:
            buffer[0] = '0';
            break;
    }
    
    buffer[1] = commandArray[1];
    
    char commandBuffer[20];
    
    sprintf(commandBuffer, "G01 X1%c Y1%c F500\r\n", buffer[0], buffer[1]);
    //sprintf(commandBuffer, "G01 X10 Y10 F500\r\n");
    
    counter++;
    
    /*if(counter == 1) {
        sprintf(commandBuffer, "G01 X10 Y10 F500\r\n");
    } else if(counter == 2) {
        sprintf(commandBuffer, "G01 X11 Y11 F500\r\n");
        counter = 0;
    }*/
    UART_UartPutString(commandBuffer);
    
    for(uint8 i = 0; i < sizeof(commandBuffer); i++) {
        process_ble_data(commandBuffer[i]);
    }
}

void BleCallBack(uint32 event, void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch(event)
    {
        /* if there is a disconnect or the stack just turned on
        from a reset then*/
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            BLE_Status_Pin_Write(0);
        break;
            
        /* when a connection is made, update the LED and Capsense
        states in the GATT database*/
        case CYBLE_EVT_GATT_CONNECT_IND:
            //readCommand();
            BLE_Status_Pin_Write(1);
        break;
        
        /*handle a write request */
        case CYBLE_EVT_GATTS_WRITE_REQ:     
            wrReqParam = (CYBLE_GATTS_WRITE_CMD_REQ_PARAM_T *) eventParam;
            /* if request write the Chess Letter value */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_COMMAND_CHAR_HANDLE)
            {
                /*only update the value and write the response if the requested write is allowed*/
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    uint8 length = wrReqParam->handleValPair.value.len;
                    //readCommand();
                    for(uint8 i = 0; i < length; i++) {
                        if(i < (sizeof(commandArray)/sizeof(uint8) ) )
                            commandArray[i] = wrReqParam->handleValPair.value.val[i];
                        else if(i > (sizeof(commandArray)/sizeof(uint8)) )
                            break;
                    }
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                    
                    convert_command_to_gcode();
                }
            }
            break;
        
        default:
            break;
    }
}

/* [] END OF FILE */
