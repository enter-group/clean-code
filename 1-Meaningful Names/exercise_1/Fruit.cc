#include "Fruit.h"

Fruit::Fruit()
{
    PlaceAtRandomPosition();
}

void Fruit::PlaceAtRandomPosition()
{
    y = rand()%(playfieldHeight - 1);// + viewportVerticalOffset;
    x = rand()%(playfieldWidth - 1);//  + viewportHorizontalOffset;
}

int Fruit::GetX()
{
    return x;
}

int Fruit::GetY()
{
    return y;
}