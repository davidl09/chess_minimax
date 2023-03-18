//
// Created by dalae on 2023-03-17.
//

#include "minimax.h"
#include "board_utils.h"
#include "move_rules.h"

int pawn_correction_table[BOARD_HEIGHT][BOARD_WIDTH] = {
        {  0,   0,   0,   0,   0,   0,   0,   0 },
        { 50,  50,  50,  50,  50,  50,  50,  50 },
        { 10,  10,  20,  30,  30,  20,  10,  10 },
        {  5,   5,  10,  25,  25,  10,   5,   5 },
        {  0,   0,   0,  20,  20,   0,   0,   0 },
        {  5,  -5, -10,   0,   0, -10,  -5,   5 },
        {  5,  10,  10, -20, -20,  10,  10,   5 },
        {  0,   0,   0,   0,   0,   0,   0,   0 }
};

int knight_correction_table[BOARD_HEIGHT][BOARD_WIDTH] = {
        { -50, -40, -30, -30, -30, -30, -40, -50 },
        { -40, -20,   0,   0,   0,   0, -20, -40 },
        { -30,   0,  10,  15,  15,  10,   0, -30 },
        { -30,   5,  15,  20,  20,  15,   5, -30 },
        { -30,   0,  15,  20,  20,  15,   0, -30 },
        { -30,   5,  10,  15,  15,  10,   5, -30 },
        { -40, -20,   0,   5,   5,   0, -20, -40 },
        { -50, -40, -30, -30, -30, -30, -40, -50 }
};

int bishop_correction_table[BOARD_HEIGHT][BOARD_WIDTH] = {
        { -20, -10, -10, -10, -10, -10, -10, -20 },
        { -10,   0,   0,   0,   0,   0,   0, -10 },
        { -10,   0,   5,  10,  10,   5,   0, -10 },
        { -10,   5,   5,  10,  10,   5,   5, -10 },
        { -10,   0,  10,  10,  10,  10,   0, -10 },
        { -10,  10,  10,  10,  10,  10,  10, -10 },
        { -10,   5,   0,   0,   0,   0,   5, -10 },
        { -20, -10, -10, -10, -10, -10, -10, -20 }
};

int rook_correction_table[BOARD_HEIGHT][BOARD_WIDTH] = {
        {  0,   0,   0,   0,   0,   0,   0,   0 },
        {  5,  10,  10,  10,  10,  10,  10,   5 },
        { -5,   0,   0,   0,   0,   0,   0,  -5 },
        { -5,   0,   0,   0,   0,   0,   0,  -5 },
        { -5,   0,   0,   0,   0,   0,   0,  -5 },
        { -5,   0,   0,   0,   0,   0,   0,  -5 },
        { -5,   0,   0,   0,   0,   0,   0,  -5 },
        {  0,   0,   0,   5,   5,   0,   0,   0 }
};

int queen_correction_table[BOARD_HEIGHT][BOARD_WIDTH] = {
        { -20, -10, -10,  -5,  -5, -10, -10, -20 },
        { -10,   0,   0,   0,   0,   0,   0, -10 },
        { -10,   0,   5,   5,   5,   5,   0, -10 },
        {  -5,   0,   5,   5,   5,   5,   0,  -5 },
        {   0,   0,   5,   5,   5,   5,   0,  -5 },
        { -10,   5,   5,   5,   5,   5,   0, -10 },
        { -10,   0,   5,   0,   0,   0,   0, -10 },
        { -20, -10, -10,  -5,  -5, -10, -10, -20 }
};

struct Minimax minimax(struct Piece** board, short depth, long long alpha, long long beta, enum Colour turn){

}

long long evaluate_board(struct Piece** board, enum Colour colour){
    long long score = 0;
    long long temp = 0;
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            switch(board[i][j].type){
                case NONE:
                    break;
                case PAWN:
                    temp += 100 + pawn_correction_table[i][j];
                case KNIGHT:
                    temp += 310 + knight_correction_table[i][j];
                case BISHOP:
                    temp += 320 + bishop_correction_table[i][j];
                case ROOK:
                    temp += 600 + rook_correction_table[i][j];
                case QUEEN:
                    temp += 950 + queen_correction_table[i][j];
                case KING:
                    temp += 100000;
            }
            if(board[i][j].threat == 3 - board[i][j].colour)
                temp /= 2;
            if(colour == board[i][j].colour) {
                score += temp;
                temp = 0;
            }else{
                score -= temp;
                temp = 0;
            }

        }
    }
    return score;
}

enum Colour is_checked(struct Piece** board){
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if(board[i][j].type == KING){
                if(board[i][j].threat == BOTH || board[i][j].threat == 3 - board[i][j].colour){
                    return board[i][j].colour;
                }
            }
        }
    }
    return 0;
}

short is_allowed(struct Piece** board, struct Move move){ // must pass this function a COPY of the current board
    short made_move = makemove(board, move);
    if(made_move == 0)
        return 0;
    update_threats(board);
    if(is_checked(board) == made_move)
        return 0;
    return 1;
}

