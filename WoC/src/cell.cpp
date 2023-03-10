#include "cell.h"
#include "board.h"

Cell* Cell::chosen = nullptr;

Cell::Cell(int x, int y) : QPushButton("+"), x(x), y(y)
{
    setFlat(true);
    setFixedSize(20, 20);
    fade();
    setAutoFillBackground(true);
    //Add your own code below
    //////////////////////////
    connect(this,SIGNAL(clicked()),this,SLOT(onclick()));
    connect(this,&Cell::isclick,Board::getBoard(),&Board::onClick);
    //////////////////////////
}
