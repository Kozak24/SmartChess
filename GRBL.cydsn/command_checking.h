#ifndef COMMAND_CHECKING_H
#define COMMAND_CHECKING_H
    
#include "project.h"
    
// Function that return index of piece
uint8 get_piece_index_from_letter(char chessPieceLetter);
// Set destination position
void set_dest_position(const char * coordinates);
// Check if square is empty
uint8 is_square_empty(void);
// Check if piece is ally
void is_piece_ally(uint8 square);
// Check if destination piece is king
uint8 is_destination_piece_king(void);
// Check if piece is on the square and is it player piece
void is_piece_on_the_square(void);
/* Checks by string paramater is this piece 
that we are looking for */
uint8 is_piece_found(uint8 squareInfo);
// Function that return piece index
uint8 get_piece_index(uint8 piece);
// Function that return player
uint8 get_player(uint8 piece);
// Function that return piece type
uint8 get_piece_type(uint8 piece);
    
#endif
