//
// Created by dalae on 2023-03-13.
//

#ifndef CHESS_MINIMAX_MOVE_RULES_H
#define CHESS_MINIMAX_MOVE_RULES_H

#include "board_utils.h"
#include <stdlib.h>
#include <stdio.h>

#define max(a, b) a > b ? a : b
#define is_valid_square(row, col) (row < BOARD_HEIGHT && row >= 0 ? (col < BOARD_WIDTH && col >= 0 ? 1 : 0) : 0)

struct Move{
    short from_row;
    short from_col;
    short to_row;
    short to_col;
};

void threaten(struct Piece** board, int row, int col, enum Colour colour);

void update_threats(struct Piece** board);

short is_legal_move(struct Piece** board, struct Move piece);


#endif //CHESS_MINIMAX_MOVE_RULES_H
