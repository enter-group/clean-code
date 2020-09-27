#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include <algorithm>
#include "Segment.h"
#include "FruitFactory.h"
#include "Direction.h"
#include "Position.h"
#include "GameConstants.h"
#include "Stage.h"

class Snake
{

friend class Renderer;

public:
    Snake();

    void Reset();
    void UpdateDirection(Direction newDirection);
    Direction GetDirection();
    bool HasCollided();
    void UpdateCollisionState(Stage& stage, int& score, bool& operationStatus);
    void UpdatePosition();
    int Length();
    void SetPosition(Position position);
    Position GetHeadPosition();

private:
    std::vector<Segment> body;
    Direction movingDirection;
    bool hasCollided;
};

#endif // SNAKE_H_