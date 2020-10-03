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
    void CalculateCollisionsWithHazards(Stage& stage);
    void CalculateCollisionsWithFruits(Stage& stage);
    void PlaceBodyAtPosition(Position position);
    void UpdatePosition();
    void ClearHasEatenFruitThisFrame();
    void ClearHasCollided();
    void AddNewSegment();
    
    bool HasCollided(); 
    bool HasEatenFruitThisFrame();
    
    int Length();
    
    Position GetHeadLocalPosition();
    Direction GetDirection();

private:
    void ResetSnakeBody();
    void MoveBodyToNewPosition(Position position);

    bool HasCollidedWithBody();
    bool HasCollidedWithWalls(Stage& stage);
    bool HadCollidedWithHazards(int tile);
    bool HadCollidedWithFruit(int tile);

    Position CalculateNewPosition();
    Segment GetHead();
    Position CalculateHeadGlobalPosition(Stage& stage);

    std::vector<Segment> body;
    Direction movingDirection;
    bool hasCollided;
    bool hasEatenFruitThisFrame;
};

#endif // SNAKE_H_