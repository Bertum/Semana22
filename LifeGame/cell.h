#ifndef CELL_H
#define CELL_H
#include <QPainter>

class Cell
{
public:
    Cell(int x,int y, bool active);

public:
    int x;
    int y;
    bool active;
};

#endif // CELL_H
