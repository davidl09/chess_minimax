//
// Created by dalae on 2023-03-13.
//

#ifndef CHESS_MINIMAX_BOARD_UTILS_H
#define CHESS_MINIMAX_BOARD_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include "CHESS_PIECES_H.h"

enum Type{
    NONE = 0,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Colour{
    NP = 0,
    WHITE,
    BLACK
};

enum Bool{
    False = 0,
    True
};

enum Threats{
    SAFE = 0,
    THREATENED_BY_WHITE,
    THREATENED_BY_BLACK,
    BOTH
};

struct Piece{
    enum Type type;
    enum Colour colour;
    enum Threats threat;
};

char* create_piece_array();

struct Piece** create_board();

void display_board(struct Piece** board, char* pieces);

struct Move get_player_move(struct Piece** board);

short makemove(struct Piece** board, struct Move move);




#endif //CHESS_MINIMAX_BOARD_UTILS_H
