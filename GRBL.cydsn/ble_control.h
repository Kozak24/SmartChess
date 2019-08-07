#ifndef BLE_CONTROL_H
    #define BLE_CONTROL_H

#include "project.h"
    
extern uint8 isNewCommand;
extern char inputCommand[5];

enum CommandCondition {
    OLD, NEW
};
    
enum NotificationIndices {
  COMMAND_STATUS_NOTIFICATION, PLAYER_NOTIFICATION, COMMAND_PROGRESS_NOTIFICATION
};

CY_ISR( BLE_Call_Int_Handler );

void updateGameInformation(void);

void updateCommandProgress(void);

// Function to process BLE events
void BleCallBack(uint32 event, void* eventParam);

void send_command_to_grbl(char * buffer);

#endif

/* [] END OF FILE */
