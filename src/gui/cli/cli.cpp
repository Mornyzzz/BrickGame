#include "cli.h"

void display_information() {
  Game game = *getGame();
  if (game == TETRIS) {
    mvprintw(2, 23, "-Tetris Game-");
    mvprintw(4, 24, "Next Figure");
    mvprintw(13, 24, "Game Control");
    mvprintw(15, 24, "[R] Start");
    mvprintw(16, 24, "[P] Pause");
    mvprintw(17, 24, "[Z] Game Over");
    mvprintw(15, 45, "[A] Left");
    mvprintw(16, 45, "[D] Right");
    mvprintw(17, 45, "[S] Falling");
    mvprintw(18, 45, "[Q] Action");
  } else if (game == SNAKE) {
    mvprintw(2, 23, "-Snake Game-");
    mvprintw(4, 24, "Game Control");
    mvprintw(6, 24, "[R] Start");
    mvprintw(7, 24, "[P] Pause");
    mvprintw(8, 24, "[Z] Game Over");
    mvprintw(6, 45, "[A] Left");
    mvprintw(7, 45, "[D] Right");
    mvprintw(8, 45, "[Q] Action");
  }
}

WINDOW* cli_init() {
  initscr();
  refresh();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);
  WINDOW* win = win = newwin(22, 22, 0, 0);
  box(win, 0, 0);  // Добавление рамки вокруг окна
  wrefresh(win);   // Обновление окна
  return win;
}

WINDOW* tetris_menu_init() {
  WINDOW* menu = newwin(7, 13, 5, 23);
  box(menu, 0, 0);  // Добавление рамки вокруг окна
  wrefresh(menu);
  return menu;
}

void print_blank(WINDOW* win) {
  Game game = *getGame();
  GameInfo_t gameInfo = updateCurrentState();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (game == SNAKE) {
        if (gameInfo.field[i][j] != 0) {
          mvwaddch(win, i + 1, j * 2 + 1, ' ');
          mvwaddch(win, i + 1, j * 2 + 2, ' ');
        }
      } else if (game == TETRIS) {
        if (gameInfo.field[i + 4][j] != 0) {
          mvwaddch(win, i + 1, j * 2 + 1, ' ');
          mvwaddch(win, i + 1, j * 2 + 2, ' ');
        }
      }
    }
    wrefresh(win);
  }
  refresh();
}

void print_tetris_blink(WINDOW* win) {
  for (int i = 0; i < 5; i++) {
    print_blank(win);
    usleep(200000);
    print_tetris_game(win);
    usleep(200000);
  }
}

void print_snake_blink(WINDOW* win) {
  for (int i = 0; i < 5; i++) {
    print_blank(win);
    usleep(200000);
    print_snake_game(win);
    usleep(200000);
  }
}

void print_tetris_game(WINDOW* win) {
  GameInfo_t gameInfo = updateCurrentState();
  for (int i = 4; i < 24; i++) {
    for (int j = 0; j < 10; j++) {
      if (gameInfo.field[i][j] != 0) {
        mvwaddch(win, i - 3, j * 2 + 1, '[');
        mvwaddch(win, i - 3, j * 2 + 2, ']');
      } else {
        mvwaddch(win, i - 3, j * 2 + 1, ' ');
        mvwaddch(win, i - 3, j * 2 + 2, ' ');
      }
    }
    wrefresh(win);
  }

  int y_indent = 7;
  int x_indent = 24;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gameInfo.next[i][j] == 1) {
        mvprintw(i + y_indent, x_indent + j * 2 + 1, "[");
        mvprintw(i + y_indent, x_indent + j * 2 + 2, "]");
      } else {
        mvprintw(i + y_indent, x_indent + j * 2 + 1, " ");
        mvprintw(i + y_indent, x_indent + j * 2 + 2, " ");
      }
    }
    wrefresh(win);
  }
  refresh();
}

void print_snake_game(WINDOW* win) {
  GameInfo_t gameInfo = updateCurrentState();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      int q = i + 1;
      if (gameInfo.field[i][j] == 3) {
        mvwaddch(win, q, j * 2 + 1, '0');
        mvwaddch(win, q, j * 2 + 2, '0');
      }
      if (gameInfo.field[i][j] == 1 || gameInfo.field[i][j] == 5) {
        mvwaddch(win, q, j * 2 + 1, '[');
        mvwaddch(win, q, j * 2 + 2, ']');
      } else if (gameInfo.field[i][j] == 2) {
        mvwaddch(win, q, j * 2 + 1, '(');
        mvwaddch(win, q, j * 2 + 2, ')');
      } else if (gameInfo.field[i][j] == 0) {
        mvwaddch(win, q, j * 2 + 1, ' ');
        mvwaddch(win, q, j * 2 + 2, ' ');
      }
    }
    wrefresh(win);
  }
  refresh();
}

void startTetrisEventLoop(WINDOW* win) {
  srand(time(NULL));
  game_init();
  WINDOW* menu = tetris_menu_init();
  display_information();

  while (true) {
    UserAction_t action = getAction(getch());
    userTetrisEvent(action);
    if (*getGameState() == GAMEOVER)
      print_tetris_blink(win);
    else
      print_tetris_game(win);
  }
}

void startSnakeEventLoop(WINDOW* win) {
  s21::SnakeController* snakeController = s21::getController();
  snakeController->field_init();
  display_information();

  while (true) {
    UserAction_t action = getAction(getch());
    snakeController->userInput(action);
    snakeController->updateField();
    switch (*getGameState()) {
      case GAMEOVER:
        print_snake_blink(win);
        break;
      case COLLIDE:
        mvprintw(16, 24, "You lose T_T");
        refresh();
        break;
      case WIN:
        mvprintw(16, 24, "Congratulations!\n You win ^_^");
        refresh();
        break;
      case GAMESTART:
        mvprintw(16, 24,
                 "                                     ");  //обнуление
                                                            //прошлой/проигрыша
                                                            //победы (если она
                                                            //была офк)
        refresh();
        break;
      default:
        print_snake_game(win);
        break;
    }
  }
}

int main() {
  Game* game = getGame();
  WINDOW* win = cli_init();
  mvprintw(2, 23, "-Change Game-");
  mvprintw(4, 24, "[A] Snake");
  mvprintw(6, 24, "[D] Tetris");
  wrefresh(win);
  UserAction_t k;
  while (!(k == Left || k == Right)) k = getAction(getch());

  mvprintw(2, 23, "           ");
  mvprintw(3, 24, "           ");
  mvprintw(6, 24, "           ");
  mvprintw(10, 24, "           ");

  switch (k) {
    case Right:
      *game = TETRIS;
      startTetrisEventLoop(win);
      break;
    case Left:
      *game = SNAKE;
      startSnakeEventLoop(win);
      break;
    default:
      break;
  }

  return 1;
}
