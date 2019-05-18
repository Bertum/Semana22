/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

//! [0]
Helper::Helper()
{
    length = 80;
    cells.resize(length);
    for(int row = 0; row < length; row++) {
      cells[row].resize(length);
    }
    cellSize = 10;
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
    srand(static_cast<unsigned int>(clock()));
    //Set the cells by default
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < length; y++) {
            bool active = true;
            if ((double(rand()) / (double(RAND_MAX) + 1.0))<=0.4){
                active=false;
            }
            cells[x][y] = new Cell(x,y,active);
            cont++;
        }
   }
}
//! [0]

//! [1]
void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    CheckCells();
    painter->fillRect(event->rect(), background);
    int cont = 0;
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < length; y++) {
            qreal left = (qreal)(cellSize*x); // margin from left
            qreal top  = (qreal)(cellSize*y); // margin from top
            if (cells[x][y]->active) {
                //painter->fillRect(cells[cont]->x *cellSize,cells[cont]->y *cellSize, cellSize, cellSize, QColor(0, 255, 0));
                QRectF r(left, top, (qreal)cellSize, (qreal)cellSize);
                painter->fillRect(r, QBrush("#00ff00")); // fill cell with brush of main color
            }
            else {
                //painter->fillRect(cells[cont]->x *cellSize,cells[cont]->y *cellSize, cellSize, cellSize, QColor(0, 0, 0));
                QRectF r(left, top, (qreal)cellSize, (qreal)cellSize);
                painter->fillRect(r, QBrush("#000000"));
            }
            cont++;
        }
    }/*
    if ((double(rand()) / (double(RAND_MAX) + 1.0))<=0.5){
        painter->fillRect(0,0, 50, 50, QColor(0, 255, 0));
    } else {
        painter->fillRect(0,0, 50, 50, QColor(255, 0, 0));
    }*/
}
//! [3]
void Helper::CheckCells() {
   int cont = 0;
   QVector< QVector<Cell *> > auxCells(length);
   for(int row = 0; row < length; row++) {
     auxCells[row].resize(length);
   }
   for (int x = 0; x < length; x++) {
       for (int y = 0; y < length; y++) {
           auxCells[x][y] = new Cell(x,y,cells[x][y]->active);
           int nAliveNeighboursCount = 0;
           //Si estas vivo, miras tus vecinos para ver si sigo vivo
           //Si estás muerto, tb pero para ver si nazco.
           //Izq
           if (x>0 && cells[x-1][y]->active) {
               nAliveNeighboursCount++;
           }
           //upIzq
           if (x>0 && y>0 && cells[x-1][y-1]->active) {
               nAliveNeighboursCount++;
           }
           //up
           if (y>0 && cells[x][y-1]->active) {
               nAliveNeighboursCount++;
           }
           //upDer
           if (x<length-1 && y>0 && cells[x+1][y-1]->active) {
               nAliveNeighboursCount++;
           }
           //der
           if (x<length-1 && cells[x+1][y]->active) {
               nAliveNeighboursCount++;
           }
           //dDer
           if (x<length-1 && y<length-1 && cells[x+1][y+1]->active) {
               nAliveNeighboursCount++;
           }
           //down
           if (y<length-1 && cells[x][y+1]->active) {
               nAliveNeighboursCount++;
           }
           //dIzq
           if (x>0 && y<length-1 && cells[x-1][y+1]->active) {
               nAliveNeighboursCount++;
           }
           //Implementacion HighLife
           //Celula viva con menos de dos vecinos muere
           //Celula viva con mas de tres vecinos muere
           if (cells[x][y]->active && (nAliveNeighboursCount < 2 || nAliveNeighboursCount > 3)){
               auxCells[x][y]->active = false;
           }
           //Celula MUERTA con tres vecinos o seis, vive
           if (!cells[x][y]->active && (nAliveNeighboursCount == 3 || nAliveNeighboursCount == 6)){
               auxCells[x][y]->active = true;
           }
           cont++;
       }
   }
   cells = auxCells;
}
