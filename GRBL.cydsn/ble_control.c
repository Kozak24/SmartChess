#include "smart_chess.h"

uint8 isNewCommand;
char inputCommand[5];

// Array keeps notification value of characteristic. 0 - DISABLED, 1 - ENABLED;
static uint8 notificationsArray[3];

static void readCommand(void) {
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_COMMAND_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &inputCommand;
    tempHandle.value.len = 5;
    CyBle_GattsReadAttributeValue(&tempHandle, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
}

static void updateCommandStatus(void) {
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_COMMANDSTATUS_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &game_info.commandStatus;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    
    if(notificationsArray[COMMAND_STATUS_NOTIFICATION]) {
        CyBle_GattsNotification(cyBle_connHandle, &tempHandle);
    }
}

static void updatePlayer(void) {
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_PLAYER_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) &game_info.player;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);

    if(notificationsArray[PLAYER_NOTIFICATION]) {
        CyBle_GattsNotification(cyBle_connHandle, &tempHandle);
    }
}

void updateCommandProgress(void) {
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    // Temporary array for test
    uint8 tempArray[2] = { 3, 13 };
    
    tempHandle.attrHandle = CYBLE_SMARTCHESS_COMMANDPROGRESS_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *) tempArray;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    
    if(notificationsArray[COMMAND_PROGRESS_NOTIFICATION]) {
        CyBle_GattsNotification(cyBle_connHandle, &tempHandle);
    }
}

void updateGameInformation(void) {
    updateCommandStatus();
    updatePlayer();
    updateCommandProgress();
}

void send_command_to_grbl(char * buffer) {
    uint8 length = strlen(buffer);
    for(uint8 i = 0; i < length; i++) {
        process_ble_data(buffer[i]);
    }
}

void BleCallBack(uint32 event, void* eventParam) {
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch(event) {
        /* if there is a disconnect or the stack just turned on
        from a reset then*/
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            BLE_Status_Pin_Write(0);
        break;
            
        /* when a connection is made, update Game information in the GATT database*/
        case CYBLE_EVT_GATT_CONNECT_IND:
            BLE_Status_Pin_Write(1);
            updateGameInformation();
        break;
        
        /*handle a write request */
        case CYBLE_EVT_GATTS_WRITE_REQ:     
            wrReqParam = (CYBLE_GATTS_WRITE_CMD_REQ_PARAM_T *) eventParam;
            
            /* Get chess command from Client */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_COMMAND_CHAR_HANDLE) {
                /*only update the value and write the response if the requested write is allowed*/
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED)) {
                    uint8 length = wrReqParam->handleValPair.value.len;
                    for(uint8 i = 0; i < length; i++) {
                        inputCommand[i] = wrReqParam->handleValPair.value.val[i];
                    }
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                    
                    isNewCommand = NEW;
                }
            }
            
            /* request to Start Game or Restart */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_STARTGAME_CHAR_HANDLE) {
                /*only update the value and write the response if the requested write is allowed*/
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED)) {
                    if(wrReqParam->handleValPair.value.val[0] == STARTED_GAME) {
                        start_game();
                    }
                    
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                    updateGameInformation();
                }
            }
            
            /*request to update the CommandStatus notification */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_COMMANDSTATUS_COMMANDSTATUSNOTIFICATION_DESC_HANDLE) {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                notificationsArray[COMMAND_STATUS_NOTIFICATION] = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            
            /*request to update the Player notification */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_PLAYER_PLAYERNOTIFICATION_DESC_HANDLE) {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                notificationsArray[PLAYER_NOTIFICATION] = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            break;
            
            /*request to update the CommandProgress notification */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SMARTCHESS_COMMANDPROGRESS_COMMANDPROGRESSNOTIFICATION_DESC_HANDLE) {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                notificationsArray[COMMAND_PROGRESS_NOTIFICATION] = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
            break;
        
        default:
            break;
    }
}

/* [] END OF FILE */
