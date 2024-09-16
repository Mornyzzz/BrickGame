#include "brickgame.h"

GameInfo_t* getGameInfo() {
  static GameInfo_t gameInfo = {0, 0, 0, 0, 0, 0, 0};
  return &gameInfo;
}

UserAction_t getAction(int user_input) {
  UserAction_t user_action = Up;
  if (user_input == MOVE_LEFT_BUTTON)
    user_action = Left;
  else if (user_input == MOVE_RIGHT_BUTTON)
    user_action = Right;
  else if (user_input == MOVE_UP_BUTTON)
    user_action = Up;
  else if (user_input == MOVE_DOWN_BUTTON)
    user_action = Down;
  else if (user_input == START_BUTTON)
    user_action = Start;
  else if (user_input == PAUSE_BUTTON)
    user_action = Pause;
  else if (user_input == END_BUTTON)
    user_action = Terminate;
  else if (user_input == ACTION_BUTTON)
    user_action = Action;
  return user_action;
}

GameInfo_t updateCurrentState() {
  GameInfo_t gameInfo = *getGameInfo();
  return gameInfo;
}

game_state* getGameState() {
  static game_state state = MENU;
  return &state;
}

Game* getGame() {
  static Game game = NULL_GAME;
  return &game;
}
