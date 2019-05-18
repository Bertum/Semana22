#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include "cell.h"

//! [0]
Helper::Helper()
{
    this->length = 1000;
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    int cont=0;
    //Set the cells by default
    for (int x = 0; x < this->length; x++) {
        for (int y = 0; y < this->length; y++) {
            int randomValue = qrand() % this->length;
            bool active = true;
            if (randomValue==0){
                active=false;
            }
            //this->cells[cont] = new Cell(x,y,active);
            this->cells.push_back( new Cell(x,y,active));
            cont++;
        }
   }
}
//! [0]

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    CheckCells();
    //Draw the cells
    int cont = 0;
    for (int x = 0; x < this->length; x++) {
        for (int y = 0; y < this->length; y++) {
            painter->setPen(QColor(255, 0, 0));
            painter->drawRect(this->cells[cont]->x ,this->cells[cont]->y, 1, 1);
            if (cells[cont]->active) {
                painter->setPen(QColor(0, 0, 255));
                painter->drawRect(this->cells[cont]->x ,this->cells[cont]->y, 1, 1);
            }
        cont++;
        }
    }
   /* painter->fillRect(event->rect(), background);
    painter->translate(100, 100);
//! [1]

//! [2]
    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
    painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 120.0 * factor;
        qreal circleRadius = 1 + factor * 20;
        painter->drawEllipse(QRectF(radius, -circleRadius,
                                    circleRadius * 2, circleRadius * 2));
    }
    painter->restore();
//! [2]

//! [3]
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));*/
}
void Helper::CheckCells() {
       int cont = 0;
       for (int x = 0; x < this->length; x++) {
           for (int y = 0; y < this->length; y++) {
               int nAlive = 0;
               //Compruebo si izq vive
               if (cont > this->length && cont < ((this->length * this->length) - this->length - 1)) {
                   if (this->cells[cont - 1]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont + 1]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont - 1 - this->length]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont - this->length]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont + 1 - this->length]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont - 1 + this->length]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont + this->length]->active) {
                       nAlive++;
                   }
                   if (this->cells[cont + 1 + this->length]->active) {
                       nAlive++;
                   }
               }
               //Implementacion HighLife
               //Celula viva con menos de dos vecinos muere
               if (this->cells[cont]->active && nAlive < 2){
                   this->cells[cont]->active = false;
               }
               //Celula viva con mas de tres vecinos muere
               if (this->cells[cont]->active && nAlive > 3){
                   this->cells[cont]->active = false;
               }
               //Celula viva con dos o tres vecinos no pasa na
               if (this->cells[cont]->active && (nAlive == 2 || nAlive == 3)){
                   //this->Cells[cont].pinturaCell.setColor(Color.BLUE);
                   this->cells[cont]->active = true;
               }
               //Celula MUERTA con tres vecinos o seis, vive
               if (this->cells[cont]->active && (nAlive == 3 || nAlive == 6)){
                   //this->Cells[cont].pinturaCell.setColor(Color.GREEN);
                   this->cells[cont]->active = true;
               }
               cont++;
           }
       }
   }
