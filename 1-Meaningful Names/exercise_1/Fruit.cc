#include "Fruit.h"

Fruit::Fruit()
{
    Drop();
}

void Fruit::Drop()
{
    c1 = rand()%17 + SCREEN_OFFST_y;
    c2 = rand()%77 + SCREEN_OFFST_X;
}

int Fruit::GetX()
{
    return c2;
}

int Fruit::GetY()
{
    return c1;
}