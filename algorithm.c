#include <stdio.h>

enum ErrorCodes{
  RIGHT_COMMAND = 0x01, ERROR_IS_ALLY = 0x02, ERROR_PIECE_NOT_FOUND = 0x03,
  ERROR_NON_PLAYER_S_PIECE = 0x04, ERROR_PATH_BLOCKED_BY_ENEMY = 0x05,
  ERROR_PATH_BLOCKED_BY_ALLY = 0x06, ERROR_PIECE_TYPE_DON_T_MATCH = 0x07,
  ERROR_DESTINATION_PIECE_IS_KING = 0x08
};

// Array of chess position on the Chess board
const char * chessPositionArray[8][8] = {
  {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"},
  {"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
  {"", "", "", "", "", "", "", ""},
  {"", "", "", "", "", "", "", ""},
  {"", "", "", "", "", "", "", ""},
  {"", "", "", "", "", "", "", ""},
  {"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
  {"bR", "bN", "bB", "bK", "bQ", "bB", "bN", "bR"}
};

// Array of chess pieces types
const char * chessPiecesTypesArray[5] = {
  "Rook", "Knight", "Bishop", "Queen", "King"
};

// Array of chess pieces letters
char chessPiecesLettersArray[5] = {
  'R', 'N', 'B', 'Q', 'K'
};

// Test commands
const char * commandArray[10] = {
    "Qc4", "h5", "b5", "h4", "a6", "h3", "b7", "g2", "c8", "f1"
};

char chessCoordinates[8][2] = {
  {'a', '1'},
  {'b', '2'},
  {'c', '3'},
  {'d', '4'},
  {'e', '5'},
  {'f', '6'},
  {'g', '7'},
  {'h', '8'},
};

typedef struct {
  const char * player;

  // Coordinates of piece
  int piecePosX;
  int piecePosY;

  /* Coordinates where piece will move 
  and info about square where'll piece move*/
  int isSquareEmpty;
  int endPosX;
  int endPosY; 

  // Piece type for validation and checks
  const char * pieceType;

  // Store info about command
  int commandStatus;
} game_info_t;
game_info_t game_info;

// Validation of input command 
void validate_command(const char * command);
// Function that return type of piece
const char * get_chess_piece_type(char chessPieceLetter);
// Check if square is empty
int is_square_empty(const char * coordinates);
// Check if piece is ally
void is_piece_ally();
// Check if destination piece is king
int is_destination_piece_king();

// Find piece by the piece type
void find_piece();
// Fucntion that find Pawn on the chess board
void find_pawn();
// Function that find piece by horizontal path
void find_by_horizontal();
// Function that find piece by vertical path
void find_by_vertical();
// Function that find piece by diagonal path
void find_by_diagonal();

// Check if piece is on the square and is it player piece
void is_piece_on_the_square();

void validate_path();
/* Function that checks if there are any chess pieces 
from Rook's position to destination position.
Return 1 if path is free or 0 in other case*/
int is_rook_path_free();
// Function that validate diagonal path
int is_diagonal_path_free();
/* Checks by string paramater is this piece 
that we are looking for. Return 1 if piece match to piece
that we searching and 0 in other cases*/
int is_piece_found(const char * piece);


// Change Pawn piece to Queen when reached other side of board
void pawn_become_queen();

// Generate GCODE commands
void generate_gcode();

void update_chess_array();

// Print chess board and all chess pieces position
void print_chess_position_array();

int main(void) {
  game_info.player = "white";

  print_chess_position_array();
  char command[3];
  /*for(;;) {
    printf("Input command: ");
    scanf("%s", command);
    validate_command(command);
  }*/
  // Automated testing
  for(int i = 0; i < 1; i++) {
    validate_command(commandArray[i]);
  }
}

// Validation of input command 
void validate_command(const char *command) {
  game_info.commandStatus = RIGHT_COMMAND;
  printf("\nPlayer is %s\n", game_info.player);
  printf("Command %s\n\n", command);
  // Get piece type
  game_info.pieceType = get_chess_piece_type(command[0]);

  // Check if square is empty. Need for next validation of some chess pieces
  if(game_info.pieceType == "Pawn") {
    game_info.isSquareEmpty = is_square_empty(command);
  } else {
    char coordinates[2];
    sprintf(coordinates, "%c%c", command[1], command[2]);  
    game_info.isSquareEmpty = is_square_empty(coordinates);
  }

  // Check if destination position piece isn't King
  if(is_destination_piece_king()) {
    game_info.commandStatus = ERROR_DESTINATION_PIECE_IS_KING;
  }

  /* If bad command then quit function and wait for the next command
  in other case find piece */
  for(int validationStep = 0; validationStep < 5; validationStep++) {
    if(game_info.commandStatus != RIGHT_COMMAND) {

      printf("\nERROR CODE %d\n", game_info.commandStatus);
      printf("________________________________________\n");
      return;
    } else {
      /* First step is find a possible coordinate 
      of the piece on the board*/
      if(validationStep == 0) {
        find_piece();
      // Second step is check if is piece on the board
      } else if(validationStep == 1) {
        is_piece_on_the_square();
      // Third step is validate path if need
      } else if(validationStep == 2) {
        // Generate GCODE here
        generate_gcode();
      // Forth step is move piece
      } else if(validationStep == 3) {
        if(game_info.pieceType == "Pawn") {
          if(game_info.player == "white" && game_info.endPosY == 7
          ||  game_info.player == "black" && game_info.endPosY == 0) {
            pawn_become_queen();
          }
        }

        update_chess_array();
      }
    }
  }

  // Print updated array
  print_chess_position_array();

  // Change player if command is right or leave the same player if command isn't right
  if(game_info.commandStatus == RIGHT_COMMAND) {
    if(game_info.player == "white") {
      game_info.player = "black";
    } else {
      game_info.player = "white";
    }
  }
}

// Update chess array after validation
void update_chess_array() {
  // Update position in array
  if(game_info.isSquareEmpty) {
    chessPositionArray[game_info.endPosY][game_info.endPosX] = chessPositionArray[game_info.piecePosY][game_info.piecePosX];
    chessPositionArray[game_info.piecePosY][game_info.piecePosX] = "";
  } else {
    // There will block to save piece at defeated pieces array
    chessPositionArray[game_info.endPosY][game_info.endPosX] = chessPositionArray[game_info.piecePosY][game_info.piecePosX];
    chessPositionArray[game_info.piecePosY][game_info.piecePosX] = "";
  }
}

// Find piece by the piece type
void find_piece() {
  if(game_info.pieceType == "Pawn") {
    find_pawn();
  } else if(game_info.pieceType == "Rook") {
    find_by_horizontal();
    find_by_vertical();
  } else if(game_info.pieceType == "Knight") {
    // Find Knight
  } else if(game_info.pieceType == "Bishop") {
    find_by_diagonal();
  } else if(game_info.pieceType == "King") {
    // Find King
  } else if(game_info.pieceType == "Queen") {
    find_by_diagonal();
    find_by_horizontal();
    find_by_vertical();
  }
}

/* Check if piece is on the square and is it player piece, 
if not then assign to command status error code*/
void is_piece_on_the_square() {
  const char * piece = chessPositionArray[game_info.piecePosY][game_info.piecePosX];
  // Check if piece is on the square
  if(piece != "") {
    if(piece[1] != game_info.pieceType[0]) {
      printf(piece);
      game_info.commandStatus = ERROR_PIECE_TYPE_DON_T_MATCH;
    } else if(piece[0] != game_info.player[0]) {
      game_info.commandStatus = ERROR_NON_PLAYER_S_PIECE;
    }
  // Then square is empty
  } else {
    game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
  }
}

// Function that return type of piece
const char * get_chess_piece_type(char chessPieceLetter) {
  const char * chessPieceType = 0;
    for(int i = 0; i < 5; i++) {
      if(chessPieceLetter == chessPiecesLettersArray[i]) {
        chessPieceType = chessPiecesTypesArray[i];
        break;
      }
  }
  if(chessPieceType == 0) {
    chessPieceType = "Pawn";
  }
  return chessPieceType;
}

// Function that checks by x y coordinates if square is empty
int is_square_empty(const char * coordinates) {
  char chessCoordinate;
  // Get X coordinate
  for(int i = 0; i < 8; i++) {
    if(coordinates[0] == chessCoordinates[i][0]) {
      game_info.endPosX = i;
      break;
    }
  }
  // Get Y coordinate
  for(int i = 0; i < 8; i++) {
    if(coordinates[1] == chessCoordinates[i][1]) {
      game_info.endPosY = i;
      break;
    }
  }
  
  //Check if square is empty
  if(chessPositionArray[game_info.endPosY][game_info.endPosX] != "") {
    is_piece_ally(
      chessPositionArray[game_info.endPosY][game_info.endPosX]);
    return 0;
  } else {
    return 1;
  }
}

// Check if piece is ally
void is_piece_ally(const char * piece) {
  if(piece[0] == game_info.player[0]) {
    game_info.commandStatus = ERROR_IS_ALLY;
  } else {
  }
}

void validate_path(const char * pieceType) {
  if(pieceType == "Pawn") {
    // Pawn path don't need validation so exit function
    return;
  } else if(pieceType == "Rook") {
    // Rook path validating after finding
  } else if(pieceType == "Knight") {
    // Check Knight path
  } else if(pieceType == "Bishop") {
    // Check Bishop path
  } else if(pieceType == "King") {
    // Check King path
  } else if(pieceType == "Queen") {
    // Check Queen path
  }
}

/* When pawn got to other side of board then pawn piece become queen.
Function that changes pawn piece to queen in the chessArray*/
void pawn_become_queen() {
  const char * queen;
  if(game_info.player == "white") {
    queen = "wQ";
  } else {
    queen = "bQ";
  }
  chessPositionArray[game_info.piecePosY][game_info.piecePosX] = queen;
}

/* Function that checks is destination piece king to avoid
killing of him*/
int is_destination_piece_king() {
  if(chessPositionArray[game_info.endPosY][game_info.endPosX][1] == 'K') {
    return 1;
  } else {
    return 0;
  }
}

// Function that find by diagonal path
void find_by_diagonal() {
  int destinationX = game_info.endPosX;
  int destinationY = game_info.endPosY;
  // Left upper diagonal path and Left downer diagonal path
  if(destinationX != 7) {
    int y = destinationY;
    // Left upper diagonal path
    for(int x = destinationX + 1; x < 8; x++) {
      y += 1;
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }

      if(x == 7 | y == 7) {
        break;
      }
    }

    y = destinationY;
    // Left downer diagonal path
    for(int x = destinationX + 1; x < 8; x++) {
      y -= 1;
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }

      if(x == 7 | y == 0) {
        break;
      }
    }
  }

  // Right downer diagonal path and Right upper diagonal path
  if(destinationX != 0) {
    int y = destinationY;
    // Right downer diagonal path
    for(int x = destinationX - 1; x >= 0; x--) {
      y -= 1;
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }

      if(x == 0 | y == 0) {
        break;
      }
    }

    y = destinationY;
    // Right upper diagonal path
    for(int x = destinationX - 1; x >= 0; x--) {
      y += 1;
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }

      if(x == 0 | y == 7) {
        break;
      }
    }
  }
}

/* Checks by string paramater is this piece 
that we are looking for. Return 1 if piece match 
to piece that we searching and 0 if other piece
(ally or enemy) and 2 if square is empty */
int is_piece_found(const char * piece) {
  if(piece != "") {
    // If it's piece that we looking for, then return 1
    if(game_info.player[0] == piece[0]
    && game_info.pieceType[0] == piece[1]) {
      game_info.commandStatus = RIGHT_COMMAND;
      return 1;
    // In this case it's not piece that we looking for and path blocked by ally, then return 0
    } else if(game_info.player[0] == piece[0]) {
      game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
      return 0;
    // In this case it's not piece that we looking for and path blocked by enemy, then return 0
    } else if(game_info.player[0] != piece[0]) {
      game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
      return 0;
    }
  // If square is empty, then return 2
  } else if(piece == "") {
    game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
    return 2;
  }
}

// Function that find piece by horizontal path
void find_by_horizontal() {
  int destinationX = game_info.endPosX;
  int destinationY = game_info.endPosY;

  // Check if piece is already found
  if(game_info.pieceType == "Queen") {
    int x = game_info.piecePosX;
    int y = game_info.piecePosY;
    const char * piece = chessPositionArray[y][x];
    // If piece is already found, then return
    if(piece[1] == game_info.pieceType[0]) {
      return;
    }
  }

  // Path to right from destination position
  if(destinationX != 7) {
    int y = destinationY;

    for(int x = destinationX + 1; x < 8; x++) {
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }
    }
  }

  // Path to left from destination position
  if(destinationX != 0) {
    int y = destinationY;
    
    for(int x = destinationX - 1; x >= 0; x--) {
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }
    }
  }
}

// Function that find piece by vertical path
void find_by_vertical() {
  int destinationX = game_info.endPosX;
  int destinationY = game_info.endPosY;

  // Check if piece is already found
  if(game_info.pieceType == "Queen"
  || game_info.pieceType == "Rook") {
    int x = game_info.piecePosX;
    int y = game_info.piecePosY;
    const char * piece = chessPositionArray[y][x];
    // If piece is already found, then return
    if(piece[1] == game_info.pieceType[0]) {
      return;
    }
  }

  if(destinationY != 7) {
    int x = destinationX;
    
    // Path from destination position to upper side
    for(int y = destinationY + 1; y < 8; y++) {
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }
    }
  }

  if(destinationY != 0) {
    int x = destinationX;

    // Path from destination position to downer side
    for(int y = destinationY - 1; y >= 0; y--) {
      const char * piece = chessPositionArray[y][x];

      // If is_piece_found return 1, then piece found - exit function
      if(is_piece_found(piece) == 1) {
        game_info.piecePosX = x;
        game_info.piecePosY = y;
        return;
      // If is_piece_found return 0, then path blocked - brake cycle
      } else if(is_piece_found(piece) == 0) {
        break;
      }
    }
  }
}

// Fucntion that find Pawn on the chess board
void find_pawn() {
  game_info.piecePosX = 0;
  game_info.piecePosY = 0;

  if(game_info.isSquareEmpty) {
    game_info.piecePosX = game_info.endPosX;
    if(game_info.player == "white") {
      /* At the start square Pawn can move 2 square forward
      if player want this */
      if(game_info.endPosY == 3) {
        // Bottom piece coordinates is [a-h]2
        const char * bottomSquare = chessPositionArray[1][game_info.endPosX];
        // Top piece coordinates is [a-h]3
        const char * topSquare = chessPositionArray[2][game_info.endPosX];  

        if(bottomSquare != "" && topSquare != "") {
          // If at top square is enemy then path is blocked
          if(topSquare[0] != game_info.player[0] 
          && bottomSquare[0] == game_info.player[0]) {
            game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
          /* If at top square is player's, then it's possible Pawn
          this'll be checked in second step of validation */
          } else if(topSquare[0] == game_info.player[0]
          && bottomSquare[0] == game_info.player[0]) {
            // If top square piece isn't Pawn then error
            if(topSquare[1] != game_info.pieceType[0]) {
              game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
            } else {
              game_info.piecePosY = 2;
            }
          }
        // If bottom and top squares is empty then no piece found
        } else if(bottomSquare == "" && topSquare == "") {
          game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
        /* If bottom square isn't empty and top square is empty
        then bottom square is possible position of Pawn */
        } else if(bottomSquare != "" && topSquare == "") {
          game_info.piecePosY = 1;
        /* If bottom square is empty and top square isn't empty
        then top square is possible position of Pawn */
        } else if(bottomSquare == "" && topSquare != "") {
          game_info.piecePosY = 2;
        }
      // In this case piece position is Y destination position - 1
      } else if(game_info.endPosY > 1) {
        game_info.piecePosY = game_info.endPosY - 1;
      }
    // If player is black then 
    } else {
      if(game_info.endPosY == 4) {
        // Bottom piece coordinates is [a-h]7
        const char * bottomSquare = chessPositionArray[6][game_info.endPosX];
        // Top piece coordinates is [a-h]6
        const char * topSquare = chessPositionArray[5][game_info.endPosX];  

        if(bottomSquare != "" && topSquare != "") {
          // If at top square is enemy then path is blocked
          if(topSquare[0] != game_info.player[0] 
          && bottomSquare[0] == game_info.player[0]) {
            game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ENEMY;
          /* If at top square is player's, then it's possible Pawn
          this'll be checked in second step of validation */
          } else if(topSquare[0] == game_info.player[0]
          && bottomSquare[0] == game_info.player[0]) {
            // If top square piece isn't Pawn then error
            if(topSquare[1] != game_info.pieceType[0]) {
              game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
            } else {
              game_info.piecePosY = 5;
            }
          }
        // If bottom and top squares is empty then no piece found
        } else if(bottomSquare == "" && topSquare == "") {
          game_info.commandStatus = ERROR_PIECE_NOT_FOUND;
        /* If bottom square isn't empty and top square is empty
        then bottom square is possible position of Pawn */
        } else if(bottomSquare != "" && topSquare == "") {
          game_info.piecePosY = 6;
        /* If bottom square is empty and top square isn't empty
        then top square is possible position of Pawn */
        } else if(bottomSquare == "" && topSquare != "") {
          game_info.piecePosY = 5;
        }
      // In this case piece position is Y destination position + 1
      } else if(game_info.endPosY < 6) {
        game_info.piecePosY = game_info.endPosY + 1;
      } 
    }
  // If square isn't empty
  } else {
    /* Calculate Y coordinate of Pawn
    Just add 1 to Y coordinate if black or substract 1 if white player */
    if(game_info.player == "white") {
      game_info.piecePosY = game_info.endPosY - 1;
    } else {
      game_info.piecePosY = game_info.endPosY + 1;
    }

    if(game_info.endPosX > 0 & game_info.endPosX < 7) {
      /* When Pawn attack he can be only to the right of enemy piece
      or to the left of enemy piece */

      /* For black player left piece will on another side
      than white player left piece, so declare here offset
      that will change his value along with changing player*/
      int offsetX;
      if(game_info.player == "white") {
        offsetX = -1;
      } else {
        offsetX = 1;
      }

      const char * leftSquare = chessPositionArray[game_info.piecePosY][game_info.endPosX-offsetX];
      const char * rightSquare = chessPositionArray[game_info.piecePosY][game_info.endPosX+offsetX];

      /* Check if left and right square isn't empty if not
      then check if left isn't empty if not
      then check if right isn't empty */
      if(rightSquare != "" && leftSquare != "") {
        // If it's not player piece 
        if(leftSquare[0] != game_info.player[0] 
        && rightSquare[0] != game_info.player[0]) {
          game_info.commandStatus = ERROR_NON_PLAYER_S_PIECE;
        /* If leftSquare isn't player piece, 
        then rightSquare is a possible position of piece */
        } else if (leftSquare[0] != game_info.player[0]) {
          game_info.piecePosX = game_info.endPosX + offsetX;
        /* If rightSquare isn't player piece, 
        then leftSquare is a possible position of piece */
        } else if (rightSquare[0] != game_info.player[0]) {
          game_info.piecePosX = game_info.endPosX - offsetX;
        /* Last case all pieces are player's, then 
        assign coordinate of left piece by default */
        } else {
          game_info.piecePosX = game_info.endPosX - offsetX;
        }
      // if rightSquare isn't empty then it's possible position of piece
      } else if(rightSquare != "") {
        game_info.piecePosX = game_info.endPosX + offsetX;
      // if leftSquare isn't empty then it's possible position of piece
      } else if(leftSquare != "") {
        game_info.piecePosX = game_info.endPosX - offsetX;
      }
    } else {
      /* If enemy's piece are at the border coordinate - A or H
      then player's attacking Pawn will be at B(1) or G(6) coordinate*/
      if(game_info.endPosX == 0) {
        game_info.piecePosX = 1;
      } else if(game_info.endPosX == 7) {
        game_info.piecePosX = 6;
      }
    }
  }
}

// Generate GCODE commands
void generate_gcode() {
  printf("GCODE Commands:\n");
  char gcodeCommandBuffer[15];

  /* Check if square isn't empty. If so need to generate 
  GCODE first for defeated piece */
  if( !game_info.isSquareEmpty ) {
    //printf("DEFEATED PIECE\n");
    // Move platform down

    sprintf(gcodeCommandBuffer, "G01 X%d Y%d F200\n\r", 
    game_info.endPosX, game_info.endPosY);
    printf("%s", gcodeCommandBuffer);

    // Move platform up

    // Find free slot for defeated piece
    printf("Move to slot t\n\n");
  }
  printf("PIECE MOVEMENT\n");
  // Move platform down

  // Move to piece position
  sprintf(gcodeCommandBuffer, "G01 X%d Y%d F500\n\r", 
  game_info.piecePosX, game_info.piecePosY);
  printf("%s", gcodeCommandBuffer);

  // Move platform up

  // Move piece to destination position
  const char * piece = game_info.pieceType;
  if (piece == "Knight") {
    // Knight GCODE is special, so he need to has different block
  } else {
    sprintf(gcodeCommandBuffer, "G01 X%d Y%d F200\n\r", 
    game_info.endPosX, game_info.endPosY);
    printf("%s", gcodeCommandBuffer);
  }
}

// Print chess board and all chess pieces position
void print_chess_position_array() {
  for(int y = 0; y < 8; y++) {
    printf("%c ", chessCoordinates[y][1]);
    for(int x = 0; x < 8; x++) {
      if(chessPositionArray[y][x] == 0 | chessPositionArray[y][x] == "") {
        printf("[  ]");
      } else {
        printf("[");
        printf(chessPositionArray[y][x]);
        printf("]");
      }
      printf(" ");
    }
    printf("\r\n");
  }
  printf("  ");
  for(int i = 0; i < 8; i++) {
    printf("  %c  ", chessCoordinates[i][0]);
  }
  printf("\n");
}
