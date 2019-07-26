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
            if(get_piece_type(chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX - KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_OFFSET_Y;
                return;
            }
        }
        
        if(endPosX + KNIGHT_HALF_OFFSET_X <= X_COORDINATE_MAX) {
            if(get_piece_type(chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY - KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX + KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_OFFSET_Y;
                return;
            }
        }
    }
    //  In this condition we check is upper points within chess board 
    if(endPosY + KNIGHT_OFFSET_Y <= Y_COORDINATE_MAX) {
        if(endPosX - KNIGHT_HALF_OFFSET_X >= X_COORDINATE_MIN) {
            if(get_piece_type(chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX - KNIGHT_HALF_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX - KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_OFFSET_Y;
                return;
            }
        }
        
        if(endPosX + KNIGHT_HALF_OFFSET_X <= X_COORDINATE_MAX) {
            if(get_piece_type(chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY + KNIGHT_OFFSET_Y][endPosX + KNIGHT_HALF_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX + KNIGHT_HALF_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_OFFSET_Y;
                return;
            }
        }
    }
    //  In this condition we check is left points within chess board
    if(endPosX - KNIGHT_OFFSET_X >= X_COORDINATE_MIN) {
        if(endPosY - KNIGHT_HALF_OFFSET_Y >= Y_COORDINATE_MIN) {
            if(get_piece_type(chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX - KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
        
        if(endPosY + KNIGHT_HALF_OFFSET_Y <= Y_COORDINATE_MAX) {
            if(get_piece_type(chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX - KNIGHT_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX - KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY + KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
    }
    //  In this condition we check is right points within chess board
    if(endPosX + KNIGHT_OFFSET_X <= X_COORDINATE_MAX) {
        if(endPosY - KNIGHT_HALF_OFFSET_Y >= Y_COORDINATE_MIN) {
            if(get_piece_type(chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY - KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X]) == player) {
                game_info.piecePosX = endPosX + KNIGHT_OFFSET_X;
                game_info.piecePosY = endPosY - KNIGHT_HALF_OFFSET_Y;
                return;
            }
        }
        
        if(endPosY + KNIGHT_HALF_OFFSET_Y <= Y_COORDINATE_MAX) {
            if(get_piece_type(chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X]) == KNIGHT
            && get_player(chessPositionArray[endPosY + KNIGHT_HALF_OFFSET_Y][endPosX + KNIGHT_OFFSET_X]) == player) {
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
  uint8 destinationX = game_info.endPosX;
  uint8 destinationY = game_info.endPosY;
    
  uint8 squareInfo = 0;
  // Left upper diagonal path and Left downer diagonal path
  if(destinationX != X_COORDINATE_MAX) {
    uint8 y = destinationY;
    // Left upper diagonal path
    for(uint8 x = destinationX + 1; x < 8; x++) {
      y += 1;
        
      squareInfo = chessPositionArray[y][x];

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
    for(uint8 x = destinationX + 1; x < 8; x++) {
      y -= 1;
        
      squareInfo = chessPositionArray[y][x];

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
    uint8 y = destinationY;
    // Right downer diagonal path
    for(uint8 x = destinationX - 1; x >= 0; x--) {
      y -= 1;
        
      squareInfo = chessPositionArray[y][x];

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
    for(uint8 x = destinationX - 1; x >= 0; x--) {
      y += 1;
      
      squareInfo = chessPositionArray[y][x];

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
  uint8 destinationX = game_info.endPosX;
  uint8 destinationY = game_info.endPosY;
    
  uint8 squareInfo = 0;

  // Check if piece is already found
  if(0 == strcmp(game_info.pieceType, "Queen")) {
    uint8 x = game_info.piecePosX;
    uint8 y = game_info.piecePosY;
    
    squareInfo = chessPositionArray[y][x];
    
    // If piece is already found, then return
    if(chessPiecesLettersArray[get_piece_index(squareInfo)] == game_info.pieceType[FIRST_LETTER]) {
      return;
    }
  }

  // Path to right from destination position
  if(destinationX != X_COORDINATE_MAX) {
    uint8 y = destinationY;

    for(uint8 x = destinationX + 1; x < 8; x++) {
        
      squareInfo = chessPositionArray[y][x];

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
    uint8 y = destinationY;
    
    for(uint8 x = destinationX - 1; x >= 0; x--) {
      
      squareInfo = chessPositionArray[y][x];

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
  uint8 destinationX = game_info.endPosX;
  uint8 destinationY = game_info.endPosY;
    
  uint8 squareInfo = 0;

  // Check if piece is already found
  if(0 == strcmp(game_info.pieceType, "Queen")
  || 0 == strcmp(game_info.pieceType, "Rook")) {
    uint8 x = game_info.piecePosX;
    uint8 y = game_info.piecePosY;
    
    squareInfo = chessPositionArray[y][x];
    
    // If piece is already found, then return
    if(chessPiecesLettersArray[get_piece_index(squareInfo)] == game_info.pieceType[FIRST_LETTER]) {
      return;
    }
  }

  if(destinationY != Y_COORDINATE_MAX) {
    uint8 x = destinationX;
    
    // Path from destination position to upper side
    for(uint8 y = destinationY + 1; y < 8; y++) {
        
      squareInfo = chessPositionArray[y][x];

      // If is_piece_found() returns 1, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found() returns 0, then path blocked - brake cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }
    }
  }

  if(destinationY != Y_COORDINATE_MIN) {
    uint8 x = destinationX;

    // Path from destination position to downer side
    for(uint8 y = destinationY - 1; y >= 0; y--) {
        
      squareInfo = chessPositionArray[y][x];

      // If is_piece_found() returns, then piece found - exit function
      if(is_piece_found(squareInfo) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found() returns, then path blocked - brake cycle
      } else if(is_piece_found(squareInfo) == 0) {
        break;
      }
    }
  }
}

// Fucntion that find Pawn on the chess board
void find_pawn(void) {
  uint8 player = game_info.player;
  uint8 destinationY = game_info.endPosY;
  uint8 destinationX = game_info.endPosX;

  if(game_info.isSquareEmpty) {
    game_info.piecePosX = destinationX;

    /* At the start square Pawn can move 2 square forward
    if player want this */
    if((3 == destinationY && WHITE_PLAYER == player)
    || (destinationY == 4 && BLACK_PLAYER == player)) {
      // Y positions of bottom and top squares
      uint8 bottomPosY = 0;
      uint8 topPosY = 0;
      // Set bottom and top square
      if(WHITE_PLAYER == player) {
        bottomPosY = 1;
        topPosY = 2;
      } else if(BLACK_PLAYER == player) {
        bottomPosY = 6;
        topPosY = 5;
      }

      // Bottom piece coordinates is [a-h]2 for white or [a-h]7 for black
      uint8 bottomSquare = chessPositionArray[bottomPosY][destinationX];
      // Top piece coordinates is [a-h]3 for white or [a-h]6 for black
      uint8 topSquare = chessPositionArray[topPosY][destinationX];

      if((EMPTY_SQUARE != bottomSquare) 
      && (EMPTY_SQUARE != topSquare)) {
        // If at top square is enemy then path is blocked
        if(get_player(topSquare) != player 
        && get_player(bottomSquare) == player) {
          game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
        /* If at top square is player's, then it's possible Pawn
        this'll be checked in second step of validation */
        } else if(get_player(topSquare) == player
        && get_player(bottomSquare) == player) {
          // If top square piece isn't Pawn then error
          if(get_piece_type(topSquare) != PAWN) {
            game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
          } else {
            game_info.piecePosY = topPosY;
          }
        }
      // If both bottom and top squares is empty then no piece found
      } else if((EMPTY_SQUARE == bottomSquare) 
      && (EMPTY_SQUARE == topSquare)) {
        game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
      /* If bottom square isn't empty and top square is empty
      then bottom square is possible position of Pawn */
      } else if((EMPTY_SQUARE != bottomSquare) 
      && (EMPTY_SQUARE == topSquare)) {
        if(get_player(bottomSquare) == player
        && get_piece_type(bottomSquare) == PAWN) {
          game_info.piecePosY = bottomPosY;
        } else {
          game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
        }
      /* If bottom square is empty and top square isn't empty
      then top square is possible position of Pawn */
      } else if((EMPTY_SQUARE == bottomSquare) 
      && (EMPTY_SQUARE != topSquare)) {
        if(get_player(topSquare) == player
        && get_piece_type(topSquare) == PAWN) {
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
      int8 offsetX = 0;
      if(WHITE_PLAYER == player) {
        offsetX = -1;
      } else if(BLACK_PLAYER == player) {
        offsetX = 1;
      }

      uint8 leftSquare = chessPositionArray[game_info.piecePosY][destinationX - offsetX];
      uint8 rightSquare = chessPositionArray[game_info.piecePosY][destinationX + offsetX];

      /* Check if both left and right square isn't empty if not
      then check if left isn't empty if not
      then check if right isn't empty */
      if((EMPTY_SQUARE != rightSquare) 
      && (EMPTY_SQUARE != leftSquare)) {
        // If it's not a player piece 
        if(get_player(leftSquare) != player 
        && get_player(rightSquare) != player) {
          game_info.commandStatus = ERROR_NON_PLAYER_S_PIECE;
        /* If leftSquare isn't player piece, 
        then rightSquare is a possible position of piece */
        } else if (get_player(leftSquare) != player) {
          if(get_player(rightSquare) == player 
          && get_piece_type(rightSquare) == PAWN) {
            game_info.piecePosX = destinationX + offsetX;
          } else {
            game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
          }
        /* If rightSquare isn't a player piece, 
        then leftSquare is a possible position of piece */
        } else if (get_player(rightSquare) != player) {
          if(get_player(leftSquare) == player 
          && get_piece_type(leftSquare) == PAWN) {
            game_info.piecePosX = destinationX - offsetX;
          } else {
            game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
          }
        /* Last case all pieces are player's, then 
        assign coordinate of left piece by default */
        } else {
          if(get_player(leftSquare) == player 
          && get_piece_type(leftSquare) == PAWN) {
            game_info.piecePosX = destinationX - offsetX;
          } else if(get_player(rightSquare) == player 
          && get_piece_type(rightSquare) == PAWN) {
            game_info.piecePosX = destinationX + offsetX;
          } else {
            game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
          }
        }
      /* if rightSquare isn't empty and leftSquare is empty,
      then it's possible position of piece */
      } else if(EMPTY_SQUARE != rightSquare) {
        // Check is it player's piece and is it Pawn
        if(get_player(rightSquare) == player 
        && get_piece_type(rightSquare) == PAWN) {
          game_info.piecePosX = destinationX + offsetX;
        }
      /* if leftSquare isn't empty and rightSquare is empty,
      then it's possible position of piece*/
      } else if(EMPTY_SQUARE != leftSquare) {
        // Check is it player's piece and is it Pawn
        if(get_player(leftSquare) == player 
        && get_piece_type(leftSquare) == PAWN) {
          game_info.piecePosX = destinationX - offsetX;
        }
      // if leftSquare and rightSquare is empty, then piece not found
      } else {
        game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
      }
    } else {
      uint8 x = 0;
      uint8 y = game_info.piecePosY;
      /* If enemy's piece are at the border coordinate - A or H
      then player's attacking Pawn will be at B(1) or G(6) coordinate*/
      if(destinationX == X_COORDINATE_MIN) {
        x = 1;
      } else if(destinationX == X_COORDINATE_MAX) {
        x = 6;
      }

      // Check if it's pawn on this square
      uint8 squareInfo = chessPositionArray[y][x];
    
      if(get_player(squareInfo) == player
      && get_piece_type(squareInfo) == PAWN) {
        game_info.piecePosX = x;
      } else {
        game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
      }
    }
  }
}
