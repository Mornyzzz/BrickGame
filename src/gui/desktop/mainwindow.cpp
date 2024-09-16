#include "mainwindow.h"

#include "ui_mainwindow.h"

void MainWindow::print_snake_field() {
  GameInfo_t gameInfo = updateCurrentState();

  QPixmap pixmap(400, 420);
  QPainter painter(&pixmap);

  painter.fillRect(0, 0, 400, 420, QColor("#319a2f"));  // field (green)
  painter.fillRect(5, 5, 210, 410, QColor("#81be01"));  // field (green)

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      int x = 10 + j * 20;
      int y = 10 + i * 20;
      if (gameInfo.field[i][j] == 0) {
        painter.fillRect(10 + j * 20, 10 + i * 20, 20, 20,
                         QColor("#319a2f"));  // field (green)
      } else if (gameInfo.field[i][j] == 5) {
        painter.fillRect(10 + j * 20, 10 + i * 20, 20, 20,
                         QColor("#81be01"));  // snake screen
      } else if (gameInfo.field[i][j] == 1) {
        painter.fillRect(10 + j * 20, 10 + i * 20, 20, 20,
                         QColor("#81be01"));  // body
        painter.fillRect(x, y, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 2, y + 2, 2, 2, QColor("#81be01"));
        painter.fillRect(x + 16, y, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 16, y + 2, 2, 2, QColor("#81be01"));
        painter.fillRect(x, y + 16, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 2, y + 16, 2, 2, QColor("#81be01"));
        painter.fillRect(x + 16, y + 16, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 16, y + 16, 2, 2, QColor("#81be01"));
      } else if (gameInfo.field[i][j] == 3) {
        painter.fillRect(10 + j * 20, 10 + i * 20, 20, 20,
                         QColor("#81be01"));  // head
        painter.fillRect(x, y, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 2, y + 2, 2, 2, QColor("#81be01"));
        painter.fillRect(x + 16, y, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 16, y + 2, 2, 2, QColor("#81be01"));
        painter.fillRect(x, y + 16, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 2, y + 16, 2, 2, QColor("#81be01"));
        painter.fillRect(x + 16, y + 16, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 16, y + 16, 2, 2, QColor("#81be01"));
        painter.fillRect(x + 4, y + 8, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 12, y + 8, 4, 4, QColor("#319a2f"));
        painter.fillRect(x + 8, y + 12, 4, 2, QColor("#319a2f"));
      } else if (gameInfo.field[i][j] == 2) {
        painter.fillRect(x, y, 20, 20, QColor("#319a2f"));  // apple
        painter.fillRect(x, y + 4, 18, 16, QColor("#81be01"));
        painter.fillRect(x + 6, y, 4, 2, QColor("#81be01"));
        painter.fillRect(x + 8, y + 2, 2, 2, QColor("#81be01"));
        painter.fillRect(x + 8, y + 18, 2, 2, QColor("#319a2f"));
        painter.fillRect(x + 6, y + 6, 2, 4, QColor("#319a2f"));
        painter.fillRect(x + 4, y + 8, 2, 4, QColor("#319a2f"));
        painter.fillRect(x, y + 4, 4, 2, QColor("#319a2f"));
        painter.fillRect(x, y + 6, 2, 2, QColor("#319a2f"));
        painter.fillRect(x + 14, y + 4, 4, 2, QColor("#319a2f"));
        painter.fillRect(x + 16, y + 6, 2, 2, QColor("#319a2f"));
        painter.fillRect(x, y + 16, 2, 4, QColor("#319a2f"));
        painter.fillRect(x + 2, y + 18, 2, 2, QColor("#319a2f"));
        painter.fillRect(x + 16, y + 16, 2, 4, QColor("#319a2f"));
        painter.fillRect(x + 14, y + 18, 2, 2, QColor("#319a2f"));
      }
    }
  }
  ui->matrix->setPixmap(pixmap);
}

void MainWindow::print_snake_blank() {
  GameInfo_t gameInfo = updateCurrentState();

  QPixmap pixmap = ui->matrix->grab();
  QPainter painter(&pixmap);

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (gameInfo.field[i][j] != 0) {
        painter.fillRect(10 + j * 20, 10 + i * 20, 20, 20,
                         QColor("#319a2f"));  // field (green)
      }
    }
  }
  ui->matrix->setPixmap(pixmap);
}

void MainWindow::print_snake_blink() {
  for (int i = 0; i < 5; i++) {
    print_snake_blank();
    QTest::qWait(200);
    print_snake_field();
    QTest::qWait(200);
  }
}

void MainWindow::print_tetris_field() {
  GameInfo_t gameInfo = updateCurrentState();

  QPixmap pixmap(400, 420);
  QPainter painter(&pixmap);

  painter.fillRect(0, 0, 400, 420, QColor("#319a2f"));  // field (green)
  painter.fillRect(5, 5, 210, 410, QColor("#81be01"));  // field (green)

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      int x = 10 + j * 20;
      int y = 10 + i * 20;
      if (gameInfo.field[i + 4][j] == 0) {
        painter.fillRect(x, y, 20, 20, QColor("#319a2f"));  // field (green)
      } else if (gameInfo.field[i + 4][j] == 5) {
        painter.fillRect(x, y, 20, 20, QColor("#81be01"));  // tetris screen
      } else if (gameInfo.field[i + 4][j] == 1 ||
                 gameInfo.field[i + 4][j] == 2) {
        painter.fillRect(x, y, 20, 20, QColor("#81be01"));  // body
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int x = 230 + j * 20;
      int y = 70 + i * 20;
      if (gameInfo.next[i][j] == 1) {
        painter.fillRect(x, y, 20, 20, QColor("#81be01"));  // body
      } else {
        painter.fillRect(x, y, 20, 20, QColor("#319a2f"));  // field
      }
    }
  }
  ui->matrix->setPixmap(pixmap);
}

void MainWindow::print_tetris_blank() {
  GameInfo_t gameInfo = updateCurrentState();

  QPixmap pixmap = ui->matrix->grab();
  QPainter painter(&pixmap);

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (gameInfo.field[i + 4][j] != 0) {
        painter.fillRect(10 + j * 20, 10 + i * 20, 20, 20,
                         QColor("#319a2f"));  // field (green)
      }
    }
  }
  ui->matrix->setPixmap(pixmap);
}

void MainWindow::print_tetris_blink() {
  for (int i = 0; i < 5; i++) {
    print_tetris_blank();
    QTest::qWait(200);
    print_tetris_field();
    QTest::qWait(200);
  }
}

void MainWindow::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);

  Game *game = getGame();
  if (*game == NULL_GAME) {
    switch (action) {
      case Left:
        *game = SNAKE;
        ui->LabelGame->setText("\nSnake Game");
        snakeController->field_init();
        snakeController->updateField();
        print_snake_field();
        break;

      case Right:
        *game = TETRIS;
        ui->LabelGame->setText("\nTetris Game");
        srand(time(NULL));
        game_init();
        print_tetris_field();
        break;
      default:
        break;
    }
  }

  else {
    switch (*game) {
      case SNAKE:
        snakeController->userInput(action);
        snakeController->updateField();

        switch (*getGameState()) {
          case GAMEOVER:
            print_snake_blink();
            break;
          case COLLIDE:
            ui->LabelStatus->setText("You lose T_T");
            break;
          case WIN:
            ui->LabelStatus->setText("Congratulations!\n You win ^_^");
            break;
          case GAMESTART:
            ui->LabelStatus->setText(
                "");  //обнуление прошлой победы/луза (если она была офк)
            break;
          default:
            print_snake_field();
            break;
        }
        action = Up;
        break;

      case TETRIS:
        userTetrisEvent(action);
        switch (*getGameState()) {
          case GAMEOVER:
            print_tetris_blink();
            break;
          default:
            print_tetris_field();
            break;
        }
        action = Up;
        break;

      default:
        break;
    }
  }
}

void MainWindow::buttonClicked(int k) {
  QKeyEvent *event = new QKeyEvent(QKeyEvent::KeyPress, k, Qt::NoModifier);
  keyPressEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  action = Up;
  int user_input = event->key();
  if (user_input == 65)
    action = Left;
  else if (user_input == 68)
    action = Right;
  else if (user_input == 87)
    action = Up;
  else if (user_input == 83)
    action = Down;
  else if (user_input == 82)
    action = Start;
  else if (user_input == 80)
    action = Pause;
  else if (user_input == 90)
    action = Terminate;
  else if (user_input == 81) {
    action = Action;
  }
}

void MainWindow::startEventLoop() {
  Game *game = getGame();
  *game = NULL_GAME;
  game_init();
  print_tetris_field();
  ui->LabelGame->setText("\nChange Game\n\n[A] Snake\n[D] Tetris");
  timerId = startTimer(2);
}

MainWindow::MainWindow(s21::SnakeController *s, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), snakeController(s) {
  ui->setupUi(this);

  ui->ButtonStart->setStyleSheet(
      "QPushButton { border-radius: 10px; background-color: #8a888c}");
  ui->ButtonEnd->setStyleSheet(
      "QPushButton { border-radius: 10px; background-color: #8a888c}");
  ui->ButtonAction->setStyleSheet(
      "QPushButton { border-radius: 30px; background-color: #800b47}");
  ui->ButtonPause->setStyleSheet(
      "QPushButton { border-radius: 30px; background-color: #800b47}");
  ui->ButtonUp->setStyleSheet(
      "QPushButton { border-top-right-radius: 7px;border-top-left-radius: 7px; "
      "background-color: #0f0e1c}");
  ui->ButtonDown->setStyleSheet(
      "QPushButton { border-bottom-right-radius: "
      "7px;border-bottom-left-radius: 7px; background-color: #0f0e1c}");
  ui->ButtonLeft->setStyleSheet(
      "QPushButton { border-top-left-radius: 7px;border-bottom-left-radius: "
      "7px; background-color: #0f0e1c}");
  ui->ButtonRight->setStyleSheet(
      "QPushButton { border-bottom-right-radius: 7px;border-top-right-radius: "
      "7px; background-color: #0f0e1c}");

  ui->LabelPause->setStyleSheet("color: #26265b;");
  ui->LabelStart->setStyleSheet("color: #26265b;");
  ui->LabelAction->setStyleSheet("color: #26265b;");
  ui->LabelQuit->setStyleSheet("color: #26265b;");
  ui->LabelStatus->setStyleSheet("color: #81be01;");
  ui->LabelGame->setStyleSheet("color: #81be01;");
  ui->LabelGame->setText("SnakeGame");

  connect(ui->ButtonUp, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 87));
  connect(ui->ButtonDown, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 83));
  connect(ui->ButtonLeft, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 65));
  connect(ui->ButtonRight, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 68));
  connect(ui->ButtonAction, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 81));
  connect(ui->ButtonPause, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 80));
  connect(ui->ButtonStart, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 82));
  connect(ui->ButtonEnd, &QPushButton::clicked, this,
          std::bind(&MainWindow::buttonClicked, this, 90));

  setFixedSize(450, 700);  // Устанавливаем фиксированный размер окна
  setWindowFlags(
      Qt::MSWindowsFixedSizeDialogHint);  // Запрещаем изменение размера окна
  press_status = false;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.fillRect(rect(), QColor("#c1c0bc"));
  painter.setPen(QColor("#0f0e1c"));
  painter.fillRect(80, 520, 50, 50, QColor("#0f0e1c"));

  QPainterPath path;
  path.addRoundedRect(5, 5, 430, 450, 0,
                      0);  // координаты, размеры и радиус скругления

  painter.setBrush(QColor("#575763"));
  painter.setPen(Qt::NoPen);
  painter.fillPath(path, painter.brush());
}
