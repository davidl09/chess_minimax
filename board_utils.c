//
// Created by dalae on 2023-03-13.
//
#include "board_utils.h"
#include "move_rules.h"
#include "CHESS_PIECES_H.h"
#include "colours.h"

struct Move get_player_move(struct Piece** board){
    struct Move move;
    printf("Enter the column of the piece you would like to move\n");
    scanf("%hd", &move.from_col);
    printf("Enter the row of the piece you would like to move\n");
    scanf("%hd", &move.from_row);
    printf("Enter the column toward which you would like to move the piece\n");
    scanf("%hd", &move.to_col);
    printf("Enter the row toward which you would like to move the piece\n");
    scanf("%hd", &move.to_row);
    if(is_legal_move(board, move) == False){
        printf("That is an illegal move, please try again\n");
        return get_player_move(board);
    }
    return move;
}

struct Piece** create_board(){
    struct Piece** board = malloc(BOARD_HEIGHT * sizeof(struct Piece*));

    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        board[i] = malloc(BOARD_WIDTH * sizeof(struct Piece));
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            board[i][j].threat = SAFE;

        }
    }

    for (short i = 2; i < BOARD_HEIGHT - 2; ++i) {
        for (short j = 0; j < BOARD_WIDTH; ++j){
            board[i][j] = (struct Piece){.type = NONE};
        }
    }

    for (int i = 0; i < BOARD_WIDTH; ++i) {
        board[1][i] = (struct Piece){.type = PAWN, .colour = BLACK};
        board[6][i] = (struct Piece){.type = PAWN, .colour = WHITE};
    }

// Add rooks
    board[0][0] = (struct Piece){.type = ROOK, .colour = BLACK};
    board[0][7] = (struct Piece){.type = ROOK, .colour = BLACK};
    board[7][0] = (struct Piece){.type = ROOK, .colour = WHITE};
    board[7][7] = (struct Piece){.type = ROOK, .colour = WHITE};

// Add knights
    board[0][1] = (struct Piece){.type = KNIGHT, .colour = BLACK};
    board[0][6] = (struct Piece){.type = KNIGHT, .colour = BLACK};
    board[7][1] = (struct Piece){.type = KNIGHT, .colour = WHITE};
    board[7][6] = (struct Piece){.type = KNIGHT, .colour = WHITE};

// Add bishops
    board[0][2] = (struct Piece){.type = BISHOP, .colour = BLACK};
    board[0][5] = (struct Piece){.type = BISHOP, .colour = BLACK};
    board[7][2] = (struct Piece){.type = BISHOP, .colour = WHITE};
    board[7][5] = (struct Piece){.type = BISHOP, .colour = WHITE};

// Add queens
    board[0][3] = (struct Piece){.type = QUEEN, .colour = BLACK};
    board[7][3] = (struct Piece){.type = QUEEN, .colour = WHITE};

// Add kings
    board[0][4] = (struct Piece){.type = KING, .colour = BLACK};
    board[7][4] = (struct Piece){.type = KING, .colour = WHITE};

    return board;
}

char* create_piece_array(){
    char* pieces = malloc(13*sizeof(char));
    pieces[EMPTY] = '-';
    pieces[WHITE_PAWN] = 'P';
    pieces[WHITE_KNIGHT] = 'N';
    pieces[WHITE_BISHOP] = 'B';
    pieces[WHITE_ROOK] = 'R';
    pieces[WHITE_QUEEN] = 'Q';
    pieces[WHITE_KING] = 'K';
    pieces[BLACK_PAWN] = 'p';
    pieces[BLACK_KNIGHT] = 'n';
    pieces[BLACK_BISHOP] = 'b';
    pieces[BLACK_ROOK] = 'r';
    pieces[BLACK_QUEEN] = 'q';
    pieces[BLACK_KING] = 'k';
    return pieces;
}

short makemove(struct Piece** board, struct Move move){
    if(is_legal_move(board, move) == 1){
        board[move.to_row][move.to_col] = board[move.from_row][move.from_col];
        board[move.from_row][move.from_col].colour = NP;
        board[move.from_row][move.from_col].type = NONE;
        return board[move.to_row][move.to_col].colour;
    }
    return 0;
}

void display_board(struct Piece** board, char* pieces){
    printf("\n");
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        printf("%d  ", i);
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            board[i][j].threat == SAFE ? colourChange(WHITE_) : (board[i][j].threat == THREATENED_BY_WHITE ? colourChange(BLUE) : (board[i][j].threat == THREATENED_BY_BLACK ? colourChange(RED) : colourChange(GREEN)));
            board[i][j].colour == WHITE ? printf("W%c ", pieces[board[i][j].type]) : (board[i][j].colour == BLACK ? printf("B%c ", pieces[board[i][j].type]) : printf("X  "));
            colourChange(WHITE_);
        }
        printf("\n");
    }
    printf("   ");
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        printf("%d  ", i);
    }
    printf("\n");
}

