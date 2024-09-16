#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTest>
#include <QTransform>
#include <QtGui>
#include <QtWidgets>

#include "../../brick_game/brickgame.h"
#include "../../brick_game/snake/SnakeController.h"
#include "../../brick_game/snake/SnakeModel.h"
#include "../../brick_game/tetris/tetrisBackend.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::SnakeController *s, QWidget *parent = nullptr);
  ~MainWindow();
  void print_snake_field();
  void print_tetris_field();
  void print_snake_blank();
  void print_tetris_blank();
  void print_snake_blink();
  void print_tetris_blink();
  void startEventLoop();
  UserAction_t getAction() { return action; }

 private:
  Ui::MainWindow *ui;
  s21::SnakeController *snakeController;
  int timerId;
  game_state state;
  UserAction_t action;
  bool press_status;

 protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 public slots:
  void buttonClicked(int k);
};
#endif  // MAINWINDOW_H
