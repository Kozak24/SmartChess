#include <stdio.h>

enum ErrorCodes{
  RIGHT_COMMAND = 0x01, ERROR_IS_ALLY = 0x02, ERROR_FIGURE_NOT_FOUND = 0x03,
  ERROR_NON_PLAYER_S_FIGURE = 0x04, ERROR_PATH_BLOCKED_BY_ENEMY = 0x05,
  ERROR_PATH_BLOCKED_BY_ALLY = 0x06, ERROR_FIGURE_TYPE_DON_T_MATCH = 0x07,
  ERROR_DESTINATION_FIGURE_IS_KING = 0x08
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

// Array of chess figures types
const char * chessFiguresTypesArray[5] = {
  "Rook", "Knight", "Bishop", "Queen", "King"
};

// Array of chess figures letters
char chessFiguresLettersArray[5] = {
  'R', 'N', 'B', 'Q', 'K'
};

// Test commands
const char * commandArray[10] = {
    "a4", "h5", "a5", "h4", "a6", "h3", "b7", "g2", "c8", "f1"
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

  // Coordinates of figure
  int figurePosX;
  int figurePosY;

  /* Coordinates where figure will move 
  and info about square where'll figure move*/
  int isSquareEmpty;
  int endPosX;
  int endPosY; 

  // Figure type for validation and checks
  const char * figureType;

  // Store info about command
  int commandStatus;
} game_info_t;
static game_info_t game_info;

void validate_command(const char * command);
const char * get_chess_figure_type(char chessFigureLetter);
int is_square_empty(const char * coordinates);
void is_figure_ally();
int is_destination_figure_king();

void find_figure();
void find_pawn();
void is_figure_on_the_square();

void validate_path();
void pawn_become_queen();

void update_chess_array();

void print_chess_position_array();

int main(void) {
  game_info.player = "white";

  print_chess_position_array();
  printf("Input command: ");
  char command[3];
  for(;;) {
    scanf("%s", command);
    validate_command(command);
  }
  // Automated testing
  /*for(int i = 0; i < 10; i++) {
    validate_command(commandArray[i]);
  }*/
}

void validate_command(const char *command) {
  game_info.commandStatus = RIGHT_COMMAND;
  printf("\nPlayer is %s\n", game_info.player);
  printf("Command %s\n\n", command);
  // Get figure type
  game_info.figureType = get_chess_figure_type(command[0]);

  // Check if square is empty. Need for next validation of some chess figures
  if(game_info.figureType == "Pawn") {
    game_info.isSquareEmpty = is_square_empty(command);
  } else {
    char coordinates[2];
    sprintf(coordinates, "%c%c", command[1], command[2]);  
    game_info.isSquareEmpty = is_square_empty(coordinates);
  }

  // Check if destination position figure isn't King
  if(is_destination_figure_king()) {
    game_info.commandStatus = ERROR_DESTINATION_FIGURE_IS_KING;
  }

  /* If bad command then quit function and wait for the next command
  in other case find figure */
  for(int validationStep = 0; validationStep < 5; validationStep++) {
    if(game_info.commandStatus != RIGHT_COMMAND) {

      printf("\nERROR CODE %d\n", game_info.commandStatus);
      return;
    } else {
      /* First step is find a possible coordinate 
      of the figure on the board*/
      if(validationStep == 0) {
        find_figure();
      // Second step is check if is figure on the board
      } else if(validationStep == 1) {
        is_figure_on_the_square();
      // Third step is validate path if need
      } else if(validationStep == 2) {
        //validate_path(figureType);
      // Fourth step is generate GCODE
      } else if(validationStep == 3) {
        // Generate GCODE here
      // Fifth step is move figure
      } else if(validationStep == 4) {
        if(game_info.figureType == "Pawn") {
          if(game_info.player == "white" && game_info.endPosY == 7
          ||  game_info.player == "black" && game_info.endPosY == 0) {
            pawn_become_queen();
          }
        }
        update_chess_array();
      }
    }
  }

  /*printf("\nFigure - %s \nLocal coordinates X%dY%d -> X%dY%d\n", game_info.figureType, 
  game_info.figurePosX, game_info.figurePosY, game_info.endPosX, game_info.endPosY);
  printf("Global coordinates %c%c -> %c%c\n\n", chessCoordinates[game_info.figurePosX][0],
   chessCoordinates[game_info.figurePosY][1], chessCoordinates[game_info.endPosX][0],
   chessCoordinates[game_info.endPosY][1]);*/

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

void update_chess_array() {
  // Update position in array
  if(game_info.isSquareEmpty) {
    chessPositionArray[game_info.endPosY][game_info.endPosX] = chessPositionArray[game_info.figurePosY][game_info.figurePosX];
    chessPositionArray[game_info.figurePosY][game_info.figurePosX] = "";
  } else {
    // There will block to save figure at defeated figures array
    chessPositionArray[game_info.endPosY][game_info.endPosX] = chessPositionArray[game_info.figurePosY][game_info.figurePosX];
    chessPositionArray[game_info.figurePosY][game_info.figurePosX] = "";
  }
}

// Find figure by the figure type
void find_figure() {
  if(game_info.figureType == "Pawn") {
    find_pawn();
  } else if(game_info.figureType == "Rook") {
    // Find Rook
  } else if(game_info.figureType == "Knight") {
    // Find Knight
  } else if(game_info.figureType == "Bishop") {
    // Find Bishop
  } else if(game_info.figureType == "King") {
    // Find King
  } else if(game_info.figureType == "Queen") {
    // Find Queen
  }
}

/* Check if figure is on the square and is it player figure, 
if not then assign to command status error code*/
void is_figure_on_the_square() {
  const char * figure = chessPositionArray[game_info.figurePosY][game_info.figurePosX];
  // Check if figure is on the square
  if(figure != "") {
    if(figure[1] != game_info.figureType[0]) {
      printf(figure);
      game_info.commandStatus = ERROR_FIGURE_TYPE_DON_T_MATCH;
    } else if(figure[0] != game_info.player[0]) {
      game_info.commandStatus = ERROR_NON_PLAYER_S_FIGURE;
    }
  // Then square is empty
  } else {
    game_info.commandStatus = ERROR_FIGURE_NOT_FOUND;
  }
}

// Function that return type of figure
const char * get_chess_figure_type(char chessFigureLetter) {
  const char * chessFigureType = 0;
    for(int i = 0; i < 5; i++) {
      if(chessFigureLetter == chessFiguresLettersArray[i]) {
        chessFigureType = chessFiguresTypesArray[i];
        break;
      }
  }
  if(chessFigureType == 0) {
    chessFigureType = "Pawn";
  }
  return chessFigureType;
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
    is_figure_ally(
      chessPositionArray[game_info.endPosY][game_info.endPosX]);
    return 0;
  } else {
    return 1;
  }
}

//Check if figure is ally
void is_figure_ally(const char * figure) {
  if(figure[0] == game_info.player[0]) {
    game_info.commandStatus = ERROR_IS_ALLY;
  } else {
  }
}

void validate_path(const char * figureType) {
  if(figureType == "Pawn") {
    // Pawn path don't need validation so exit function
    return;
  } else if(figureType == "Rook") {
    // Check Rook path
  } else if(figureType == "Knight") {
    // Check Knight path
  } else if(figureType == "Bishop") {
    // Check Bishop path
  } else if(figureType == "King") {
    // Check King path
  } else if(figureType == "Queen") {
    // Check Queen path
  }
}

void pawn_become_queen() {
  const char * queen;
  if(game_info.player == "white") {
    queen = "wQ";
  } else {
    queen = "bQ";
  }
  chessPositionArray[game_info.figurePosY][game_info.figurePosX] = queen;
}

int is_destination_figure_king() {
  if(chessPositionArray[game_info.endPosY][game_info.endPosX][1] == 'K') {
    return 1;
  } else {
    return 0;
  }
}

void find_pawn() {
  game_info.figurePosX = 0;
  game_info.figurePosY = 0;

  if(game_info.isSquareEmpty) {
    game_info.figurePosX = game_info.endPosX;
    if(game_info.player == "white") {
      /* At the start square Pawn can move 2 square forward
      if player want this */
      if(game_info.endPosY == 3) {
        // Bottom figure coordinates is [a-h]2
        const char * bottomSquare = chessPositionArray[1][game_info.endPosX];
        // Top figure coordinates is [a-h]3
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
            // If top square figure isn't Pawn then error
            if(topSquare[1] != game_info.figureType[0]) {
              game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
            } else {
              game_info.figurePosY = 2;
            }
          }
        // If bottom and top squares is empty then no figure found
        } else if(bottomSquare == "" && topSquare == "") {
          game_info.commandStatus = ERROR_FIGURE_NOT_FOUND;
        /* If bottom square isn't empty and top square is empty
        then bottom square is possible position of Pawn */
        } else if(bottomSquare != "" && topSquare == "") {
          game_info.figurePosY = 1;
        /* If bottom square is empty and top square isn't empty
        then top square is possible position of Pawn */
        } else if(bottomSquare == "" && topSquare != "") {
          game_info.figurePosY = 2;
        }
      // In this case figure position is Y destination position - 1
      } else if(game_info.endPosY > 1) {
        game_info.figurePosY = game_info.endPosY - 1;
      }
    // If player is black then 
    } else {
      if(game_info.endPosY == 4) {
        // Bottom figure coordinates is [a-h]7
        const char * bottomSquare = chessPositionArray[6][game_info.endPosX];
        // Top figure coordinates is [a-h]6
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
            // If top square figure isn't Pawn then error
            if(topSquare[1] != game_info.figureType[0]) {
              game_info.commandStatus = ERROR_PATH_BLOCKED_BY_ALLY;
            } else {
              game_info.figurePosY = 5;
            }
          }
        // If bottom and top squares is empty then no figure found
        } else if(bottomSquare == "" && topSquare == "") {
          game_info.commandStatus = ERROR_FIGURE_NOT_FOUND;
        /* If bottom square isn't empty and top square is empty
        then bottom square is possible position of Pawn */
        } else if(bottomSquare != "" && topSquare == "") {
          game_info.figurePosY = 6;
        /* If bottom square is empty and top square isn't empty
        then top square is possible position of Pawn */
        } else if(bottomSquare == "" && topSquare != "") {
          game_info.figurePosY = 5;
        }
      // In this case figure position is Y destination position + 1
      } else if(game_info.endPosY < 6) {
        game_info.figurePosY = game_info.endPosY + 1;
      } 
    }
  // If square isn't empty
  } else {
    /* Calculate Y coordinate of Pawn
    Just add 1 to Y coordinate if black or substract 1 if white player */
    if(game_info.player == "white") {
      game_info.figurePosY = game_info.endPosY - 1;
    } else {
      game_info.figurePosY = game_info.endPosY + 1;
    }

    if(game_info.endPosX > 0 & game_info.endPosX < 7) {
      /* When Pawn attack he can be only to the right of enemy figure
      or to the left of enemy figure */

      /* For black player left figure will on another side
      then white player left figure, so declare here offset
      that will change his value with changing player*/
      int offsetX;
      if(game_info.player == "white") {
        offsetX = -1;
      } else {
        offsetX = 1;
      }

      const char * leftSquare = chessPositionArray[game_info.figurePosY][game_info.endPosX-offsetX];
      const char * rightSquare = chessPositionArray[game_info.figurePosY][game_info.endPosX+offsetX];

      /* Check if left and right square isn't empty if not
      then check if left isn't empty if not
      then check if right isn't empty */
      if(rightSquare != "" && leftSquare != "") {
        // If it's not player figure 
        if(leftSquare[0] != game_info.player[0] 
        && rightSquare[0] != game_info.player[0]) {
          game_info.commandStatus = ERROR_NON_PLAYER_S_FIGURE;
        /* If leftSquare isn't player figure, 
        then rightSquare is a possible position of figure */
        } else if (leftSquare[0] != game_info.player[0]) {
          game_info.figurePosX = game_info.endPosX + offsetX;
        /* If rightSquare isn't player figure, 
        then leftSquare is a possible position of figure */
        } else if (rightSquare[0] != game_info.player[0]) {
          game_info.figurePosX = game_info.endPosX - offsetX;
        /* Last case all figures are player's, then 
        assign coordinate of left figure by default */
        } else {
          game_info.figurePosX = game_info.endPosX - offsetX;
        }
      // if rightSquare isn't empty then it's possible position of figure
      } else if(rightSquare != "") {
        game_info.figurePosX = game_info.endPosX + offsetX;
      // if leftSquare isn't empty then it's possible position of figure
      } else if(leftSquare != "") {
        game_info.figurePosX = game_info.endPosX - offsetX;
      }
    } else {
      /* If enemy's figure are at the border coordinate - A or H
      then player's attacking Pawn will be at B(1) or G(6) coordinate*/
      if(game_info.endPosX == 0) {
        game_info.figurePosX = 1;
      } else if(game_info.endPosX == 7) {
        game_info.figurePosX = 6;
      }
    }
  }
}

// Print chess board and all chess figures position
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
