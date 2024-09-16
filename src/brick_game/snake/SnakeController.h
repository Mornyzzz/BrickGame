#ifndef BRICKGAME_SNAKECONTROLLER_H
#define BRICKGAME_SNAKECONTROLLER_H
#include "SnakeModel.h"

namespace s21 {
class SnakeController {
 private:
  SnakeModel *snakeModel;

 public:
  SnakeController(SnakeModel *m) : snakeModel(m){};
  void init_snake();
  void field_delete();
  void set_direction_left();
  void set_direction_right();
  void field_init();
  int get_size();
  int get_direction();
  GameInfo_t updateField();
  void set_time(clock_t new_time);
  void userInput(UserAction_t action);
};

SnakeController *getController();
}  // namespace s21
#endif
