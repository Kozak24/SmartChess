#ifndef ble_control_h
    #define ble_control_h

#include "project.h"
    
#define COMMAND_STATUS_NOTIFICATION (0)
#define PLAYER_NOTIFICATION         (1)
    
CY_ISR( BLE_Call_Int_Handler );

void readCommand(void);

void updateCommandStatus(void);

void updatePlayer(void);

void updateGameInformation(void);

void updateCommandProgress(void);

// Function to process BLE events
void BleCallBack(uint32 event, void* eventParam);

void send_command_to_grbl(char * buffer);

#endif

/* [] END OF FILE */
