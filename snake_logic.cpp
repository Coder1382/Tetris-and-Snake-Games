#include "gamebox.h"
using namespace s21;
void Game2 :: starting(){
  for(int i=0; i<200; data.snake[i].n=data.snake[i].x=data.snake[i].y=0, i+=1){};
  data.score=data.pause=0, data.level=1, data.speed=12;
  timer->start(data.speed*80.0);
  (f = fopen("snakeRecord.txt", "r")) == NULL || fscanf(f, "%d", &data.high_score) == -1 ? data.high_score = 0 : 0;
  f ? fclose(f) : 0;
  for(int i=9; i<13; i++){
    data.snake[i-9].n=i-8, data.snake[i-9].x=5*dw, data.snake[i-9].y=i*dh;
  }
  for(int j=0; ; j=0){
    data.appleX=rand() % 270-1, data.appleY=rand() % 570+1;
    for(; j<200 && !(qFabs(data.snake[j].y-data.appleY)<=dh && qFabs(data.snake[j].x-data.appleX)<=dw); j+=1);
    if(j==200)  break;
  }
}
void Game2 :: moveLeft() {
  int i=1;
  for(; data.snake[i].n && !(qFabs(data.snake[i].x-data.snake[0].x)<dw && qFabs(data.snake[i].y-data.snake[0].y)<dh); i+=1);
  if(data.snake[i].n){
    data.speed=-100;
    return;
  }
  if(data.snake[0].x==0)
    data.speed=-100;
  else{
    if(!(qFabs(data.appleY-data.snake[0].y)<=dh && qFabs(data.appleX-data.snake[0].x)<=dw)){
      for(i=199; data.snake[i].n==0; i-=1);
      for(i-=1; i>=0; data.snake[i+1].y=data.snake[i].y, data.snake[i+1].x=data.snake[i].x, i-=1);
      data.snake[0].x=data.snake[0].x-dw;
    }
    else  eating();
  }
}
void Game2 :: moveRight() {
  int i=1;
  for(; data.snake[i].n && !(qFabs(data.snake[i].x-data.snake[0].x)<dw && qFabs(data.snake[i].y-data.snake[0].y)<dh); i+=1);
  if(data.snake[i].n){
    data.speed=-100;
    return;
  }
  if(data.snake[0].x==10*dw-dw)
    data.speed=-100;
  else{
    if(!(qFabs(data.appleY-data.snake[0].y)<=dh && qFabs(data.appleX-data.snake[0].x)<=dw)){
      for(i=199; data.snake[i].n==0; i-=1);
      for(i-=1; i>=0; data.snake[i+1].y=data.snake[i].y, data.snake[i+1].x=data.snake[i].x, i-=1);
      data.snake[0].x=data.snake[0].x+dw;
    }
    else  eating();
  }
}
void Game2 :: moveDown() {
  int i=1;
  for(; data.snake[i].n && !(qFabs(data.snake[i].y-data.snake[0].y)<dh && qFabs(data.snake[i].x-data.snake[0].x)<dw); i+=1);
  if(data.snake[i].n){
    data.speed=-100;
    return;
  }
  if(data.snake[0].y==20*dh-dh)
    data.speed=-100;
  else{
    if(!(qFabs(data.appleY-data.snake[0].y)<=dh && qFabs(data.appleX-data.snake[0].x)<=dw)){
      for(i=199; data.snake[i].n==0; i-=1);
      for(i-=1; i>=0; data.snake[i+1].y=data.snake[i].y, data.snake[i+1].x=data.snake[i].x, i-=1);
      data.snake[0].y=data.snake[0].y+dh;
    }
    else  eating();
  }
}
void Game2 :: moveUp() {
  int i=1;
  for(; data.snake[i].n && !(qFabs(data.snake[i].y-data.snake[0].y)<dh && qFabs(data.snake[i].x-data.snake[0].x)<dw); i+=1);
  if(data.snake[i].n){
    data.speed=-100;
    return;
  }
  if(data.snake[0].y==0)
    data.speed=-100;
  else{
    if(!(qFabs(data.appleY-data.snake[0].y)<=dh && qFabs(data.appleX-data.snake[0].x)<=dw)){
      for(i=199; data.snake[i].n==0; i-=1);
      for(i-=1; i>=0; data.snake[i+1].y=data.snake[i].y, data.snake[i+1].x=data.snake[i].x, i-=1);
      data.snake[0].y=data.snake[0].y-dh;
    }
    else  eating();
  }
}
void Game2 :: shiftAhead() {
   if(data.pause==0 && data.speed>0){
    if(data.snake[1].y==data.snake[0].y-dh)
        moveDown();
    else if(data.snake[1].y==data.snake[0].y+dh)
        moveUp();
    else if(data.snake[1].x==data.snake[0].x-dw)
        moveRight();
    else if(data.snake[1].x==data.snake[0].x+dw)
        moveLeft();
  }
}
void Game2 :: eating(){
  int i=199;
  if(data.snake[i].n)
    data.speed=-200;
  else{
    data.score+=1;
    if(data.score && data.score%5==0 && data.level<10)
      data.level+=1, data.speed-=0.1, timer->stop(), timer->start(data.speed*80);
    for(; data.snake[i].n==0; i-=1);
    data.snake[i+1].n=data.snake[i].n+1;
    for(; i>=0; data.snake[i+1].y=data.snake[i].y, data.snake[i+1].x=data.snake[i].x, i-=1);
    if(data.vert){
        if(data.appleY-data.snake[1].y>0)
            data.snake[0].y=data.snake[1].y+dh, data.snake[0].x=data.snake[1].x;
        else    data.snake[0].y=data.snake[1].y-dh, data.snake[0].x=data.snake[1].x;
    }
    else if(data.horiz){
        if(data.appleX-data.snake[1].x>0)
            data.snake[0].y=data.snake[1].y, data.snake[0].x=data.snake[1].x+dw;
        else    data.snake[0].y=data.snake[1].y, data.snake[0].x=data.snake[1].x-dw;
    }
    for(int j=0; ; j=0){
      data.appleX=rand() % 270-1, data.appleY=rand() % 570+1;
      for(; j<200 && !(qFabs(data.snake[j].y-data.appleY)<=dh && qFabs(data.snake[j].x-data.appleX)<=dw); j+=1);
      if(j==200)  break;
    }
  }
}
