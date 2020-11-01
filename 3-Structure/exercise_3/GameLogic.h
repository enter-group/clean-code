#ifndef GAME_OBJECTS_H_
#define GAME_OBJECTS_H_

#include <thread>

#include "Snake.h"
#include "FruitFactory.h"
#include "Renderer.h"
#include "Direction.h"
#include "GameConstants.h"
#include "Stage.h"
#include "LandLib/MapGenerator.h"

class GameLogic
{
public:
    GameLogic();
    void RunGame();

private:
    void ResetGameObjects();
    void DetermineMovementDelay(Direction snakeDirection);
    void EndGame();
    void ExecuteGameLogic();
    void RenderGame();
    void ProcessKeys();
    void UpdateSnakeBasedOnPosition();
    void ProcessEatenFruit();
    void GenerateRandomStageSize();
    void GenerateRandomStage();
    void GenerateMap();
    void CalculateInitialPositions();
    void CalculateHorizontalInitialPosition();
    void CalculateVerticalInitialPosition();

    MapGenerator mapGenerator;
    uint8_t* currentMap;
    Stage stage;
    Size stageSize;
    FruitFactory fruitFactory;
    Snake snake;
    int score;
    int pressedKey;
    Direction direction;
    Point2D initialPosition;
    Point2D initialStagePosition;
    Point2D initialSnakePosition;
};

#endif // GAME_OBJECTS_H_