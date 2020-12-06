/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <thread>

#include "Snake.h"
#include "FruitFactory.h"
#include "Renderer.h"
#include "Direction.h"
#include "GameConstants.h"
#include "Stage.h"
#include "Gamepad.h"

#include "LandLib/MapGenerator.h"
#include "InputLib/Joypad.h"
#include "InputLib/Button.h"

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
    void UpdateSnakeBasedOnPosition();
    void ProcessEatenFruit();
    void GenerateRandomStageSize();
    void GenerateRandomStage();
    void GenerateMap();
    void CalculateInitialPositions();
    void CalculateHorizontalInitialPosition();
    void CalculateVerticalInitialPosition();
    void UpdatePauseFlag();
    void ProcessPlayerInput();

    LandLib::MapGenerator mapGenerator;

    Gamepad gamepad;
    Stage stage;
    Snake snake;
    FruitFactory fruitFactory;
    
    uint8_t* currentMap;
    int score;
    
    Direction direction;
    Size stageSize;
    Point2D initialPosition;
    Point2D initialStagePosition;
    Point2D initialSnakePosition;

    bool gameEnded = false;
    bool running = false;
    bool paused = false;
    bool startPressed = false;
};