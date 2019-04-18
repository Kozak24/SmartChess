#ifndef CHESS_ALGORITHM_H
#define CHESS_ALGORITHM_H
    #include "project.h"
    
    #define START_GAME   (1)

    #define EMPTY_SQUARE (0)
    #define WHITE_PLAYER (1)
    #define BLACK_PLAYER (2)   
    
    #define PLAYER_INDEX (0)
    #define PIECE_INDEX  (1)

enum CommandStatuses{
  RIGHT_COMMAND = 0x01, ERROR_IS_ALLY = 0x02, ERROR_PIECE_NOT_FOUND = 0x03,
  ERROR_NON_PLAYER_S_PIECE = 0x04, ERROR_PATH_BLOCKED_BY_ENEMY = 0x05,
  ERROR_PATH_BLOCKED_BY_ALLY = 0x06, ERROR_PIECE_TYPE_DON_T_MATCH = 0x07,
  ERROR_DESTINATION_PIECE_IS_KING = 0x08, ERROR_COORDINATES_OUT_OF_RANGE = 0x09,
  // RESERVED addresses for errors
  COMMAND_IS_PROCESSING = 0x10, COMMAND_IS_PROCESSED = 0x11
};

typedef struct {
  uint8 player;

  // Coordinates of piece
  uint8 piecePosX;
  uint8 piecePosY;

  /* Coordinates where piece will move 
  and info about square where will piece move*/
  uint8 isSquareEmpty;
  uint8 endPosX;
  uint8 endPosY; 

  // Piece type for validation and checks
  const char * pieceType;

  // Store info about command
  enum CommandStatuses commandStatus;
} game_info_t;

// Link global variables
extern game_info_t game_info;
extern uint8 chessPositionArray[8][8][2];
extern const char * chessPiecesTypesArray[6];
extern char chessPiecesLettersArray[6];
extern char bufferForSpritnf[35];
    
// Validation of input command 
void validate_command(char * command);

// Check if command coordinates is rightly formed [a-h][1-8]
uint8 is_coordinates_range_right(char * coordinates);

// When we starting new game we need move all pieces to start position and set WHITE player 
void start_game(void);

// Change Pawn piece to Queen when reached other side of board
void pawn_become_queen(void);

// Generate GCODE commands
void generate_gcode(void);

// Function that marks current command to processed status, calls from GRBL go_idle_function
void mark_chess_command_processed(void);

// Upd
void update_chess_array(void);
#endif
