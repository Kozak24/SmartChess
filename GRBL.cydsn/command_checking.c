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

// Function that return index of piece
uint8 get_piece_index_from_letter(char chessPieceLetter) {
    uint8 pieceIndex = 0;
    for(int i = 0; i < 6; i++) {
      if(chessPieceLetter == chessPiecesLettersArray[i]) {
        pieceIndex = i;
        break;
      }
  }
    
  return pieceIndex;
}

/* Function that checks is destination piece king to avoid
killing of him*/
uint8 is_destination_piece_king(void) {
  uint8 piece = chessPositionArray[game_info.endPosY][game_info.endPosX];
  if(chessPiecesLettersArray[get_piece_index(piece)] == 'K') {
    return 1;
  } else {
    return 0;
  }
}

// Check if piece is ally
void is_piece_ally(uint8 square) {
  if(get_player(square) == game_info.player) {
    game_info.commandStatus = ERROR_IS_ALLY;
  }
}

/* Check if piece is on the square and is it player piece, 
if not then assign to command status error code*/
void is_piece_on_the_square(void) {
  uint8 squareInfo = chessPositionArray[game_info.piecePosY][game_info.piecePosX];
  // Check if piece is on the square
  if(EMPTY_SQUARE != squareInfo) {
    if(get_player(squareInfo) != game_info.player) {
      game_info.commandStatus = ERROR_NON_PLAYER_S_PIECE;
    } else if(chessPiecesLettersArray[get_piece_index(squareInfo)] != game_info.pieceType[FIRST_LETTER]) {
      sprintf(bufferForSpritnf, "Piece on the square is %d\n\r", get_piece_index(squareInfo));
      UART_UartPutString(bufferForSpritnf);   
      game_info.commandStatus = ERROR_PIECE_TYPE_DON_T_MATCH;
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
  if(EMPTY_SQUARE != chessPositionArray[game_info.endPosY][game_info.endPosX]) {
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
uint8 is_piece_found(uint8 squareInfo) {
  if(EMPTY_SQUARE != squareInfo) {
    // If it's piece that we looking for, then return 1
    if(game_info.player == get_player(squareInfo)
    && game_info.pieceType[FIRST_LETTER] == chessPiecesLettersArray[get_piece_index(squareInfo)]) {
      game_info.commandStatus = RIGHT_COMMAND;
      return 1;
    // In this case it's not piece that we looking for and path blocked by ally, then return 0
    } else if(game_info.player == get_player(squareInfo)) {
      game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
      return 0;
    // In this case it's not piece that we looking for and path blocked by enemy, then return 0
    } else if(game_info.player != get_player(squareInfo)) {
      game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
      return 0;
    }
  // If square is empty, then return 2
  } else if(EMPTY_SQUARE == squareInfo) {
    game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
    return 2;
  }
  return 0;
}

// Function that return piece index
uint8 get_piece_index(uint8 piece) {
  // Substract 1 because the array indices begin from 0
  return (piece & 0b0111) - 1;
}

// Function that return player
uint8 get_player(uint8 piece) {
  return piece & 0b10000000;
}

// Function that return piece type
uint8 get_piece_type(uint8 piece) {
    return piece & 0b0111;
}
