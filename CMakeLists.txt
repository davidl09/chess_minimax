cmake_minimum_required(VERSION 3.23)
project(chess_minimax C)

set(CMAKE_C_STANDARD 99)

add_executable(chess_minimax main.c board_utils.c board_utils.h CHESS_PIECES_H.h move_rules.c move_rules.h colours.h minimax.c minimax.h)
