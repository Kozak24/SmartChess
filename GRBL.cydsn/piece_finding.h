#ifndef PIECE_FINDING_H
#define PIECE_FINDING_H

// Offsets for knight finding
#define KNIGHT_OFFSET_Y      (2)
#define KNIGHT_OFFSET_X      (2)
#define KNIGHT_HALF_OFFSET_Y (1)
#define KNIGHT_HALF_OFFSET_X (1)

// Boundary coordinates
#define X_COORDINATE_MIN (0)
#define Y_COORDINATE_MIN (0)
#define X_COORDINATE_MAX (7)
#define Y_COORDINATE_MAX (7)

// If there is no piece on the square
#define EMPTY_SQUARE (0x00)

// Defines of pieces numbers
// White pieces
#define WHITE_PAWN      (WHITE_PLAYER + PAWN)
#define WHITE_ROOK      (WHITE_PLAYER + ROOK)
#define WHITE_KNIGHT    (WHITE_PLAYER + KNIGHT)
#define WHITE_BISHOP    (WHITE_PLAYER + BISHOP)
#define WHITE_QUEEN     (WHITE_PLAYER + QUEEN)
#define WHITE_KING      (WHITE_PLAYER + KING)
// Black pieces
#define BLACK_PAWN      (BLACK_PLAYER + PAWN)
#define BLACK_ROOK      (BLACK_PLAYER + ROOK)
#define BLACK_KNIGHT    (BLACK_PLAYER + KNIGHT)
#define BLACK_BISHOP    (BLACK_PLAYER + BISHOP)
#define BLACK_QUEEN     (BLACK_PLAYER + QUEEN)
#define BLACK_KING      (BLACK_PLAYER + KING)
    
#define PAWN    (0x01)
#define ROOK    (0x02)
#define KNIGHT  (0x03)
#define BISHOP  (0x04)
#define QUEEN   (0x05)
#define KING    (0x06)
    
#define FIRST_LETTER (0)
    
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
