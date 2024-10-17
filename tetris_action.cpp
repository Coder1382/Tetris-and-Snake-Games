#include "gamebox.h"
using namespace s21;
void Game1 :: keyPressEvent(QKeyEvent *e) {
  key = e->key();
  if (data.speed > 0 && key == data.Pause)
    data.pause ? (data.pause = 0) : (data.pause = 1);
  else if (data.speed > 0 && data.pause == 0) {
    if (key == data.Left)
      moveLeft();
    else if (key == data.Right)
      moveRight();
    else if (key == data.Fall && fall==0)
        fall=1, timer->stop(), timer->start(data.speed*5);
    else if (key == data.Action)
      data.brick.pos = (data.brick.pos > 2 ? 0 : data.brick.pos + 1);
    removeFilled();
  }
  else if (data.speed <= 0 && key == data.Start) {
    srand ( time(NULL) );
    data.score = data.pause = 0, data.level = 1, data.speed = 12;
    (f = fopen("tetrisRecord.txt", "r")) == NULL ||
            fscanf(f, "%d", &data.high_score) == -1
        ? data.high_score = 0
        : 0;
    f ? fclose(f), f = NULL : 0;
    for (int y = 0; y <20*dh; y++)
      for (int x = 0; x <10*dw; data.field[y][x] = 0, x++);
    newBrick(&data.brick), newBrick(&data.next);
    timer->start(data.speed*80);
  }
  if (data.speed>0 && data.score >= data.high_score){
    (f = fopen("tetrisRecord.txt", "w")) ? fprintf(f, "%d", data.score), fclose(f), f = NULL : 0;
    data.high_score=data.score;
  }
  if (key == data.Terminate) {
    if (data.score >= data.high_score)
      (f = fopen("tetrisRecord.txt", "w")) ? fprintf(f, "%d", data.score),
          fclose(f), f = NULL : 0;
    Game1::close();
    this->close();
    return;
  }
}
void Game1::keyReleaseEvent(QKeyEvent *e){
    if(data.speed>0 && fall && !e->isAutoRepeat())
     fall=0, timer->stop(), timer->start(data.speed*80);
}
