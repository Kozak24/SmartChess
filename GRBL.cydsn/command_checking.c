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

// Function that return type of piece
const char * get_chess_piece_type(char chessPieceLetter) {
  const char * chessPieceType = "NONETYPE";
    for(int i = 0; i < 6; i++) {
      if(chessPieceLetter == chessPiecesLettersArray[i]) {
        chessPieceType = chessPiecesTypesArray[i];
        break;
      }
  }
  if(0 == strcmp(chessPieceType, "NONETYPE")) {
    chessPieceType = "Pawn";
  }
  return chessPieceType;
}

/* Function that checks is destination piece king to avoid
killing of him*/
uint8 is_destination_piece_king(void) {
    uint8 piece = chessPositionArray[game_info.endPosY][game_info.endPosX][PIECE_INDEX];
  if(chessPiecesLettersArray[piece] == 'K') {
    return 1;
  } else {
    return 0;
  }
}

// Check if piece is ally
void is_piece_ally(uint8 * square) {
  if(square[0] == game_info.player) {
    game_info.commandStatus = ERROR_IS_ALLY;
  } else {
    // ?????
  }
}

/* Check if piece is on the square and is it player piece, 
if not then assign to command status error code*/
void is_piece_on_the_square(void) {
  uint8 squareInfo[2]; 
  memcpy(squareInfo, chessPositionArray[game_info.piecePosY][game_info.piecePosX], 2);
  // Check if piece is on the square
  if(EMPTY_SQUARE != squareInfo[PLAYER_INDEX]) {
    if(chessPiecesLettersArray[squareInfo[PIECE_INDEX]] != game_info.pieceType[0]) {
      sprintf(bufferForSpritnf, "Piece on the square is %d\n\r", squareInfo[PIECE_INDEX]);
      UART_UartPutString(bufferForSpritnf);   
      game_info.commandStatus = ERROR_PIECE_TYPE_DON_T_MATCH;
    } else if(squareInfo[PLAYER_INDEX] != game_info.player) {
      game_info.commandStatus = ERROR_NON_PLAYER_S_PIECE;
    }
  // Then square is empty
  } else {
    game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
  }
}

// Function that checks by x y coordinates if square is empty
uint8 is_square_empty(const char * coordinates) {
  // Assign end position X coordinate
  for(int i = 0; i < 8; i++) {
    if(coordinates[0] == chessCoordinates[i][0]) {
      game_info.endPosX = i;
      break;
    }
  }
  // Assign end position Y coordinate
  for(int i = 0; i < 8; i++) {
    if(coordinates[1] == chessCoordinates[i][1]) {
      game_info.endPosY = i;
      break;
    }
  }
  
  //Check if square is empty
  if(EMPTY_SQUARE != chessPositionArray[game_info.endPosY][game_info.endPosX][PLAYER_INDEX]) {
    is_piece_ally(chessPositionArray[game_info.endPosY][game_info.endPosX]);
    return 0;
  } else {
    return 1;
  }
}

/* Checks by string paramater is this piece 
that we are looking for. Return 1 if piece match 
to piece that we searching and 0 if other piece
(ally or enemy) and 2 if square is empty */
uint8 is_piece_found(uint8 * squareInfo) {
  if(EMPTY_SQUARE != squareInfo[PLAYER_INDEX]) {
    // If it's piece that we looking for, then return 1
    if(game_info.player == squareInfo[PLAYER_INDEX]
    && game_info.pieceType[0] == chessPiecesLettersArray[squareInfo[PIECE_INDEX]]) {
      game_info.commandStatus = RIGHT_COMMAND;
      return 1;
    // In this case it's not piece that we looking for and path blocked by ally, then return 0
    } else if(game_info.player == squareInfo[PLAYER_INDEX]) {
      game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
      return 0;
    // In this case it's not piece that we looking for and path blocked by enemy, then return 0
    } else if(game_info.player != squareInfo[PLAYER_INDEX]) {
      game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
      return 0;
    }
  // If square is empty, then return 2
  } else if(0 == squareInfo[PLAYER_INDEX]) {
    game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
    return 2;
  }
  return 0;
}
