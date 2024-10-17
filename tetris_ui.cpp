#include "gamebox.h"
using namespace s21;
void Game1::paintEvent(QPaintEvent *e){
    Q_UNUSED(*e);
    QBrush colors[7];
    QBrush red(QColor(Qt::red), Qt::SolidPattern);
    QBrush orange(QColor(255,105,0), Qt::SolidPattern);
    QBrush yellow(QColor(Qt::yellow), Qt::SolidPattern);
    QBrush pink(QColor(255,0,105), Qt::SolidPattern);
    QBrush green(QColor(Qt::green), Qt::SolidPattern);
    QBrush blue(QColor(Qt::blue), Qt::SolidPattern);
    QBrush magenta(QColor(Qt::magenta), Qt::SolidPattern);
    QBrush field(QColor(20,20,20), Qt::SolidPattern);
    QBrush info(QColor(30,30,30), Qt::SolidPattern);
    QBrush pop(QColor(255,255,255), Qt::SolidPattern);
    QPainter qp(this);
    this->update();
    qp.setBrush(field);
    qp.setPen(QColor(20,20,20));
    qp.drawRect(0,0,10*dw,20*dh);
    qp.setBrush(info);
    qp.drawRect(5*dw,20*dh,5*dw,4*dh);
    qp.drawRect(0,20*dh,5*dw,4*dh);
    qp.setBrush(field);
    qp.drawRect(0,24*dh,10*dw,3*dh);
    if(data.speed==0){
        qp.setPen(QColor(Qt::white));
        qp.setFont(QFont("Arial",16,700));
        qp.drawText(QRect(0,0,10*dw,20*dh),Qt::AlignCenter,"Tetris Game\nPress Enter to start");
        qp.setFont(QFont("Arial",12,700));
        qp.drawText(QRect(0,20*dh,5*dw,4*dh),Qt::AlignCenter,"Score "+QString::number(data.score)+"\nLevel "+QString::number(data.level));
        qp.drawText(QRect(5*dw,20*dh,5*dw,4*dh),Qt::AlignCenter,"Esc - Quit");
    }
    else if(data.speed){
        for (int y = 0; y <= 20*dh-dh; y+=1)
            for (int x = 0; x <=10*dw-dw; x+=1){
              if (data.field[y][x]){
                  if(data.field[y][x]==1)   qp.setBrush(red);
                  else if(data.field[y][x]==2)  qp.setBrush(orange);
                  else if(data.field[y][x]==3)  qp.setBrush(yellow);
                  else if(data.field[y][x]==4)  qp.setBrush(pink);
                  else if(data.field[y][x]==5)  qp.setBrush(green);
                  else if(data.field[y][x]==6)  qp.setBrush(blue);
                  else if(data.field[y][x]==7)  qp.setBrush(magenta);
                  qp.drawRect(x,y,dw,dh);
              }
              else if (data.brick.set[data.brick.pos][y][x]){
                  if(data.brick.shape==1)   qp.setBrush(red);
                  else if(data.brick.shape==2)  qp.setBrush(orange);
                  else if(data.brick.shape==3)  qp.setBrush(yellow);
                  else if(data.brick.shape==4)  qp.setBrush(pink);
                  else if(data.brick.shape==5)  qp.setBrush(green);
                  else if(data.brick.shape==6)  qp.setBrush(blue);
                  else if(data.brick.shape==7)  qp.setBrush(magenta);
                  qp.drawRect(x,y,dw,dh);
              }
              if (data.next.set[0][y][x]){
                          if(data.next.shape==1)   qp.setBrush(red);
                          else if(data.next.shape==2)  qp.setBrush(orange);
                          else if(data.next.shape==3)  qp.setBrush(yellow);
                          else if(data.next.shape==4)  qp.setBrush(pink);
                          else if(data.next.shape==5)  qp.setBrush(green);
                          else if(data.next.shape==6)  qp.setBrush(blue);
                          else if(data.next.shape==7)  qp.setBrush(magenta);
                          if(data.next.shape==1)
                             qp.drawRect(x,y+25*dh,dw,dh);
                          else
                            qp.drawRect(x,y+24.5*dh,dw,dh);
                      }
            }
        if(data.speed>0 && data.pause==0){
            qp.setPen(QColor(Qt::white));
            qp.setFont(QFont("Arial",12,700));
            qp.drawText(QRect(5*dw,20*dh,5*dw,4*dh),Qt::AlignCenter,"Left/Right\nDown - Fall\nUp - Rotate\nSpace - Pause\nEsc - Quit");
            qp.drawText(QRect(0,20*dh,5*dw,4*dh),Qt::AlignCenter,"Record "+QString::number(data.high_score)+"\nScore "+QString::number(data.score)+"\nLevel "+QString::number(data.level)+"\nSpeed "+QString::number(data.speed));
        }
        else if(data.pause){
                data.pause=1;
                qp.setPen(QColor(Qt::black));
                qp.setFont(QFont("Arial",16,700));
                qp.setBrush(pop);
                qp.drawRect(2*dw,9*dh,6*dw,2*dh);
                qp.drawText(QRect(2*dw,9*dh,6*dw,2*dh),Qt::AlignCenter,"Pause");
                qp.setFont(QFont("Arial",12,700));
                qp.setPen(QColor(Qt::white));
                qp.drawText(QRect(5*dw,20*dh,5*dw,4*dh),Qt::AlignCenter,"Space - Resume\nEsc - Quit");
                qp.drawText(QRect(0,20*dh,5*dw,4*dh),Qt::AlignCenter,"Record "+QString::number(data.high_score)+"\nScore "+QString::number(data.score)+"\nLevel "+QString::number(data.level)+"\nSpeed "+QString::number(data.speed));
            }
        else if(data.pause==0 && data.speed<0){
            qp.setPen(QColor(Qt::black));
            qp.setFont(QFont("Arial",16,700));
            qp.setBrush(pop);
            qp.drawRect(2*dw,9*dh,6*dw,2*dh);
            qp.drawText(QRect(2*dw,9*dh,6*dw,2*dh),Qt::AlignCenter,"Game Over");
            qp.setFont(QFont("Arial",12,700));
            qp.setPen(QColor(Qt::white));
            qp.drawText(QRect(5*dw,20*dh,5*dw,4*dh),Qt::AlignCenter,"Enter - Restart\nEsc - Quit");
            qp.drawText(QRect(0,20*dh,5*dw,4*dh),Qt::AlignCenter,"Record "+QString::number(data.high_score)+"\nScore "+QString::number(data.score)+"\nLevel "+QString::number(data.level));
        }
    }
}
