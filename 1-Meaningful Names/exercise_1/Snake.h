#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include <algorithm>
#include "Segment.h"
#include "Fruit.h"
#include "Direction.h"
#include "GameConstants.h"

class Snake
{

friend class Renderer;

public:
    Snake();

    void Reset();
    void UpdateDirection(Direction newDirection);
    Direction GetDir();
    bool HasCollided();
    void UpdateCollisionState();
    void UpdatePosition();
    int Length();
    void TryToEatFruit(Fruit& in_out_fruit, int& out_sc);

private:
    std::vector<Segment> snakeSize;
    Direction movingDirection;
    bool hasCollided;
};

#endif // SNAKE_H_