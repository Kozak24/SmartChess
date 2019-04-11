#ifndef COMMAND_CHECKING_H
#define COMMAND_CHECKING_H
    
#include "project.h"
    
// Function that return type of piece
const char * get_chess_piece_type(char chessPieceLetter);
// Check if square is empty
uint8 is_square_empty(const char * coordinates);
// Check if piece is ally
void is_piece_ally(uint8 * square);
// Check if destination piece is king
uint8 is_destination_piece_king(void);
// Check if piece is on the square and is it player piece
void is_piece_on_the_square(void);
/* Checks by string paramater is this piece 
that we are looking for */
uint8 is_piece_found(uint8 * squareInfo);
    
#endif
