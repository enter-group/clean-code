#ifndef SEGMENT_H_
#define SEGMENT_H_

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

#endif // SEGMENT_H_