//
// Created by dalae on 2023-03-17.
//

#ifndef CHESS_MINIMAX_MINIMAX_H
#define CHESS_MINIMAX_MINIMAX_H

#include "move_rules.h"

struct Minimax{
    struct Move move;
    long long score;
};

struct Minimax minimax(struct Piece** board, short depth, long long alpha, long long beta, enum Colour turn);

long long evaluate_board(struct Piece** board, enum  Colour colour);

enum Colour is_checked(struct Piece** board);

short is_allowed(struct Piece** board, struct Move move);

#endif //CHESS_MINIMAX_MINIMAX_H
