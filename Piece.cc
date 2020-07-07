#include "Piece.h"

bool Piece::operator==(Piece bodyObjectToBeCompared) 
{
    return x == bodyObjectToBeCompared.x && y == bodyObjectToBeCompared.y;
}

bool Piece::operator==(Fruit bodyObjectToBeCompared)
{
    return x == bodyObjectToBeCompared.GetX() && y == bodyObjectToBeCompared.GetY();
}

void Piece::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Piece::GetPositionX()
{
    return x;
}

int Piece::GetPositionY()
{
    return y;
}