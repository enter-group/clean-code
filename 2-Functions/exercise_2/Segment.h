#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "Position.h"

class Segment
{

friend class Renderer;

public:
    Segment() = default;
    void SetPosition(int x, int y);
    int GetX();
    int GetY();
    bool operator==(Segment bodyObjectToBeCompared);
    bool operator==(Position bodyObjectToBeCompared);

private:
    int x;
    int y;
};

#endif // SEGMENT_H_