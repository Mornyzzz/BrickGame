#ifndef CPP3_BRICKGAME_V2_0_1_BRICKGAME_H
#define CPP3_BRICKGAME_V2_0_1_BRICKGAME_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MOVE_UP_BUTTON 'w'
#define MOVE_DOWN_BUTTON 's'
#define MOVE_LEFT_BUTTON 'a'
#define MOVE_RIGHT_BUTTON 'd'
#define ACTION_BUTTON 'q'
#define START_BUTTON 'r'
#define END_BUTTON 'z'
#define PAUSE_BUTTON 'p'

#define WAIT_TIME 400000

typedef struct TetFigure {
  int blocks[4][4];
  int block_cords[4][2];
} TetFigure;

typedef struct TetField {
  int blocks[24][10];
} TetField;

typedef enum {
  GAMESTART,
  SPAWN,
  MOVE,
  SHIFT,
  COLLIDE,
  GROW,
  PAUSE,
  GAMEOVER,
  WIN,
  MENU
} game_state;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,  //не используется
  Down,
  Action
} UserAction_t;

typedef enum { TETRIS, SNAKE, NULL_GAME } Game;

typedef struct {
  int** field;
  int** next;
  int score;       //не используется
  int high_score;  //не используется
  int level;       //не используется
  int speed;
  int pause;
} GameInfo_t;

UserAction_t getAction(int user_input);
GameInfo_t* getGameInfo();
GameInfo_t updateCurrentState();
game_state* getGameState();
Game* getGame();

#endif
