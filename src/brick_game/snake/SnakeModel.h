#ifndef BRICKGAME_SNAKEMODEL_H
#define BRICKGAME_SNAKEMODEL_H
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "../brickgame.h"
namespace s21 {
class SnakeModel {
 private:
  int cords[200][2]{};
  int direction;
  int size;
  clock_t start_time;
  bool switchEntered;

 public:
  SnakeModel();
  void field_init();
  void null_field();
  void field_delete();
  int figure_go();
  int check_collision();
  void set_apple();
  void set_direction(int new_direction) { this->direction = new_direction; };
  int get_direction() { return direction; };
  void set_size(int new_size) { this->size = new_size; };
  int get_size() { return size; };
  void set_time(clock_t new_time) { this->start_time = new_time; };
  clock_t get_time() { return start_time; };
  int get_cord(int a, int b) { return cords[a][b]; }
  void set_cord(int a, int b, int value) { cords[a][b] = value; }
  int snake_grow();
  GameInfo_t updateField();
  void set_snake_screen();
  void set_state(game_state new_state);
  void gamestart_gs();
  void move_gs(UserAction_t action);
  void pause_gs(UserAction_t action);
  void menu_gs(UserAction_t action);
};
}  // namespace s21

#endif
