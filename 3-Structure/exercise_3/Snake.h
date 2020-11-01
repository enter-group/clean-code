/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include <algorithm>
#include "Segment.h"
#include "FruitFactory.h"
#include "Direction.h"
#include "Point2D.h"
#include "GameConstants.h"
#include "Stage.h"

#include "LandLib/MapGenerator.h"

class Snake
{

friend class Renderer;

public:
    Snake();

    void Reset();
    void UpdateDirection(Direction newDirection);
    void CalculateCollisionsWithHazards(Stage& stage);
    void CalculateCollisionsWithFruits(Stage& stage);
    void PlaceBodyAtPosition(Point2D position);
    void PlaceBodyAtAbsolute(Point2D position);
    void UpdatePosition();
    void ClearHasEatenFruitThisFrame();
    void ClearHasCollided();
    void AddNewSegment();
    
    bool HasCollided(); 
    bool HasEatenFruitThisFrame();
    
    int Length();
    
    Point2D GetHeadLocalPosition();
    Direction GetDirection();

private:
    void ResetSnakeBody();
    void MoveBodyToNewPosition(Point2D position);

    bool HasCollidedWithBody();
    bool HasCollidedWithWalls(Stage& stage);
    bool HadCollidedWithHazards(int tile);
    bool HadCollidedWithFruit(int tile);

    Point2D CalculateNewPosition();
    Segment GetHead();
    Point2D CalculateHeadGlobalPosition(Stage& stage);

    std::vector<Segment> body;
    Direction movingDirection;
    bool hasCollided;
    bool hasEatenFruitThisFrame;
};

#endif // SNAKE_H_