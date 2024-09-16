#include "SnakeModel.h"

namespace s21 {
SnakeModel::SnakeModel()
    : direction(0), size(0), start_time(0), switchEntered(false) {
  for (auto &cord : cords) {
    cord[0] = -5;
    cord[1] = -5;
  }
  this->cords[0][0] = 11;
  this->cords[0][1] = 4;  //голова
  this->cords[1][0] = 10;
  this->cords[1][1] = 4;
  this->cords[2][0] = 9;
  this->cords[2][1] = 4;
  this->cords[3][0] = 8;
  this->cords[3][1] = 4;
  this->size = 4;
}

void SnakeModel::set_state(game_state new_state) {
  game_state *state = getGameState();
  *state = new_state;
}

int SnakeModel::snake_grow() {
  game_state *state = getGameState();
  set_cord(get_size(), 0, get_cord(get_size() - 1, 0));
  set_cord(get_size(), 1, get_cord(get_size() - 1, 1));
  set_size(get_size() + 1);

  if (get_size() == 200) {
    *state = WIN;
  } else {
    *state = MOVE;
    start_time = clock();
    set_apple();
  }
  return *state;
}

void SnakeModel::set_snake_screen() {
  GameInfo_t *gameInfo = getGameInfo();
  int matrix[20][10] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5,
      5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5,
      0, 5, 0, 5, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 0, 0, 5, 0, 0, 5, 5, 0,
      0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 5, 5,
      5, 5, 5, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0,
      0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i][j] = matrix[i][j];
    }
  }
}

GameInfo_t SnakeModel::updateField() {
  GameInfo_t *gameInfo = getGameInfo();
  game_state *snake_state = getGameState();
  if (*snake_state == GAMEOVER || *snake_state == COLLIDE ||
      *snake_state == GAMESTART || *snake_state == MENU) {
    return *gameInfo;
  }
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (gameInfo->field[i][j] == 1 || gameInfo->field[i][j] == 3) {
        gameInfo->field[i][j] = 0;
      }
    }
  }
  gameInfo->field[this->get_cord(0, 0)][this->get_cord(0, 1)] = 3;
  for (int i = 1; i < this->get_size(); i++) {
    gameInfo->field[this->get_cord(i, 0)][this->get_cord(i, 1)] = 1;
  }
  return *gameInfo;
}

void SnakeModel::field_init() {
  GameInfo_t *gameInfo = getGameInfo();
  gameInfo->field = new int *[20];
  for (int i = 0; i < 20; i++) {
    gameInfo->field[i] = new int[10];
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i][j] = 0;
    }
  }
}

void SnakeModel::null_field() {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i][j] = 0;
    }
  }
}

int SnakeModel::check_collision() {
  for (int i = 1; i < 200; i++) {
    if (this->cords[0][0] == this->cords[i][0] &&
        this->cords[0][1] == this->cords[i][1])
      return 1;
  }
  if (this->cords[0][0] == -1 || this->cords[0][0] == 20) return 1;
  if (this->cords[0][1] == -1 || this->cords[0][1] == 10) return 1;
  return 0;
}

int SnakeModel::figure_go() {
  GameInfo_t gameInfo = *getGameInfo();
  game_state *state = getGameState();
  *state = MOVE;

  for (int i = this->size - 1; i > 0; i--) {
    this->cords[i][0] = this->cords[i - 1][0];
    this->cords[i][1] = this->cords[i - 1][1];
  }

  if (this->direction == 2) {
    this->cords[0][1]--;  // left
  }
  if (this->direction == 0) {
    this->cords[0][1]++;  // right
  }
  if (this->direction == 1) {
    this->cords[0][0]++;  // down
  }
  if (this->direction == 3) {
    this->cords[0][0]--;  // up
  }

  if (check_collision())
    *state = COLLIDE;

  else if (gameInfo.field[this->cords[0][0]][this->cords[0][1]] == 2) {
    *state = GROW;
  } else {
    start_time = clock();
  }
  return *state;
}

void SnakeModel::set_apple() {
  GameInfo_t *gameInfo = getGameInfo();
  int temp[20][10] = {0};
  for (int i = 0; i < this->size; i++) {
    temp[this->cords[i][0]][this->cords[i][1]] = 1;
  }

  int count_free_cells = 200 - this->size;
  int apple_cell = rand() % count_free_cells;

  for (int i = 0; i < 200; i++) {
    if (apple_cell == 0 && temp[i / 10][i % 10] != 1) {
      gameInfo->field[i / 10][i % 10] = 2;
      break;
    }
    if (temp[i / 10][i % 10] != 1) {
      apple_cell--;
    }
  }
}

void SnakeModel::field_delete() {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 20; i++) {
    delete[] gameInfo->field[i];
  }
  delete[] gameInfo->field;
}

void SnakeModel::gamestart_gs() {
  start_time = clock();
  set_state(MOVE);
}

void SnakeModel::move_gs(UserAction_t action) {
  if (clock() - start_time > WAIT_TIME) {
    set_state(SHIFT);
    switchEntered = false;
  }
  if (!switchEntered) {
    switch (action) {
      case Left:
        set_direction((get_direction() + 3) % 4);
        switchEntered = true;
        break;
      case Right:
        set_direction((get_direction() + 1) % 4);
        switchEntered = true;
        break;
      case Action:
        set_state(SHIFT);
        break;
      case Pause:
        set_state(PAUSE);
        break;
      case Terminate:
        set_state(GAMEOVER);
        break;
      default:
        break;
    }
  }
  updateField();
}

void SnakeModel::pause_gs(UserAction_t action) {
  switch (action) {
    case Terminate:
      set_state(GAMEOVER);
      break;
    case Pause:
      start_time = clock();
      set_state(MOVE);
      break;
    default:
      break;
  }
}

void SnakeModel::menu_gs(UserAction_t action) {
  set_snake_screen();
  switch (action) {
    case Start:
      set_state(GAMESTART);
      break;
    default:
      break;
  }
}
}  // namespace s21
