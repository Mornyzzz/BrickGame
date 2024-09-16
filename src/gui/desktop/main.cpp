#include <QApplication>

#include "../../brick_game/brickgame.h"
#include "../../brick_game/snake/SnakeController.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::SnakeController *snakeController = s21::getController();
  MainWindow w(snakeController, nullptr);

  w.show();
  w.startEventLoop();

  return a.exec();
}
