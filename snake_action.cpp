#include "gamebox.h"
using namespace s21;
void Game2 :: keyPressEvent(QKeyEvent *e) {
    key = e->key();
  if (data.speed > 0 && key == data.Pause)
    data.pause ? (data.pause = 0) : (data.pause = 1);
  else if (data.speed > 0 && data.pause == 0) {
    if (key == data.Left && data.vert==true)
      moveLeft(), data.horiz=true, data.vert=false;
    else if(key == data.Right && data.vert==true)
      moveRight(), data.horiz=true, data.vert=false;
    else if (key == data.Down && data.horiz==true)
      moveDown(), data.horiz=false, data.vert=true;
    else if(key == data.Up && data.horiz==true)
      moveUp(), data.horiz=false, data.vert=true;
    else if(key==data.Action && data.fast==0)
      data.fast=1, timer->stop(), timer->start(data.speed*20);
  }
  else if (data.speed <= 0 && key == data.Start)
    starting();
  if (data.speed>0 && data.score >= data.high_score){
    (f = fopen("snakeRecord.txt", "w")) ? fprintf(f, "%d", data.score), fclose(f) : 0;
    data.high_score=data.score;
  }
  if (key == data.Terminate) {
    if (data.score >= data.high_score)
      (f = fopen("snakeRecord.txt", "w")) ? fprintf(f, "%d", data.score), fclose(f) : 0;
    Game2::close();
    this->close();
    return;
  }

}
void Game2 :: keyReleaseEvent(QKeyEvent *e){
    if(data.speed>0 && data.fast && !e->isAutoRepeat())
     data.fast=0, timer->stop(), timer->start(data.speed*80);
}
