#include <stdio.h>

enum ErrorCodes{
  RIGHT_COMMAND = 0x01, ERROR_IS_ALLY = 0x02, ERROR_FIGURE_NOT_FOUND = 0x03,
  ERROR_NON_PLAYER_S_FIGURE = 0x04
};

/* default array on start need this to quick restore
const char * chessPositionArray[8][8] = {
  {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"},
  {"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
  {"", "", "", "", "", "", "", ""},
  {"", "", "", "", "", "", "", ""},
  {"", "", "", "", "", "", "", ""},
  {"", "", "", "", "", "", "", ""},
  {"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
  {"bR", "bN", "bB", "bK", "bQ", "bB", "bN", "bR"}
};*/

// Array of chess position on the Chess board
const char * chessPositionArray[8][8] = {
  {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"},
  {"", "wP", "", "wP", "", "wP", "", "wP"},
  {"", "", "", "", "", "", "", ""},
  {"wP", "", "wP", "", "wP", "", "wP", ""},
  {"", "bP", "", "bP", "", "bP", "", "bP"},
  {"", "", "", "", "", "", "", ""},
  {"bP", "", "bP", "", "bP", "", "bP", ""},
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
const char * commandArray[5] = {
    "h5", "e7", "a4", "d5", "e4"
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

void find_figure();
void find_pawn();
void is_figure_on_the_square();

void validate_path();

void print_chess_position_array();

int main(void) {
  game_info.player = "white";

  print_chess_position_array();
  for(int i = 0; i < 5; i++) {
    validate_command(commandArray[i]);
  }
}

void validate_command(const char *command) {
  game_info.commandStatus = RIGHT_COMMAND;
  printf("\nPlayer is %s\n", game_info.player);
  printf("Command %s\n", command);
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

  /* If bad command then quit function and wait for the next command
  in other case find figure */
  for(int validationStep = 0; validationStep < 3; validationStep++) {
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
      } else if (validationStep == 2) {
        //validate_path(figureType);
      }
    }
  }

  printf("\nFigure - %s X%dY%d -> X%dY%d\n", game_info.figureType, game_info.figurePosX, game_info.figurePosY, game_info.endPosX, game_info.endPosY);

  // Change player if command is right or leave the same player if command isn't right
  if(game_info.commandStatus == RIGHT_COMMAND) {
    if(game_info.player == "white") {
      game_info.player = "black";
    } else {
      game_info.player = "white";
    }
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

void find_pawn() {
  game_info.figurePosX = 0;
  game_info.figurePosY = 0;
  if(game_info.isSquareEmpty) {
    printf("Find Pawn");
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
      int offset;
      if(game_info.player == "white") {
        offset = -1;
      } else {
        offset = 1;
      }

      const char * leftSquare = chessPositionArray[game_info.figurePosY][game_info.endPosX-offset];
      const char * rightSquare = chessPositionArray[game_info.figurePosY][game_info.endPosX+offset];

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
          game_info.figurePosX = game_info.endPosX + offset;
        /* If rightSquare isn't player figure, 
        then leftSquare is a possible position of figure */
        } else if (rightSquare[0] != game_info.player[0]) {
          game_info.figurePosX = game_info.endPosX - offset;
        /* Last case all figures are player's, then 
        assign coordinate of left figure by default */
        } else {
          game_info.figurePosX = game_info.endPosX - offset;
        }
      // if rightSquare isn't empty then it's possible position of figure
      } else if(rightSquare != "") {
        game_info.figurePosX = game_info.endPosX + offset;
      // if leftSquare isn't empty then it's possible position of figure
      } else if(leftSquare != "") {
        game_info.figurePosX = game_info.endPosX - offset;
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

/* Check if figure is on the square and is it player figure, 
if not then assign to command status error code*/
void is_figure_on_the_square() {
  const char * figure = chessPositionArray[game_info.figurePosY][game_info.figurePosX];
  if(figure != "") {
    if(figure[0] != game_info.player[0]) {
      game_info.commandStatus = ERROR_NON_PLAYER_S_FIGURE;
    }
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
  printf("Figure type - %s\n", chessFigureType);
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
  if(chessPositionArray[game_info.endPosY][game_info.endPosX]) {
    printf("Square isn't empty\n");
    is_figure_ally(
      chessPositionArray[game_info.endPosY][game_info.endPosX]);
    return 0;
  } else {
    printf("Square is empty\n");
    return 1;
  }
}

//Check if figure is ally
void is_figure_ally(const char * figure) {
  if(figure[0] == game_info.player[0]) {
    printf("Figure is ally (BAD COMMAND)\n");
    game_info.commandStatus = ERROR_IS_ALLY;
  } else {
    printf("Figure is enemy\n");
  }
}

void validate_path(const char * figureType) {
  if(figureType == "Pawn") {
    // Check Pawn path
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

// Print chess board and all chess figures position
void print_chess_position_array() {
    for(int y = 0; y < 8; y++) {
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
}
