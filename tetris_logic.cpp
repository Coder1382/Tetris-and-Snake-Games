#include "gamebox.h"
using namespace s21;
void Game1::moveLeft() {
  int x = 0, i = 0, j = 0;
  for (; x < 4; x++) {
    for (i = 0; i <= 20*dh-dh; i++) {
      for (j = 10*dw-dw; j >=dw; j--)
        if (data.brick.set[x][i][j] && data.field[i][j - dw])
            j = 1, i = 20*dh;
      if(j == dw-1 && data.brick.set[x][i][0])
          i = 20*dh;
    }
    if (i == 20*dh-dh+1)
      for (i = 0; i <= 20*dh-dh; i++)
        for (j = dw; j <= 10*dw-dw; j++)
          data.brick.set[x][i][j - dw] = data.brick.set[x][i][j], data.brick.set[x][i][j] = 0;
  }
}
void Game1::moveRight() {
  int x = 0, i = 0, j = 0;
  for (; x < 4; x++) {
    for (i = 0; i <= 20*dh-dh; i++) {
      for (j = 0; j <= 10*dw-dw; j++)
        if (data.brick.set[x][i][j] && data.field[i][j + dw])
            j = 10*dw, i = 20*dh;
      if(j == 10*dw-dw+1 && data.brick.set[x][i][10*dw-dw])
          i = 20*dh;
    }
    if (i == 20*dh-dh+1){
      for (i = 0; i <= 20*dh-dh; i++)
        for (j = 10*dw-dw-1; j >= 0; j--)
          data.brick.set[x][i][j + dw] = data.brick.set[x][i][j], data.brick.set[x][i][j] = 0;
    }
  }
}
void Game1::shiftDown () {
  int x = 0, i = 0, j = 0;
  if(data.pause==0)
  for (x=0; x < 4; x+=1) {
    for (j=0; j <= 10*dw-dw && data.brick.set[x][20*dh-dh][j] == 0; j+=1);
    if (j == 10*dw-dw+1) {
      for (i = 0; i <= 20*dh-dh; i+=1)
        for (j = 0; j <= 10*dw-dw; j+=1)
          if (data.brick.set[x][i][j] && data.field[i+dh][j])
              j = 10*dw, i = 20*dh;
      if (i == 20*dh-dh+1)
        for (i = 20*dh-dh-dh; i >= 0; i-=1)
          for (j = 0; j < 10*dw; j+=1)
            data.brick.set[x][i + dh][j] = data.brick.set[x][i][j], data.brick.set[x][i][j] = 0;
      else  bottom=1;
    }
    else    bottom=1;
    if(bottom){
     if(x==data.brick.pos){
        for (i = 0; i <= 20*dh-dh; i+=1)
          for (j = 0; j <= 10*dw-dw; j+=1)
             if(data.brick.set[x][i][j])
                 data.field[i][j] = data.brick.shape;
        for(; x<10*dw && data.field[0][x]==0; x++);
        if(x<10*dw)
            data.speed=-1;
        else
            data.brick=data.next, newBrick(&data.next);
        fall=1, x=4;
      }
     bottom=0;
    }
  }
}
void Game1::removeFilled () {
  int x = 0, y = 0, i = 0, j = 0, c=0, temp = 0;
  for (y = 20*dh-dh; y >= 0; y--) {
    for (x = 0, c=0; x < 10*dw && data.field[y][x]; c++, x+=dw);
    if (c==10) {
      for (x = 0, temp++; x <10*dw; data.field[y][x] = 0, x++);
      for (i = y - 1, y = 20*dh-dh; i >= 0; i--)
        for (j = 0; j < 10*dw; j++)
          data.field[i + dh][j] = data.field[i][j], data.field[i][j] = 0;
    }
  }
  temp = (temp == 1   ? 100 : temp == 2 ? 300 : temp == 3 ? 700 : temp > 3  ? 1500: 0);
  data.level += (temp / 600), data.speed -= (temp / 600);
  if ((data.score % 600 + temp % 600) >= 600) data.level++, data.speed--;
  data.level > 10 ? data.level = 10 : 0, data.speed < 3 ? data.speed = 3 : 0, data.score += temp;
}
void Game1::newBrick(Brick *brick) {
  brick->pos = 0, brick->shape = rand() % 7 + 1;
  for (int v = 0; v < 4; v+=1)
    for (int i = 0; i < 20*dh; i+=1)
      for (int j = 0; j < 10*dw; brick->set[v][i][j] = 0, j+=1);
  if (brick->shape == 1)
    brick->set[0][0][3*dw] = brick->set[0][0][4*dw] = brick->set[0][0][5*dw] =
        brick->set[0][0][6*dw] = brick->set[1][0][4*dw] = brick->set[1][dh][4*dw] =
            brick->set[1][2*dh][4*dw] = brick->set[1][3*dh][4*dw] = brick->set[2][0][3*dw] =
                brick->set[2][0][4*dw] = brick->set[2][0][5*dw] =
                    brick->set[2][0][6*dw] = brick->set[3][0][4*dw] =
                         brick->set[3][dh][4*dw] = brick->set[3][2*dh][4*dw] =
                            brick->set[3][3*dh][4*dw] = 1;
  else if (brick->shape == 2)
    brick->set[0][0][4*dw] = brick->set[0][dh][4*dw] = brick->set[0][dh][5*dw] =
        brick->set[0][dh][6*dw] = brick->set[1][0][4*dw] = brick->set[1][0][5*dw] =
            brick->set[1][dh][4*dw] = brick->set[1][2*dh][4*dw] = brick->set[2][0][4*dw] =
                brick->set[2][0][5*dw] = brick->set[2][0][6*dw] =
                    brick->set[2][dh][6*dw] = brick->set[3][0][5*dw] =
                        brick->set[3][dh][5*dw] = brick->set[3][2*dh][4*dw] =
                            brick->set[3][2*dh][5*dw] = 1;
  else if (brick->shape == 3)
    brick->set[0][0][5*dw] = brick->set[0][dh][3*dw] = brick->set[0][dh][4*dw] =
        brick->set[0][dh][5*dw] = brick->set[1][0][3*dw] = brick->set[1][dh][3*dw] =
            brick->set[1][2*dh][3*dw] = brick->set[1][2*dh][4*dw] = brick->set[2][0][3*dw] =
                brick->set[2][0][4*dw] = brick->set[2][0][5*dw] =
                    brick->set[2][dh][3*dw] = brick->set[3][0][3*dw] =
                        brick->set[3][0][4*dw] = brick->set[3][dh][4*dw] =
                            brick->set[3][2*dh][4*dw] = 1;
  else if (brick->shape == 4)
    brick->set[0][0][4*dw] = brick->set[0][0][5*dw] = brick->set[0][dh][4*dw] =
        brick->set[0][dh][5*dw] = brick->set[1][0][4*dw] = brick->set[1][0][5*dw] =
            brick->set[1][dh][4*dw] = brick->set[1][dh][5*dw] = brick->set[2][0][4*dw] =
                brick->set[2][0][5*dw] = brick->set[2][dh][4*dw] =
                    brick->set[2][dh][5*dw] = brick->set[3][0][4*dw] =
                        brick->set[3][0][5*dw] = brick->set[3][dh][4*dw] =
                            brick->set[3][dh][5*dw] = 1;
  else if (brick->shape == 5)
    brick->set[0][0][5*dw] = brick->set[0][0][6*dw] = brick->set[0][dh][4*dw] =
        brick->set[0][dh][5*dw] = brick->set[1][0][4*dw] = brick->set[1][dh][4*dw] =
            brick->set[1][dh][5*dw] = brick->set[1][2*dh][5*dw] = brick->set[2][0][5*dw] =
                brick->set[2][0][6*dw] = brick->set[2][dh][4*dw] =
                    brick->set[2][dh][5*dw] = brick->set[3][0][4*dw] =
                        brick->set[3][dh][4*dw] = brick->set[3][dh][5*dw] =
                            brick->set[3][2*dh][5*dw] = 1;
  else if (brick->shape == 6)
    brick->set[0][0][5*dw] = brick->set[0][dh][4*dw] = brick->set[0][dh][5*dw] =
        brick->set[0][dh][6*dw] = brick->set[1][0][5*dw] = brick->set[1][dh][5*dw] =
            brick->set[1][dh][6*dw] = brick->set[1][2*dh][5*dw] = brick->set[2][0][4*dw] =
                brick->set[2][0][5*dw] = brick->set[2][0][6*dw] =
                    brick->set[2][dh][5*dw] = brick->set[3][0][6*dw] =
                        brick->set[3][dh][5*dw] = brick->set[3][dh][6*dw] =
                            brick->set[3][2*dh][6*dw] = 1;
  else
    brick->set[0][0][4*dw] = brick->set[0][0][5*dw] = brick->set[0][dh][5*dw] =
        brick->set[0][dh][6*dw] = brick->set[1][0][5*dw] = brick->set[1][dh][4*dw] =
            brick->set[1][dh][5*dw] = brick->set[1][2*dh][4*dw] = brick->set[2][0][4*dw] =
                brick->set[2][0][5*dw] = brick->set[2][dh][5*dw] =
                    brick->set[2][dh][6*dw] = brick->set[3][0][5*dw] =
                        brick->set[3][dh][4*dw] = brick->set[3][dh][5*dw] =
                            brick->set[3][2*dh][4*dw] = 1;
}
