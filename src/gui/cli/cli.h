#ifndef CPP3_BRICKGAME_V2_0_1_CLI_C_H
#define CPP3_BRICKGAME_V2_0_1_CLI_C_H
#include <ncurses.h>

#include "../../brick_game/brickgame.h"
#include "../../brick_game/snake/SnakeController.h"
#include "../../brick_game/tetris/tetrisBackend.h"

void display_information();
WINDOW* cli_init();
WINDOW* tetris_menu_init();
void print_blank(WINDOW* win);
void print_tetris_blink(WINDOW* win);
void print_snake_blink(WINDOW* win);
void print_tetris_game(WINDOW* win);
void print_snake_game(WINDOW* win);
void startTetrisEventLoop(WINDOW* win);
void startSnakeEventLoop(WINDOW* win);

#endif
