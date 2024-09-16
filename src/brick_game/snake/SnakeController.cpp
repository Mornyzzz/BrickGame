#include "SnakeController.h"

namespace s21 {
SnakeController *getController() {
  static SnakeModel snakeModel;
  static SnakeController controller(&snakeModel);
  return &controller;
}

void SnakeController::field_init() { snakeModel->field_init(); }

GameInfo_t SnakeController::updateField() { return snakeModel->updateField(); }

int SnakeController::get_size() { return snakeModel->get_size(); }

void SnakeController::set_direction_left() {
  snakeModel->set_direction((snakeModel->get_direction() + 3) % 4);
}

void SnakeController::set_direction_right() {
  snakeModel->set_direction((snakeModel->get_direction() + 1) % 4);
}

int SnakeController::get_direction() { return snakeModel->get_direction(); }

void SnakeController::init_snake() {
  for (int i = 0; i < 200; i++) {
    snakeModel->set_cord(i, 0, -5);
    snakeModel->set_cord(i, 1, -5);
  }
  snakeModel->set_cord(0, 0, 11);
  snakeModel->set_cord(0, 1, 4);  //голова
  snakeModel->set_cord(1, 0, 10);
  snakeModel->set_cord(1, 1, 4);
  snakeModel->set_cord(2, 0, 9);
  snakeModel->set_cord(2, 1, 4);
  snakeModel->set_cord(3, 0, 8);
  snakeModel->set_cord(3, 1, 4);
  snakeModel->set_size(4);
  snakeModel->set_direction(1);
  snakeModel->null_field();
  snakeModel->set_apple();
}

void SnakeController::set_time(clock_t new_time) {
  snakeModel->set_time(new_time);
}

void SnakeController::field_delete() { snakeModel->field_delete(); }

void SnakeController::userInput(UserAction_t action) {
  switch (*getGameState()) {
    case GAMESTART:
      init_snake();
      snakeModel->gamestart_gs();
      break;

    case MOVE:
      snakeModel->move_gs(action);
      break;

    case SHIFT:
      snakeModel->figure_go();
      break;

    case GROW:
      snakeModel->snake_grow();
      break;

    case WIN:
      snakeModel->set_state(GAMEOVER);
      break;

    case COLLIDE:
      snakeModel->set_state(GAMEOVER);
      break;

    case PAUSE:
      snakeModel->pause_gs(action);
      break;

    case GAMEOVER:
      snakeModel->set_state(MENU);
      break;

    case MENU:
      snakeModel->menu_gs(action);
      break;
    default:
      break;
  }
}
}  // namespace s21
