/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include "Point2D.h"

class Segment
{

friend class Renderer;

public:
    Segment() = default;
    void SetPosition(int x, int y);
    int GetX();
    int GetY();
    bool operator==(Segment bodyObjectToBeCompared);
    bool operator==(Point2D bodyObjectToBeCompared);

private:
    int x;
    int y;
};