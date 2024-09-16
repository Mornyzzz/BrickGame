#ifndef C7_BRICKGAME_V1_0_1_TETRISBACKEND_H
#define C7_BRICKGAME_V1_0_1_TETRISBACKEND_H

#include "../brickgame.h"

void shift_matrix(int n);
int check_collision();
void rotate_figure();
void rotate_one_time_figure();
void figure_left();
void figure_right();
void figure_down();
void fill_figure(TetFigure *figure, int type);
int update_cords(TetFigure *figure);
void null_figure(TetFigure *figure);
void copy_figure(TetFigure src, TetFigure *dest);
void game_init();
void set_tetris_screen();
void remove_lines();
void figure_to_next(TetFigure figure);
void updateField();
TetFigure *getFigure();
void set_state(game_state new_state);
int attach_figure();
void null_field();
void userTetrisEvent(UserAction_t action);

#endif
