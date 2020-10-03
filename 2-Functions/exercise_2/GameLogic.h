#ifndef GAME_OBJECTS_H_
#define GAME_OBJECTS_H_

#include <thread>

#include "Snake.h"
#include "FruitFactory.h"
#include "Renderer.h"
#include "Direction.h"
#include "GameConstants.h"
#include "Room.h"
#include "Stage.h"

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

    Stage stage;
    FruitFactory fruitFactory;
    Snake snake;
    int score;
    int pressedKey;
    Direction direction;
};

#endif // GAME_OBJECTS_H_