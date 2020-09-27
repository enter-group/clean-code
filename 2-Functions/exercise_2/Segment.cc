#include "Segment.h"

bool Segment::operator==(Segment other) 
{
    return x == other.x && y == other.y;
}

bool Segment::operator==(Position other)
{
    return x == other.x && y == other.y;
}

void Segment::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Segment::GetX()
{
    return x;
}

int Segment::GetY()
{
    return y;
}