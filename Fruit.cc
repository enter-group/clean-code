#include "Fruit.h"

Fruit::Fruit()
{
    UpdateLocation();
}

void Fruit::UpdateLocation()
{
    c1 = rand()%17 + SCREEN_OFFST_X;
    c2 = rand()%77 + SCREEN_OFFST_y;
}

int Fruit::GetX()
{
    return c2;
}

int Fruit::GetY()
{
    return c1;
}