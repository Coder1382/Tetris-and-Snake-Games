#ifndef GAMEBOX_H
#define GAMEBOX_H
#include "fcntl.h"
#include "locale.h"
#include "iostream"
#include "time.h"
#include "uchar.h"
#include "unistd.h"
#include "wchar.h"
#include "QWidget"
#include "QKeyEvent"
#include "QPainter"
#include "QPaintEvent"
#include "QDebug"
#include "QTimer"
#include "QtMath"
#include "QBrush"
#include "QColor"
#include "QPushButton"
#include "QMainWindow"
namespace s21{
class Play1{
  private:
  struct Snake{
  int n;
  int x;
  int y;
};
  public:
  enum UserAction_t{
  Start = 16777220, Pause = 32, Terminate = 16777216, Action= 16777217,
  Left = 16777234, Right = 16777236, Down = 16777237, Up = 16777235
};
  bool horiz=0, vert=1;
  int field[22][12], score=0, high_score=0, level=0, pause=0, speed=0, fast=0;
  int appleX=0, appleY=0, length=4;
  Snake snake[200];
};
class Game2 : public QWidget{
private:
    const int dh=30, dw=30;
public:
    Play1 data;
    int run=0, over=0, key='\0', selected=0;
    QKeyEvent *e;
    QPaintEvent *qp;
    QTimerEvent *qt;
    QPainter p;
    FILE *f=nullptr;
    QTimer *timer = new QTimer(this);
    void starting();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void shiftAhead();
    void eating();
    void keyPressEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    Game2(){
        f=nullptr;
        this->setFixedSize(10*dw,24*dh);
        this->setWindowTitle("Snake");
        connect(timer, &QTimer::timeout, this, &Game2::shiftAhead);
    }
};
typedef struct {
 int set[4][600][300];
 int shape, pos;
} Brick;
class Play2{
  private:
  public:
  enum UserAction_t{
  Start = 16777220, Pause = 32, Terminate = 16777216,
  Left = 16777234, Right = 16777236, Fall = 16777237, Action = 16777235
};
  int field[600][300], score=0, high_score=0, level=0, pause=0, speed=0;
  Brick brick;
  Brick next;

};
class Game1 : public QWidget{
private:
    const int dh=30, dw=30;
public:
    Play2 data;
    int fall=0, key='\0', bottom=0;
    QKeyEvent *e;
    QPaintEvent *qp;
    QTimerEvent *qt;
    FILE *f=nullptr;
    QTimer *timer = new QTimer(this);
    void moveLeft();
    void moveRight();
    void shiftDown();
    void removeFilled();
    void newBrick(Brick*);
    void keyPressEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    Game1(){
        this->setFixedSize(10*dw,27*dh);
        this->setWindowTitle("Tetris");
        connect(timer, &QTimer::timeout, this, &Game1::shiftDown);
    }
};
class Wrap: public QWidget {
private:
    const int dh=30, dw=30;
public:
    Game2 game2;
    Game1 game1;
    QPushButton *tetris=new QPushButton(this);
    QPushButton *snake=new QPushButton(this);
    void Snake(){
        tetris->close();
        snake->close();
        this->hide();
        game2.show();
    }
    void Tetris(){
        tetris->close();
        snake->close();
        this->hide();
        game1.show();
    }
    Wrap(){
        game2.hide();
        game1.hide();
        setFixedSize(10*dw,24*dh);
        this->setWindowTitle("Choose Game");
        tetris->setStyleSheet("width:100;height:50;background:lime;font-weight:bold");
        tetris->setText("Tetris");
        tetris->move(1*dw,9*dh);
        snake->setStyleSheet("width:100;height:50;background:coral;font-weight:bold");
        snake->setText("Snake");
        snake->move(5.5*dw,9*dh);
        this->show();
        connect(this->snake,&QPushButton::clicked, this, &Wrap::Snake);
        connect(this->tetris,&QPushButton::clicked, this, &Wrap::Tetris);
    }
};
}
#endif

