#include "smart_chess.h"

uint8 inputCommand[5];

void readCommand()
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return;
    }

    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_COMMAND_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &inputCommand;
    tempHandle.value.len = 5;
    CyBle_GattsReadAttributeValue(&tempHandle, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
}

void updateCommandStatus(void) {
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return;
    }

    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_COMMANDSTATUS_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &game_info.commandStatus;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
}

void updataPlayer(void) {
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return;
    }

    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_PLAYER_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &game_info.player;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
}

void updateGameInformation(void) {
    updateCommandStatus();
    updataPlayer();
}

void send_command_to_grbl(char * buffer) {
    uint8 length = strlen(buffer);
    for(uint8 i = 0; i < length; i++) {
        process_ble_data(buffer[i]);
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
            BLE_Status_Pin_Write(1);
            updateGameInformation();
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
                    for(uint8 i = 0; i < length; i++) {
                        inputCommand[i] = wrReqParam->handleValPair.value.val[i];
                    }
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                    char command[4];
                    sprintf(command, "%c%c%c", inputCommand[0], inputCommand[1], inputCommand[2]);
                    validate_command(command);
                    updateGameInformation();
                }
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_STARTGAME_CHAR_HANDLE)
            {
                /*only update the value and write the response if the requested write is allowed*/
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    if(wrReqParam->handleValPair.value.val[0] == START_GAME) {
                        start_game();
                    }
                    
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                    updateGameInformation();
                }
            }
            break;
        
        default:
            break;
    }
}

/* [] END OF FILE */
