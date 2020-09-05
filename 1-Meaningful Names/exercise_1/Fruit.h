#ifndef FRUIT_H_
#define FRUIT_H_

#include <stdlib.h>
#include "GameConstants.h"

class Fruit
{

friend class Renderer;

public:
    Fruit();
    void PlaceAtRandomPosition();
    int GetX();
    int GetY();

private:
    int y;
    int x;
};

#endif // FRUIT_H_