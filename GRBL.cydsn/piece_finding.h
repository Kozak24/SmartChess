#ifndef PIECE_FINDING_H
#define PIECE_FINDING_H

#define KNIGHT_OFFSET_Y      (2)
#define KNIGHT_OFFSET_X      (2)
#define KNIGHT_HALF_OFFSET_Y (1)
#define KNIGHT_HALF_OFFSET_X (1)
    
#define X_COORDINATE_MIN (0)
#define Y_COORDINATE_MIN (0)
#define X_COORDINATE_MAX (7)
#define Y_COORDINATE_MAX (7)
    
#define KNIGHT_PIECE (2)
    
#include "project.h"
    
// Find piece by the piece type
void find_piece(void);
// Fucntion that find Pawn on the chess board
void find_pawn(void);
// Function that find Knight on the chess board
void find_knight(void);
// Function that find piece by horizontal path
void find_by_horizontal(void);
// Function that find piece by vertical path
void find_by_vertical(void);
// Function that find piece by diagonal path
void find_by_diagonal(void);
    
#endif
