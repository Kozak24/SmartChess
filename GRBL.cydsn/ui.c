#include "smart_chess.h"

static char chessCoordinates[8][2] = {
  {'a', '1'},
  {'b', '2'},
  {'c', '3'},
  {'d', '4'},
  {'e', '5'},
  {'f', '6'},
  {'g', '7'},
  {'h', '8'},
};

static const char * error_messages[9] = {
    "No errors\n\r",
    "Piece is ally\n\r",
    "Piece not found\n\r",
    "Non player piece\n\r",
    "Path blocked by enemy\n\r",
    "Path blocked by ally\n\r",
    "Piece type don't match\n\r",
    "Destination piece is KING\n\r",
    "Command coordinates out of range\n\r"
};

void print_error_message(void) {
    sprintf(bufferForSpritnf, "\nERROR CODE %d\n\r", game_info.commandStatus);
    UART_UartPutString(bufferForSpritnf);
    uint8 error_index = game_info.commandStatus - 1;
    const char * error_message = error_messages[error_index];
    UART_UartPutString(error_message);
    //sprintf(bufferForSpritnf, "__________________\n\r");
    //UART_UartPutString(bufferForSpritnf);
}

// Print chess board and all chess pieces position
void print_chess_position_array(void) {
  for(int y = 0; y < 8; y++) {
    UART_UartPutChar(chessCoordinates[y][1]);
    UART_UartPutChar(' ');
    
    for(int x = 0; x < 8; x++) {
      if(EMPTY_SQUARE == chessPositionArray[y][x][PLAYER_INDEX]) {
        UART_UartPutString("[  ]");
      } else {
        UART_UartPutString("[");
        
        // Print player initial w - for White, b - for Black
        if(WHITE_PLAYER == chessPositionArray[y][x][PLAYER_INDEX]) {
            UART_UartPutChar('w');
        } else if(BLACK_PLAYER == chessPositionArray[y][x][PLAYER_INDEX]) {
            UART_UartPutChar('b');
        }
        
        // Print piece initial (first letter)
        UART_UartPutChar(chessPiecesLettersArray[chessPositionArray[y][x][PIECE_INDEX]]);
        
        UART_UartPutString("]");
      }
      UART_UartPutString(" ");
    }
    UART_UartPutString("\r\n");
  }
  UART_UartPutString("  ");
  for(int i = 0; i < 8; i++) {
    sprintf(bufferForSpritnf, "  %c  ", chessCoordinates[i][0]);
    UART_UartPutString(bufferForSpritnf);
  }
  UART_UartPutString("\n\r");
}
