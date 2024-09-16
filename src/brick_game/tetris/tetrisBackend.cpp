#include "tetrisBackend.h"

void copy_figure(TetFigure src, TetFigure *dest) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dest->blocks[i][j] = src.blocks[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      dest->block_cords[i][j] = src.block_cords[i][j];
    }
  }
}

void game_init() {
  GameInfo_t *gameInfo = getGameInfo();
  gameInfo->field = (int **)calloc(24, sizeof(int *));
  for (int i = 0; i < 24; i++) {
    gameInfo->field[i] = (int *)calloc(10, sizeof(int));
  }
  gameInfo->next = (int **)calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    gameInfo->next[i] = (int *)calloc(4, sizeof(int));
  }
}

void null_field() {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 10; j++) gameInfo->field[i][j] = 0;
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) gameInfo->next[i][j] = 0;
  }
}

void null_figure(TetFigure *figure) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure->blocks[i][j] = 0;
    }
  }
}

int update_cords(TetFigure *figure) {
  GameInfo_t *gameInfo = getGameInfo();
  int count = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure->blocks[i][j] != 0 && !(i == 1 && j == 2)) {
        figure->block_cords[count][0] = figure->block_cords[0][0] + (i - 1);
        figure->block_cords[count][1] = figure->block_cords[0][1] + (j - 2);
        if (gameInfo->field[figure->block_cords[count][0]]
                           [figure->block_cords[count][1]] == 1) {
          return 0;
        }
        count++;
      }
    }
  }
  return 1;
}

void figure_to_next(TetFigure figure) {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gameInfo->next[i][j] = figure.blocks[i][j];
    }
  }
}

void fill_figure(TetFigure *figure, int type) {
  null_figure(figure);
  figure->block_cords[0][0] = 2;
  figure->block_cords[0][1] = 5;  //координаты точки - центра тяжести
  switch (type) {
    case 1:
      figure->blocks[1][1] = 1;  //[][]
      figure->blocks[1][2] = 1;  //[][]
      figure->blocks[2][1] = 1;
      figure->blocks[2][2] = 1;
      break;
    case 2:
      figure->blocks[1][0] = 1;  //[][][][]
      figure->blocks[1][1] = 1;
      figure->blocks[1][2] = 1;
      figure->blocks[1][3] = 1;
      break;
    case 3:
      figure->blocks[2][1] = 1;  //  [][]
      figure->blocks[2][2] = 1;  //[][]
      figure->blocks[1][2] = 1;
      figure->blocks[1][3] = 1;
      break;
    case 4:
      figure->blocks[1][1] = 1;  //[][]
      figure->blocks[1][2] = 1;  //  [][]
      figure->blocks[2][2] = 1;
      figure->blocks[2][3] = 1;
      break;
    case 5:
      figure->blocks[1][1] = 1;  //    []
      figure->blocks[1][2] = 1;  //[][][]
      figure->blocks[1][3] = 1;
      figure->blocks[0][3] = 1;
      break;
    case 6:
      figure->blocks[0][1] = 1;  //[]
      figure->blocks[1][1] = 1;  //[][][]
      figure->blocks[1][2] = 1;
      figure->blocks[1][3] = 1;
      break;
    case 7:
      figure->blocks[0][2] = 1;  //  []
      figure->blocks[1][1] = 1;  //[][][]
      figure->blocks[1][2] = 1;
      figure->blocks[1][3] = 1;
      break;
    default:
      break;
  }
  update_cords(figure);
}

void figure_down() {
  TetFigure *figure = getFigure();
  for (int i = 0; i < 4; i++) {
    figure->block_cords[i][0]++;
  }
}

void figure_right() {
  TetFigure *figure = getFigure();
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 4; i++) {
    if (figure->block_cords[i][1] >= 9) return;
    if (gameInfo->field[figure->block_cords[i][0]]
                       [figure->block_cords[i][1] + 1] == 1)
      return;
  }
  for (int i = 0; i < 4; i++) {
    figure->block_cords[i][1]++;
  }
}

void figure_left() {
  TetFigure *figure = getFigure();
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 4; i++) {
    if (figure->block_cords[i][1] == 0) return;
    if (gameInfo->field[figure->block_cords[i][0]]
                       [figure->block_cords[i][1] - 1] == 1)
      return;
  }
  for (int i = 0; i < 4; i++) {
    figure->block_cords[i][1]--;
  }
  updateField();
}

void rotate_one_time_figure() {
  TetFigure *figure = getFigure();
  TetFigure temp;
  copy_figure(*figure, &temp);
  null_figure(figure);
  for (int j = 1; j < 4; j++) {
    for (int i = 0; i < 3; i++) {
      figure->blocks[i][j] = temp.blocks[j - 1][3 - i];
    }
  }
  figure->blocks[1][0] = temp.blocks[3][2];
  figure->blocks[3][2] = temp.blocks[1][0];
  if (!update_cords(figure)) {
    copy_figure(temp, figure);
    return;
  }
  for (int i = 0; i < 4; i++) {
    if (figure->block_cords[i][1] < 0 || figure->block_cords[i][1] > 9) {
      copy_figure(temp, figure);
      return;
    }
  }
}

void rotate_figure() {
  TetFigure *figure = getFigure();
  if ((figure->blocks[0][2] != 0 && figure->blocks[1][2] != 0 &&
       figure->blocks[1][3] != 0 && figure->blocks[2][3] != 0) ||
      (figure->blocks[0][3] != 0 && figure->blocks[1][3] != 0 &&
       figure->blocks[1][2] != 0 && figure->blocks[2][2] != 0)) {
    for (int i = 0; i < 2; i++) {
      rotate_one_time_figure();
    }
  }
  rotate_one_time_figure();
}

int check_collision() {
  TetFigure figure = *getFigure();
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 4; i++) {
    if (figure.block_cords[i][0] == 23) return 1;
    if (gameInfo->field[figure.block_cords[i][0] + 1]
                       [figure.block_cords[i][1]] == 1)
      return 1;
  }
  return 0;
}

void shift_matrix(int n) {
  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i][j] = 0;
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i][j] = gameInfo->field[i - 1][j];
    }
  }
}

int attach_figure() {
  TetFigure *figure = getFigure();
  GameInfo_t *gameInfo = getGameInfo();
  for (int j = 0; j < 10; j++) {
    if (gameInfo->field[4][j] == 1) {
      return 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    gameInfo->field[figure->block_cords[i][0]][figure->block_cords[i][1]] = 1;
  }
  return 0;
}

void set_tetris_screen() {
  GameInfo_t *gameInfo = getGameInfo();
  int matrix[20][10] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 0, 0, 5, 5, 0, 0, 5,
      0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0,
      0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5,
      5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo->field[i + 4][j] = matrix[i][j];
    }
  }
}

void remove_lines() {
  GameInfo_t *gameInfo = getGameInfo();
  int flag = 0;
  for (int i = 4; i < 24; i++) {
    int sum = 0;
    for (int j = 0; j < 10; j++) {
      if (gameInfo->field[i][j] != 0) {
        sum++;
      }
    }
    if (sum == 10) {
      flag = 1;
      shift_matrix(i);
    }
    if (flag) {
      usleep(10000);
    }
  }
}

TetFigure *getFigure() {
  static TetFigure figure = {
      {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
  return &figure;
}

void set_state(game_state new_state) {
  game_state *state = getGameState();
  *state = new_state;
}

void updateField() {
  GameInfo_t *gameInfo = getGameInfo();
  TetFigure figure = *getFigure();
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 10; j++) {
      if (gameInfo->field[i][j] == 2) {
        gameInfo->field[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    gameInfo->field[figure.block_cords[i][0]][figure.block_cords[i][1]] = 2;
  }
}

void userTetrisEvent(UserAction_t action) {
  TetFigure *figure = getFigure();
  TetFigure temp = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                    {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
  static clock_t start_time;
  static int next_figure = 2;

  switch (*getGameState()) {
    case GAMESTART:
      null_field();
      next_figure = rand() % 7 + 1;
      set_state(SPAWN);
      break;

    case SPAWN:
      fill_figure(figure, next_figure);
      next_figure = rand() % 7 + 1;
      fill_figure(&temp, next_figure);
      figure_to_next(temp);
      start_time = clock();
      set_state(MOVE);
      break;

    case MOVE:
      if (clock() - start_time > WAIT_TIME) {
        set_state(SHIFT);
      }
      switch (action) {
        case Left:
          figure_left();
          if (check_collision()) {
            set_state(COLLIDE);
          }
          break;
        case Right:
          figure_right();
          if (check_collision()) {
            set_state(COLLIDE);
          }
          break;
        case Action:
          rotate_figure();
          if (check_collision()) {
            set_state(COLLIDE);
          }
          break;
        case Down:
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
      updateField();
      break;

    case SHIFT:
      figure_down();
      if (check_collision()) {
        set_state(COLLIDE);
      } else {
        start_time = clock();
        set_state(MOVE);
      }
      break;

    case COLLIDE:
      if (attach_figure()) {
        set_state(GAMEOVER);
      } else {
        remove_lines();
        set_state(SPAWN);
      }
      break;

    case GAMEOVER:
      null_field();
      set_state(MENU);
      break;

    case PAUSE:
      switch (action) {
        case Terminate:
          sleep(1);
          set_state(GAMEOVER);
          break;
        case Pause:
          set_state(MOVE);
          break;
        default:
          break;
      }
      break;

    case MENU:
      set_tetris_screen();
      switch (action) {
        case Start:
          set_state(GAMESTART);
          break;
          //                case Terminate:
          //                    endwin();
          //                    exit(0);
          //                    break;
        default:
          break;
      }
    default:
      break;
  }
}