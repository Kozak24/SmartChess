#include "smart_chess.h"

// Find piece by the piece type
void find_piece(void) {
  if(0 == strcmp(game_info.pieceType, "Pawn")) {
    find_pawn();
  } else if(0 == strcmp(game_info.pieceType, "Rook")) {
    find_by_horizontal();
    find_by_vertical();
  } else if(0 == strcmp(game_info.pieceType, "Night")) {
    find_knight();
  } else if(0 == strcmp(game_info.pieceType, "Bishop")) {
    find_by_diagonal();
  } else if(0 == strcmp(game_info.pieceType, "King")) {
    // Find King
  } else if(0 == strcmp(game_info.pieceType, "Queen")) {
    find_by_diagonal();
    find_by_horizontal();
    find_by_vertical();
  }
}

// Function that find knight by 8 possible points from destination position
void find_knight(void) {
    uint8 endPosY = game_info.endPosY;
    uint8 endPosX = game_info.endPosX;
    uint8 player = game_info.player;
    
    //  In this condition we check is lower points within chess board 
    if(endPosY - KNIGHT_OFFSET_Y >= Y_COORDINATE_MIN) {
        if(endPosX - KNIGHT_HALF_OFFSET_X >= X_COORDINATE_MIN) {
            if(chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX - KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_OFFSET_Y;
                return;
            }
        }
        
        if(endPosX + KNIGHT_HALF_OFFSET_X <= X_COORDINATE_MAX) {
            if(chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX + KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_OFFSET_Y;
                return;
            }
        }
    }
    //  In this condition we check is upper points within chess board 
    if(endPosY + KNIGHT_OFFSET_Y <= Y_COORDINATE_MAX) {
        if(endPosX - KNIGHT_HALF_OFFSET_X >= X_COORDINATE_MIN) {
            if(chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX - KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_OFFSET_Y;
                return;
            }
        }
        
        if(endPosX + KNIGHT_HALF_OFFSET_X <= X_COORDINATE_MAX) {
            if(chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX + KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_OFFSET_Y;
                return;
            }
        }
    }
    //  In this condition we check is left points within chess board
    if(endPosX - KNIGHT_OFFSET_X >= X_COORDINATE_MIN) {
        if(endPosY - KNIGHT_HALF_OFFSET_Y >= Y_COORDINATE_MIN) {
            if(chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX - KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
        
        if(endPosY + KNIGHT_HALF_OFFSET_Y <= Y_COORDINATE_MAX) {
            if(chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX - KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
    }
    //  In this condition we check is right points within chess board
    if(endPosX + KNIGHT_OFFSET_X <= X_COORDINATE_MAX) {
        if(endPosY - KNIGHT_HALF_OFFSET_Y >= Y_COORDINATE_MIN) {
            if(chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX + KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
        
        if(endPosY + KNIGHT_HALF_OFFSET_Y <= Y_COORDINATE_MAX) {
            if(chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X][PIECE_INDEX] == KNIGHT_PIECE
            && chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X][PLAYER_INDEX] == player) {
                game_info.piecePosX = endPosX + KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
    }
    game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
}

// Function that find by diagonal path
void find_by_diagonal(void) {
  int destinationX = game_info.endPosX;
  int destinationY = game_info.endPosY;
  // Left upper diagonal path and Left downer diagonal path
  if(destinationX != X_COORDINATE_MAX) {
    int y = destinationY;
    // Left upper diagonal path
    for(int x = destinationX + 1; x < 8; x++) {
      y += 1;
        
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - break cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }

      if(x == X_COORDINATE_MAX || y == Y_COORDINATE_MAX) {
        break;
      }
    }

    y = destinationY;
    // Left downer diagonal path
    for(int x = destinationX + 1; x < 8; x++) {
      y -= 1;
        
      uint8 squareInfo[2];
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - break cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }

      if(x == X_COORDINATE_MAX || y == Y_COORDINATE_MIN) {
        break;
      }
    }
  }

  // Right downer diagonal path and Right upper diagonal path
  if(destinationX != X_COORDINATE_MIN) {
    int y = destinationY;
    // Right downer diagonal path
    for(int x = destinationX - 1; x >= 0; x--) {
      y -= 1;
        
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - break cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }

      if(x == X_COORDINATE_MIN || y == Y_COORDINATE_MIN) {
        break;
      }
    }

    y = destinationY;
    // Right upper diagonal path
    for(int x = destinationX - 1; x >= 0; x--) {
      y += 1;
      
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - break cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }

      if(x == X_COORDINATE_MIN || y == Y_COORDINATE_MAX) {
        break;
      }
    }
  }
}

// Function that find piece by horizontal path
void find_by_horizontal(void) {
  int destinationX = game_info.endPosX;
  int destinationY = game_info.endPosY;

  // Check if piece is already found
  if(0 == strcmp(game_info.pieceType, "Queen")) {
    int x = game_info.piecePosX;
    int y = game_info.piecePosY;
    
    uint8 squareInfo[2]; 
    memcpy(squareInfo, chessPositionArray[y][x], 2);
    
    // If piece is already found, then return
    if(chessPiecesLettersArray[squareInfo[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
      return;
    }
  }

  // Path to right from destination position
  if(destinationX != X_COORDINATE_MAX) {
    int y = destinationY;

    for(int x = destinationX + 1; x < 8; x++) {
        
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }
    }
  }

  // Path to left from destination position
  if(destinationX != X_COORDINATE_MIN) {
    int y = destinationY;
    
    for(int x = destinationX - 1; x >= 0; x--) {
      
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }
    }
  }
}

// Function that find piece by vertical path
void find_by_vertical(void) {
  int destinationX = game_info.endPosX;
  int destinationY = game_info.endPosY;

  // Check if piece is already found
  if(0 == strcmp(game_info.pieceType, "Queen")
  || 0 == strcmp(game_info.pieceType, "Rook")) {
    int x = game_info.piecePosX;
    int y = game_info.piecePosY;
    
    uint8 squareInfo[2]; 
    memcpy(squareInfo, chessPositionArray[y][x], 2);
    
    // If piece is already found, then return
    if(chessPiecesLettersArray[squareInfo[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
      return;
    }
  }

  if(destinationY != Y_COORDINATE_MAX) {
    int x = destinationX;
    
    // Path from destination position to upper side
    for(int y = destinationY + 1; y < 8; y++) {
        
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }
    }
  }

  if(destinationY != Y_COORDINATE_MIN) {
    int x = destinationX;

    // Path from destination position to downer side
    for(int y = destinationY - 1; y >= 0; y--) {
        
      uint8 squareInfo[2]; 
      memcpy(squareInfo, chessPositionArray[y][x], 2);

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }
    }
  }
}

// Fucntion that find Pawn on the chess board
void find_pawn(void) {
  uint8 player = game_info.player;
  int destinationY = game_info.endPosY;
  int destinationX = game_info.endPosX;

  if(game_info.isSquareEmpty) {
    game_info.piecePosX = destinationX;

    /* At the start square Pawn can move 2 square forward
    if player want this */
    if((3 == destinationY && WHITE_PLAYER == player)
    || (destinationY == 4 && BLACK_PLAYER == player)) {
      // Y positions of bottom and top squares
      int bottomPosY = 0;
      int topPosY = 0;
      // Set bottom and top square
      if(WHITE_PLAYER == player) {
        bottomPosY = 1;
        topPosY = 2;
      } else if(BLACK_PLAYER == player) {
        bottomPosY = 6;
        topPosY = 5;
      }

      // Bottom piece coordinates is [a-h]2 for white or [a-h]7 for black
      uint8 bottomSquare[2];
      memcpy(bottomSquare, chessPositionArray[bottomPosY][destinationX], 2);
      // Top piece coordinates is [a-h]3 for white or [a-h]6 for black
      uint8 topSquare[2];
      memcpy(topSquare, chessPositionArray[topPosY][destinationX], 2);  

      if((EMPTY_SQUARE != bottomSquare[PLAYER_INDEX]) 
      && (EMPTY_SQUARE != topSquare[PLAYER_INDEX])) {
        // If at top square is enemy then path is blocked
        if(topSquare[PLAYER_INDEX] != player 
        && bottomSquare[PLAYER_INDEX] == player) {
          game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
        /* If at top square is player's, then it's possible Pawn
        this'll be checked in second step of validation */
        } else if(topSquare[PLAYER_INDEX] == player
        && bottomSquare[PLAYER_INDEX] == player) {
          // If top square piece isn't Pawn then error
          if(chessPiecesLettersArray[topSquare[PIECE_INDEX]] != game_info.pieceType[FIRST_LETTER]) {
            game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
          } else {
            game_info.piecePosY = topPosY;
          }
        }
      // If both bottom and top squares is empty then no piece found
      } else if((EMPTY_SQUARE == bottomSquare[PLAYER_INDEX]) 
      && (EMPTY_SQUARE == topSquare[PLAYER_INDEX])) {
        game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
      /* If bottom square isn't empty and top square is empty
      then bottom square is possible position of Pawn */
      } else if((EMPTY_SQUARE != bottomSquare[PLAYER_INDEX]) 
      && (EMPTY_SQUARE == topSquare[PLAYER_INDEX])) {
        if(bottomSquare[PLAYER_INDEX] == player
        && chessPiecesLettersArray[bottomSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
          game_info.piecePosY = bottomPosY;
        } else {
          game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
        }
      /* If bottom square is empty and top square isn't empty
      then top square is possible position of Pawn */
      } else if((EMPTY_SQUARE == bottomSquare[PLAYER_INDEX]) 
      && (EMPTY_SQUARE != topSquare[PLAYER_INDEX])) {
        if(topSquare[PLAYER_INDEX] == player
        && chessPiecesLettersArray[topSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
          game_info.piecePosY = topPosY;
        } else {
          game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
        }
      }
    /* In this case piece position for white player is 
    destinationY position - 1 and for black player is
    destinatonY position + 1*/
    } else if((destinationY > 1 && WHITE_PLAYER == player) 
    || (destinationY < 6 && BLACK_PLAYER == player)) {
      if(WHITE_PLAYER == player) {
        game_info.piecePosY = destinationY - 1;
      } else if(BLACK_PLAYER == player) {
        game_info.piecePosY = destinationY + 1;
      }
    }
  // If square isn't empty
  } else {
    /* Calculate offset for Y coordinate of Pawn. Just add 1 to 
    Y coordinate if black or substract 1 if white player */
    if(WHITE_PLAYER == player) {
      game_info.piecePosY = destinationY - 1;
    } else if(BLACK_PLAYER == player) {
      game_info.piecePosY = destinationY + 1;
    }

    /* When Pawn attacks he can be only to the right of enemy piece
    or to the left of enemy piece */
    if(destinationX > X_COORDINATE_MIN && destinationX < X_COORDINATE_MAX) {

      /* For black player left piece will on another side
      than white player left piece, so declare here offset
      that will change his value along with changing player*/
      int offsetX = 0;
      if(WHITE_PLAYER == player) {
        offsetX = -1;
      } else if(BLACK_PLAYER == player) {
        offsetX = 1;
      }

      uint8 leftSquare[2];
      memcpy(leftSquare, chessPositionArray[game_info.piecePosY][destinationX - offsetX], 2);
      uint8 rightSquare[2];
      memcpy(rightSquare, chessPositionArray[game_info.piecePosY][destinationX + offsetX], 2);

      /* Check if both left and right square isn't empty if not
      then check if left isn't empty if not
      then check if right isn't empty */
      if((EMPTY_SQUARE != rightSquare[PLAYER_INDEX]) 
      && (EMPTY_SQUARE != leftSquare[PLAYER_INDEX])) {
        // If it's not player piece 
        if(leftSquare[PLAYER_INDEX] != player 
        && rightSquare[PLAYER_INDEX] != player) {
          game_info.commandStatus = ERROR_NON_PLAYER_S_PIECE;
        /* If leftSquare isn't player piece, 
        then rightSquare is a possible position of piece */
        } else if (leftSquare[PLAYER_INDEX] != player) {
          if(rightSquare[PLAYER_INDEX] == player 
          && chessPiecesLettersArray[rightSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
            game_info.piecePosX = destinationX + offsetX;
          } else {
            game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
          }
        /* If rightSquare isn't player piece, 
        then leftSquare is a possible position of piece */
        } else if (rightSquare[PLAYER_INDEX] != player) {
          if(leftSquare[PLAYER_INDEX] == player 
          && chessPiecesLettersArray[leftSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
            game_info.piecePosX = destinationX - offsetX;
          } else {
            game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
          }
        /* Last case all pieces are player's, then 
        assign coordinate of left piece by default */
        } else {
          if(leftSquare[PLAYER_INDEX] == player 
          && chessPiecesLettersArray[leftSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
            game_info.piecePosX = destinationX - offsetX;
          } else if(rightSquare[PLAYER_INDEX] == player 
          && chessPiecesLettersArray[rightSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
            game_info.piecePosX = destinationX + offsetX;
          } else {
            game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
          }
        }
      /* if rightSquare isn't empty and leftSquare is empty,
      then it's possible position of piece */
      } else if(EMPTY_SQUARE != rightSquare[PLAYER_INDEX]) {
        // Check is it player's piece and is it Pawn
        if(rightSquare[PLAYER_INDEX] == player 
        && chessPiecesLettersArray[rightSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
          game_info.piecePosX = destinationX + offsetX;
        }
      /* if leftSquare isn't empty and rightSquare is empty,
      then it's possible position of piece*/
      } else if(EMPTY_SQUARE != leftSquare[PLAYER_INDEX]) {
        // Check is it player's piece and is it Pawn
        if(leftSquare[PLAYER_INDEX] == player 
        && chessPiecesLettersArray[leftSquare[PIECE_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
          game_info.piecePosX = destinationX - offsetX;
        }
      // if leftSquare and rightSquare is empty, then piece not found
      } else {
        game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
      }
    } else {
      int x = 0;
      int y = game_info.piecePosY;
      /* If enemy's piece are at the border coordinate - A or H
      then player's attacking Pawn will be at B(1) or G(6) coordinate*/
      if(destinationX == X_COORDINATE_MIN) {
        x = 1;
      } else if(destinationX == X_COORDINATE_MAX) {
        x = 6;
      }

      // Check if it's pawn on this square
      uint8 squareInfo[2];
      memcpy(squareInfo, chessPositionArray[y][x], 2);
      if(squareInfo[PLAYER_INDEX] == player
      && chessPiecesLettersArray[squareInfo[PLAYER_INDEX]] == game_info.pieceType[FIRST_LETTER]) {
        game_info.piecePosX = x;
      } else {
        game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
      }
    }
  }
}
