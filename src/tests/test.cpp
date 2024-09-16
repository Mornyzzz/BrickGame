#include <gtest/gtest.h>

#include <stdexcept>

#include "../brick_game/snake/SnakeController.h"

namespace s21 {
TEST(Controller, get_controller) {
  SnakeModel model;
  SnakeController controller(&model);
  EXPECT_EQ(4, controller.get_size());
}

TEST(Controller, field_init) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();

  GameInfo_t *gameInfo = getGameInfo();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      EXPECT_EQ(gameInfo->field[i][j], 0);
    }
  }
  controller.field_delete();
}

TEST(Controller, update_field_no_changes_1) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();

  GameInfo_t *lastInfo = getGameInfo();

  game_state *snake_state = getGameState();
  *snake_state = GAMEOVER;
  controller.updateField();

  GameInfo_t *newInfo = getGameInfo();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      EXPECT_EQ(lastInfo->field[i][j], newInfo->field[i][j]);
    }
  }
  controller.field_delete();
}

TEST(Controller, update_field_no_changes_2) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();

  GameInfo_t lastInfo = updateCurrentState();

  game_state *snake_state = getGameState();
  *snake_state = COLLIDE;
  controller.updateField();

  GameInfo_t newInfo = updateCurrentState();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      EXPECT_EQ(lastInfo.field[i][j], newInfo.field[i][j]);
    }
  }
  controller.field_delete();
}

TEST(Controller, menu_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = MENU;
  controller.userInput(Up);
  EXPECT_EQ(*getGameState(), MENU);
  controller.userInput(Down);
  EXPECT_EQ(*getGameState(), MENU);
  controller.userInput(Right);
  EXPECT_EQ(*getGameState(), MENU);
  controller.userInput(Action);
  EXPECT_EQ(*getGameState(), MENU);
  controller.userInput(Start);
  EXPECT_EQ(*getGameState(), GAMESTART);
  controller.field_delete();
}

TEST(Controller, gameover_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = GAMEOVER;
  controller.userInput(Up);
  EXPECT_EQ(*getGameState(), MENU);
  controller.field_delete();
}

TEST(Controller, pause_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = PAUSE;
  controller.userInput(Down);
  EXPECT_EQ(*getGameState(), PAUSE);
  controller.userInput(Right);
  EXPECT_EQ(*getGameState(), PAUSE);
  controller.userInput(Action);
  EXPECT_EQ(*getGameState(), PAUSE);
  controller.userInput(Pause);
  EXPECT_EQ(*getGameState(), MOVE);
  *snake_state = PAUSE;
  controller.userInput(Terminate);
  EXPECT_EQ(*getGameState(), GAMEOVER);
  controller.field_delete();
}

TEST(Controller, collide_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = COLLIDE;
  controller.userInput(Down);
  EXPECT_EQ(*getGameState(), GAMEOVER);
  controller.field_delete();
}

TEST(Controller, win_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = WIN;
  controller.userInput(Down);
  EXPECT_EQ(*getGameState(), GAMEOVER);
  controller.field_delete();
}

TEST(Controller, shift_sm_1) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = MENU;
  controller.userInput(Start);

  for (int i = 0; i < 5; i++) {
    *snake_state = SHIFT;
    controller.userInput(Up);
    EXPECT_EQ(*getGameState(), MOVE);
  }
  *snake_state = SHIFT;
  controller.userInput(Up);
  EXPECT_EQ(*getGameState(), COLLIDE);
  controller.field_delete();
}

TEST(Controller, shift_sm_2) {
  SnakeController *controller = getController();
  controller->field_init();
  controller->init_snake();
  game_state *snake_state = getGameState();
  GameInfo_t *gameInfo = getGameInfo();
  gameInfo->field[12][4] = 2;
  *snake_state = SHIFT;
  controller->userInput(Up);
  EXPECT_EQ(*getGameState(), GROW);
  controller->field_delete();
}

TEST(Controller, grow_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  controller.init_snake();
  controller.updateField();
  game_state *snake_state = getGameState();

  *snake_state = GROW;
  controller.userInput(Up);
  EXPECT_EQ(*getGameState(), MOVE);

  model.set_size(199);
  model.set_cord(198, 0, 3);
  model.set_cord(198, 1, 3);
  model.snake_grow();
  EXPECT_EQ(*getGameState(), WIN);
  controller.field_delete();
}

TEST(Controller, gamestart_sm) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.field_init();
  game_state *snake_state = getGameState();
  *snake_state = GAMESTART;
  controller.userInput(Down);
  EXPECT_EQ(*getGameState(), MOVE);
}

TEST(Controller, move_sm) {
  SnakeController *controller = getController();
  game_state *snake_state = getGameState();
  int lastDir = controller->get_direction();

  *snake_state = MOVE;
  controller->userInput(Action);
  EXPECT_EQ(*getGameState(), SHIFT);

  *snake_state = MOVE;
  controller->userInput(Pause);
  EXPECT_EQ(*getGameState(), PAUSE);

  *snake_state = MOVE;
  controller->userInput(Terminate);
  EXPECT_EQ(*getGameState(), GAMEOVER);

  *snake_state = MOVE;
  controller->userInput(Up);
  controller->userInput(Up);
  EXPECT_EQ(*getGameState(), MOVE);

  *snake_state = MOVE;
  controller->set_time(clock() - 2 * WAIT_TIME);
  controller->userInput(Left);

  *snake_state = MOVE;
  controller->set_time(clock() - 2 * WAIT_TIME);
  controller->userInput(Right);

  EXPECT_EQ(lastDir, controller->get_direction());
}

TEST(Action, get_action) {
  EXPECT_EQ(getAction(MOVE_LEFT_BUTTON), Left);
  EXPECT_EQ(getAction(MOVE_RIGHT_BUTTON), Right);
  EXPECT_EQ(getAction(MOVE_UP_BUTTON), Up);
  EXPECT_EQ(getAction(MOVE_DOWN_BUTTON), Down);
  EXPECT_EQ(getAction(START_BUTTON), Start);
  EXPECT_EQ(getAction(PAUSE_BUTTON), Pause);
  EXPECT_EQ(getAction(END_BUTTON), Terminate);
  EXPECT_EQ(getAction(ACTION_BUTTON), Action);
  EXPECT_EQ(getAction(124123423), Up);
}

TEST(Controller, set_direction) {
  SnakeModel model;
  SnakeController controller(&model);
  controller.init_snake();
  controller.updateField();

  EXPECT_EQ(model.get_direction(), 1);
  controller.set_direction_left();
  controller.set_direction_left();
  EXPECT_EQ(model.get_direction(), 3);
  controller.set_direction_right();
  controller.set_direction_right();
  EXPECT_EQ(model.get_direction(), 1);
  controller.field_delete();
}
}  // namespace s21
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
