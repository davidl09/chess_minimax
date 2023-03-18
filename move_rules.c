//
// Created by dalae on 2023-03-13.
//
#include "move_rules.h"

const int knight_moves[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
const int king_moves[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

void threaten(struct Piece** board, int row, int col, enum Colour colour) {
    if(board[row][col].threat == BOTH || board[row][col].threat == (enum Threats) colour || board[row][col].colour == colour)
        return;
    if(board[row][col].threat == SAFE) {
        board[row][col].threat = (enum Threats) colour;
        return;
    }
    board[row][col].threat = BOTH;
}

void update_threats(struct Piece** board){
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            board[i][j].threat = SAFE;
        }
    }
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if(board[i][j].type == PAWN){
                //break;
                if(board[i][j].type == PAWN){
                    if(board[i][j].colour == WHITE){
                        threaten(board, i - 1, j + 1, WHITE);
                        threaten(board, i - 1, j - 1, WHITE);
                    }
                    else{
                        threaten(board, i + 1, j + 1, BLACK);
                        threaten(board, i + 1, j - 1, BLACK);
                    }
                }
            }
            if(board[i][j].type == KNIGHT){//break;
                for (int k = 0; k < 8; ++k) {
                    if (is_valid_square(i + knight_moves[k][0], j + knight_moves[k][1]) != False) {
                        threaten(board, i + knight_moves[k][0], j + knight_moves[k][1], board[i][j].colour);
                    }
                }
            }

            if(board[i][j].type == BISHOP){//break;
                short k = 1;
                while (True) {
                    if (is_valid_square(i + k, j + k) == False)
                        break;
                    if (board[i + k][j + k].colour == board[i][j].colour)
                        break;
                    threaten(board, i + k, j + k, board[i][j].colour);
                    if (board[i + k][j + k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
                k = 1;
                while (True) {
                    if (is_valid_square(i - k, j + k) == False)
                        break;
                    if (board[i - k][j + k].colour == board[i][j].colour)
                        break;
                    threaten(board, i - k, j + k, board[i][j].colour);
                    if (board[i - k][j + k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
                k = 1;
                while (True) {
                    if (is_valid_square(i + k, j - k) == False)
                        break;
                    if (board[i + k][j - k].colour == board[i][j].colour)
                        break;
                    threaten(board, i + k, j - k, board[i][j].colour);
                    if (board[i + k][j - k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
                k = 1;
                while (True) {
                    if (is_valid_square(i - k, j - k) == False)
                        break;
                    if (board[i - k][j - k].colour == board[i][j].colour)
                        break;
                    threaten(board, i - k, j - k, board[i][j].colour);
                    if (board[i - k][j - k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
            }

            if(board[i][j].type == ROOK){//break;
                for (int l = i + 1; l < BOARD_HEIGHT; ++l) {
                    if (board[l][j].colour == board[i][j].colour)
                        break;
                    threaten(board, l, j, board[i][j].colour);
                    if (board[l][j].colour == 3 - board[i][j].colour)
                        break;
                }
                for (int l = i - 1; l >= 0; --l) {
                    if (board[l][j].colour == board[i][j].colour)
                        break;
                    threaten(board, l, j, board[i][j].colour);
                    if (board[l][j].colour == 3 - board[i][j].colour)
                        break;
                }
                for (int l = j + 1; l < BOARD_WIDTH; ++l) {
                    if (board[i][l].colour == board[i][j].colour)
                        break;
                    threaten(board, i, l, board[i][j].colour);
                    if (board[i][l].colour == 3 - board[i][j].colour)
                        break;
                }
                for (int l = j - 1; l >= 0; --l) {
                    if (board[i][l].colour == board[i][j].colour)
                        break;
                    threaten(board, i, l, board[i][j].colour);
                    if (board[i][l].colour == 3 - board[i][j].colour)
                        break;
                }
            }

            if(board[i][j].type == QUEEN){//break;
                for (int l = i + 1; l < BOARD_HEIGHT; ++l) {
                    if (board[l][j].colour == board[i][j].colour)
                        break;
                    threaten(board, l, j, board[i][j].colour);
                    if (board[l][j].colour == 3 - board[i][j].colour)
                        break;
                }
                for (int l = i - 1; l >= 0; --l) {
                    if (board[l][j].colour == board[i][j].colour)
                        break;
                    threaten(board, l, j, board[i][j].colour);
                    if (board[l][j].colour == 3 - board[i][j].colour)
                        break;
                }
                for (int l = j + 1; l < BOARD_WIDTH; ++l) {
                    if (board[i][l].colour == board[i][j].colour)
                        break;
                    threaten(board, i, l, board[i][j].colour);
                    if (board[i][l].colour == 3 - board[i][j].colour)
                        break;
                }
                for (int l = j - 1; l >= 0; --l) {
                    if (board[i][l].colour == board[i][j].colour)
                        break;
                    threaten(board, i, l, board[i][j].colour);
                    if (board[i][l].colour == 3 - board[i][j].colour)
                        break;
                }
                short k = 1;
                while (True) {
                    if (is_valid_square(i + k, j + k) == False)
                        break;
                    if (board[i + k][j + k].colour == board[i][j].colour)
                        break;
                    threaten(board, i + k, j + k, board[i][j].colour);
                    if (board[i + k][j + k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
                k = 1;
                while (True) {
                    if (is_valid_square(i - k, j + k) == False)
                        break;
                    if (board[i - k][j + k].colour == board[i][j].colour)
                        break;
                    threaten(board, i - k, j + k, board[i][j].colour);
                    if (board[i - k][j + k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
                k = 1;
                while (True) {
                    if (is_valid_square(i + k, j - k) == False)
                        break;
                    if (board[i + k][j - k].colour == board[i][j].colour)
                        break;
                    threaten(board, i + k, j - k, board[i][j].colour);
                    if (board[i + k][j - k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
                k = 1;
                while (True) {
                    if (is_valid_square(i - k, j - k) == False)
                        break;
                    if (board[i - k][j - k].colour == board[i][j].colour)
                        break;
                    threaten(board, i - k, j - k, board[i][j].colour);
                    if (board[i - k][j - k].colour == 3 - board[i][j].colour)
                        break;
                    k++;
                }
            }

            if(board[i][j].type == KING){//break;
                for (int l = 0; l < 8; ++l) {
                    if (is_valid_square(i + king_moves[l][0], j + king_moves[l][1]) == 1)
                        threaten(board, i + king_moves[l][0], j + king_moves[l][1], board[i][j].colour);
                }
            }

        }
    }
}

short is_legal_move(struct Piece** board, struct Move piece) {
    if (piece.from_col == piece.to_col && piece.from_row == piece.to_row)  //if move does nothing
        return 0;
    if (piece.to_row < 0 || piece.to_row >= BOARD_HEIGHT || piece.to_col < 0 || piece.to_col >= BOARD_WIDTH) //if piece is out of bounds
        return 0;

    switch (board[piece.from_row][piece.from_col].type) {
        case NONE:
            return 0;
        case PAWN:
            switch (board[piece.from_row][piece.from_col].colour) {
                case WHITE:
                    if(piece.from_row == 6 && piece.to_row == 4 && board[piece.to_row][piece.to_col].type == NONE && board[piece.to_row + 1][piece.to_col].type == NONE && piece.to_col == piece.from_col)
                        return 1;
                    if ((piece.from_row - piece.to_row == 1 && board[piece.to_row][piece.to_col].type == NONE &&
                         piece.to_col - piece.from_col == 0) ||
                        (piece.from_row - piece.to_row == 1 && abs((piece.from_col - piece.to_col)) == 1 &&
                         board[piece.to_row][piece.to_col].colour == BLACK))
                        return 1;
                    else return 0;
                case BLACK:
                    if(piece.from_row == 1 && piece.to_row == 3 && board[piece.to_row][piece.to_col].type == NONE && board[piece.to_row - 1][piece.to_col].type == NONE && piece.to_col == piece.from_col)
                        return 1;
                    if ((piece.from_row - piece.to_row == -1 && board[piece.to_row][piece.to_col].type == NONE &&
                         piece.to_col - piece.from_col == 0) ||
                        (piece.from_row - piece.to_row == -1 && abs((piece.from_col - piece.to_col)) == 1 &&
                         board[piece.to_row][piece.to_col].colour == WHITE))
                        return 1;
                    else return 0;
                default:
                    "";
            }
        case KNIGHT:
            if (abs((piece.to_row - piece.from_row)) + abs((piece.to_col - piece.from_col)) != 3)
                return 0;
            switch (board[piece.from_row][piece.from_col].colour) { //optimize this
                case WHITE:
                    if (board[piece.to_row][piece.to_col].colour == WHITE)
                        return 0;
                    else return 1;
                case BLACK:
                    if (board[piece.to_row][piece.to_col].colour == BLACK)
                        return 0;
                    else return 1;
                default:
                    "";
            }
        case BISHOP:
            if (board[piece.from_row][piece.from_col].colour == board[piece.to_row][piece.to_col].colour)
                return 0;
            int x_dist = piece.to_col - piece.from_col;
            int y_dist = piece.to_row - piece.from_row;
            if (abs(x_dist) != abs(y_dist))
                return 0;
            for (int i = 1; i < abs(x_dist); ++i) {
                if (board[piece.from_row + i * (y_dist / abs(y_dist))][piece.from_col +
                                                                       i * (x_dist / abs(x_dist))].type != NONE) {
                    return 0;
                }
            }
            return 1;

        case ROOK:
            if (board[piece.from_row][piece.from_col].colour == board[piece.to_row][piece.to_col].colour)
                return 0;
            x_dist = piece.to_col - piece.from_col;
            y_dist = piece.to_row - piece.from_row;
            if ((x_dist == 0 ^ y_dist == 0) == False)
                return 0;

            for (int i = 1; i < abs(y_dist) || i < abs(x_dist); ++i) {
                if (x_dist == 0) {
                    if (board[piece.from_row + i * (y_dist / abs(y_dist))][piece.from_col].type != NONE)
                        return 0;
                }
                if (y_dist == 0) {
                    if (board[piece.from_row][piece.from_col + i * (x_dist / abs(x_dist))].type != NONE)
                        return 0;
                }
            }
            return 1;

        case QUEEN:
            if (board[piece.from_row][piece.from_col].colour == board[piece.to_row][piece.to_col].colour)
                return 0;
            x_dist = piece.to_col - piece.from_col;
            y_dist = piece.to_row - piece.from_row;
            if (x_dist == 0 ^ y_dist == 0) { //rook logic
                for (int i = 1; i < abs(y_dist) || i < abs(x_dist); ++i) {
                    if(x_dist == 0){
                        if (board[piece.from_row + i * (y_dist / abs(y_dist))][piece.from_col].type != NONE)
                            return 0;
                    }
                    if(y_dist == 0){
                        if (board[piece.from_row][piece.from_col + i * (x_dist / abs(x_dist))].type != NONE)
                            return 0;
                    }

                }
                return 1;

            } else if (abs(x_dist) == abs(y_dist)) { //bishop logic
                for (int i = 1; i < abs(x_dist); ++i) {
                    if (board[piece.from_row + i * (y_dist / abs(y_dist))][piece.from_col + i * (x_dist / abs(x_dist))].type !=
                        NONE) {
                        return 0;
                    }
                }
                return 1;
            } else return 0;

        case KING:
            if (board[piece.from_row][piece.from_col].colour == board[piece.to_row][piece.to_col].colour)
                return 0;
            x_dist = piece.to_col - piece.from_col;
            y_dist = piece.to_row - piece.from_row;
            if(abs(x_dist) > 1 || abs(y_dist) > 1)
                return 0;
            return 1;
    }
}
