#include "gamebox.h"
using namespace s21;
void Game2 :: paintEvent(QPaintEvent *e){
    Q_UNUSED(*e);
    QPainter qp(this);
    QBrush head(QColor(Qt::yellow), Qt::SolidPattern);
    QBrush element(QColor(Qt::green), Qt::SolidPattern);
    QBrush apple(QColor(Qt::red), Qt::SolidPattern);
    QBrush field(QColor(20,20,20), Qt::SolidPattern);
    QBrush info(QColor(30,30,30), Qt::SolidPattern);
    QBrush pop(QColor(255,255,255), Qt::SolidPattern);
    qp.setBrush(field);
    qp.setPen(QColor(20,20,20));
    qp.drawRect(0,0,10*dw,20*dh);
    qp.setBrush(info);
    qp.drawRect(5*dw,20*dh,5*dw,4*dh);
    qp.drawRect(0,20*dh,5*dw,4*dh);
    this->update();
    if(data.speed==0){
        run=over=0;
        qp.setPen(QColor(Qt::white));
        qp.setFont(QFont("Arial",16,700));
        qp.drawText(QRect(0,0,10*dw,20*dh),Qt::AlignCenter,"Snake Game\nPress Enter to Start");
        qp.setFont(QFont("Arial",12,700));
        qp.drawText(QRect(0,20*dh,5*dw,4*dh),Qt::AlignCenter,"Score "+QString::number(data.score)+"\nLevel "+QString::number(data.level));
        qp.drawText(QRect(5*dw,20*dh,5*dw,4*dh),Qt::AlignCenter,"Esc - Quit");
    }
    else if(data.speed){
        qp.setBrush(head);
        qp.setPen(QColor(20,20,20));
        qp.drawEllipse(data.snake[0].x,data.snake[0].y,dw,dh);
        for(int i=1; data.snake[i].n; i++){
          qp.setBrush(element);
          qp.setPen(QColor(20,20,20));
          qp.drawEllipse(data.snake[i].x,data.snake[i].y,dw,dh);
        }
        qp.setBrush(apple);
        qp.setPen(QColor(20,20,20));
        qp.drawEllipse(data.appleX,data.appleY,dw,dh);
        if(data.speed>0 && data.pause==0){
            run=1, over=0;
            qp.setPen(QColor(Qt::white));
            qp.setFont(QFont("Arial",12,700));
            qp.drawText(QRect(5*dw,20*dh,5*dw,4*dh),Qt::AlignCenter,"Left/Right\nUp/Down\nTab - Faster\nSpace - Pause\nEsc - Quit");
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
        else if(data.pause==0 && data.speed<-1){
            run=0, over=1;
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

