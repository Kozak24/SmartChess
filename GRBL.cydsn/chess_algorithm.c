#include "smart_chess.h"

char bufferForSpritnf[35];

/* Data sets player - piece. For example 1, 1 is White Player, Rook
Players: 1 - White, 2 - Black, 0 - Empty square
Pieces: 0 - Pawn, 1 - Rook, 2 - Knight, 3 - Bishop, 4 - Queen, 5 - King*/
uint8 chessPositionArray[8][8][2] = {
    { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 3}, {1, 2}, {1, 1} },
    { {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0} }, 
    { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
    { {2, 0}, {2, 0}, {2, 0}, {2, 0}, {2, 0}, {2, 0}, {2, 0}, {2, 0} }, 
    { {2, 1}, {2, 2}, {2, 3}, {2, 5}, {2, 4}, {2, 3}, {2, 2}, {2, 1} },
};

// Array of chess pieces types
const char * chessPiecesTypesArray[6] = {
  "Pawn", "Rook", "Night", "Bishop", "Queen", "King"
};

// Array of chess pieces letters
char chessPiecesLettersArray[6] = {
  'P', 'R', 'N', 'B', 'Q', 'K'
};

// Array of commands for automated testing
const char * commandArray[40] = {
  "a4", "a5", "h4", "h5", "c4", "c5", "d4", "d5",
  "e4", "e5", "f4", "f5", "g4", "g5", "b4", "b5",
  "b5", "b4", "c5", "e4", "e5", "g4", "g5", "Ra4",
  "Ra4", "h4", "c6", "h3", "c7", "Qb5", "b8", "h2",
  "Qd6", "g1", "Nc3", "Nh6", "Ne4", "", "", ""
};

game_info_t game_info;

/*int main(void) {
  UART_Start();
  start_game();

  UART_UartPutString("\n\r--------------------START----------------\n\r");

  print_chess_position_array();
  //Automated testing
  for(int i = 0; i < 37; i++) {
    validate_command(commandArray[i]);
  }
  return 0;
  
  for(;;) {
    UART_UartPutString("Input command: ");
    break;
    //validate_command(command);
  }
}
*/

// When we starting new game we need move all pieces to start position and set WHITE player 
void start_game(void) {
  // TODO ADD CODE BLOCK FOR RETURNING PIECES TO START POSITION
  UART_UartPutString("START GAME\n\n\r");
  game_info.player = 1;
}

uint8 is_coordinates_range_right(char * coordinates) {
    if(coordinates[0] < 'a' || coordinates[0] > 'h') {
        game_info.commandStatus = ERROR_COORDINATES_OUT_OF_RANGE;
        return 0;
    } 
    
    if(coordinates[1] < '1' || coordinates[1] > '8') {
        game_info.commandStatus = ERROR_COORDINATES_OUT_OF_RANGE;
        return 0;
    }
    
    return 1;
}


// Validation of input command 
void validate_command(char * command) {
  game_info.commandStatus = RIGHT_COMMAND;
  sprintf(bufferForSpritnf, "\nPlayer is %d\n\r", game_info.player);
  UART_UartPutString(bufferForSpritnf);
  sprintf(bufferForSpritnf, "Command %s\n\n\r", command);
  UART_UartPutString(bufferForSpritnf);
  // Get piece type
  game_info.pieceType = get_chess_piece_type(command[0]);

  // Check if square is empty. Need for next validation of some chess pieces
  if(0 == strcmp(game_info.pieceType, "Pawn")) {
    if(is_coordinates_range_right(command)) {
        game_info.isSquareEmpty = is_square_empty(command);
    }
  } else {
    char coordinates[2];
    sprintf(coordinates, "%c%c", command[1], command[2]);
    if(is_coordinates_range_right(coordinates)) {
        game_info.isSquareEmpty = is_square_empty(coordinates);
    }
  }

  // Check if destination position piece isn't King
  if(is_destination_piece_king()) {
    game_info.commandStatus = ERROR_DESTINATION_PIECE_IS_KING;
  }

  /* If bad command then quit function and wait for the next command
  in other case find piece */
  for(int validationStep = 0; validationStep < 4; validationStep++) {
    CyBle_ProcessEvents();
    if(game_info.commandStatus != RIGHT_COMMAND) {
      print_error_message();
      return;
    } else {
      /* First step is find a possible coordinate 
      of the piece on the board*/
      if(validationStep == 0) {
        find_piece();
      // Second step is check if is piece on the board
      } else if(validationStep == 1) {
        is_piece_on_the_square();
      // Third step is update chess array and check if Pawn reaches end square
      } else if(validationStep == 2) {
        // Check if Pawn reaches end of the board, if yes then make this piece Queen
        if(0 == strcmp(game_info.pieceType, "Pawn")) {
          if(((game_info.player == WHITE_PLAYER) && game_info.endPosY == 7)
          || ((game_info.player == BLACK_PLAYER) && game_info.endPosY == 0)) {
            pawn_become_queen();
          }
        }
        
        update_chess_array();
      // Forth step is generate GCODE
      } else if(validationStep == 3) {
        // Generate GCODE here
        generate_gcode();
        //Here is problem so do break to exit cycle
        break;
      }
    }
  }

  // Print updated array
  print_chess_position_array();

  // Change player if command is right or leave the same player if command isn't right
  if(game_info.commandStatus == RIGHT_COMMAND) {
    if(game_info.player == WHITE_PLAYER) {
      game_info.player = BLACK_PLAYER;
    } else {
      game_info.player = WHITE_PLAYER;
    }
  }
}

// Update chess array after validation
void update_chess_array(void) {
  // Set end(destination) positions and piece positions for shorter records
  uint8 endPosX = game_info.endPosX;
  uint8 endPosY = game_info.endPosY;
  uint8 piecePosX = game_info.piecePosX;
  uint8 piecePosY = game_info.piecePosY;
  
  // Update position in array
  if(game_info.isSquareEmpty) {
    // Destination square is empty, then we just copy from piece square to destination square
    memcpy(chessPositionArray[endPosY][endPosX], chessPositionArray[piecePosY][piecePosX], 2);
    // And now set 0 values in former piece's square, because square will empty after piece movement
    memset(chessPositionArray[piecePosY][piecePosX], 0, 2);
  } else {
    // There will block to save piece at defeated pieces array
    // TODO Make block to save defeated piece
    
    // Copy data from piece square to destination square
    memcpy(chessPositionArray[endPosY][endPosX], chessPositionArray[piecePosY][piecePosX], 2);
    // And now set 0 values in former piece's square, because square will empty after piece movement
    memset(chessPositionArray[piecePosY][piecePosX], 0, 2);
  }
}

/* When pawn got to other side of board then pawn piece become queen.
Function that changes pawn piece to queen in the chessArray*/
void pawn_become_queen(void) {
  // Assign queen index to the variable and then put it in array
  uint8 queen = 4;
  chessPositionArray[game_info.piecePosY][game_info.piecePosX][PIECE_INDEX] = queen;
}

// Generate GCODE commands
void generate_gcode(void) {
  // Variables for shorter records
  uint8 endPosX = game_info.endPosX;
  uint8 endPosY = game_info.endPosY;
  uint8 piecePosX = game_info.piecePosX;
  uint8 piecePosY = game_info.piecePosY;
    
  sprintf(bufferForSpritnf, "GCODE Commands:\n\r");
  UART_UartPutString(bufferForSpritnf);
  char gcodeCommandBuffer[30];

  /* Check if square isn't empty. If so need to generate 
  GCODE first for defeated piece */
  if( !game_info.isSquareEmpty ) {
    //printf("DEFEATED PIECE\n");
    // Move to defeated piece position
    sprintf(gcodeCommandBuffer, "G01 X%d Y%d F200\n\r", endPosX, endPosY);
    send_command_to_grbl(gcodeCommandBuffer);
    UART_UartPutString(gcodeCommandBuffer);
    // Move platform up

    // Find free slot for defeated piece
    UART_UartPutString("Move to slot t\n\n\r");
    // Move platform down
  }

  UART_UartPutString("PIECE MOVEMENT\n\r");

  // Move to piece position
  sprintf(gcodeCommandBuffer, "G01 X%d Y%d F500\n\r", piecePosX, piecePosY);
  send_command_to_grbl(gcodeCommandBuffer);
  UART_UartPutString(gcodeCommandBuffer);
  sprintf(gcodeCommandBuffer, "G01 A180 X%.2f Y%.2f F500\n\r", piecePosX - 0.01, piecePosY - 0.01);
  send_command_to_grbl(gcodeCommandBuffer);
  UART_UartPutString(gcodeCommandBuffer);

  // Move platform up

  // Move piece to destination position
  const char * piece = game_info.pieceType;
  if (0 == strcmp(piece, "Knight")) {
    // Knight GCODE is special, so he need to has different block
  } else {
    sprintf(gcodeCommandBuffer, "G01 X%d Y%d F200\n\r", endPosX, endPosY);
    send_command_to_grbl(gcodeCommandBuffer);
    UART_UartPutString(gcodeCommandBuffer);
  }
  //Move platform down
  sprintf(gcodeCommandBuffer, "G01 A0 X%.2f Y%.2f F200\n\r", endPosX - 0.01, endPosY - 0.01);
  send_command_to_grbl(gcodeCommandBuffer);
  UART_UartPutString(gcodeCommandBuffer);
  
  /*send_command_to_grbl("G01 X1 Y1 F500\n\r");
  send_command_to_grbl("G01 X19 Y19 F500\n\r");
  send_command_to_grbl("G01 X15 Y15 F200\n\r");*/
}
