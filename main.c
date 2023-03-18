#include "board_utils.h"
#include "move_rules.h"

int main() {
    struct Move move;
    struct Piece** board = create_board();
    char* piece_array = create_piece_array();
    update_threats(board);
    display_board(board, piece_array);
    while(1){
        move = get_player_move(board);
        makemove(board, move);
        update_threats(board);
        display_board(board, piece_array);
    }
}
