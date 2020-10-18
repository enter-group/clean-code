#include "GameLogic.h"

GameLogic::GameLogic()
    : stage(Room::Layout, Size::MakeSize(Room::RoomWidth, Room::RoomHeight))
    , score(0)
    , pressedKey(0)
    , direction(Direction::none)
{
    fruitFactory.Reset(stage);
}

void GameLogic::ResetGameObjects()
{
    snake.Reset();
    stage.Reset(Room::Layout, Size::MakeSize(Room::RoomWidth, Room::RoomHeight));
    fruitFactory.Reset(stage);
    score = 0;
    pressedKey = 0;
    direction = Direction::none;
}

void GameLogic::ProcessEatenFruit()
{
    stage.SetTileAt(stage.ScreenToGlobalPosition(snake.GetHeadLocalPosition()), 0);
    snake.AddNewSegment();
    score += eatenFruitScoreIncrement + snake.Length();
    fruitFactory.CreateFruitAtRandomPosition(stage);
    snake.ClearHasEatenFruitThisFrame();
}

void GameLogic::UpdateSnakeBasedOnPosition()
{
    if (direction != Direction::none)
        snake.UpdateDirection(direction);

    snake.UpdatePosition();
}

void GameLogic::ProcessKeys()
{
    switch (pressedKey)
    {
        case KEY_DOWN:  direction = Direction::down; break;
        case KEY_UP:    direction = Direction::up; break;
        case KEY_LEFT:  direction = Direction::left; break;
        case KEY_RIGHT: direction = Direction::right; break;
    }
}

void GameLogic::RenderGame()
{
    if (!snake.HasCollided())
        Renderer::RenderGame(stage, snake, score);
    else
        Renderer::RenderGameOverScreen();
}

void GameLogic::ExecuteGameLogic()
{
    ProcessKeys();
    UpdateSnakeBasedOnPosition();
    snake.CalculateCollisionsWithHazards(stage);
    snake.CalculateCollisionsWithFruits(stage);
        
    if (snake.HasEatenFruitThisFrame())
        ProcessEatenFruit();
}

void GameLogic::EndGame()
{
    if (pressedKey == KEY_F(2))
        ResetGameObjects();
}

void GameLogic::DetermineMovementDelay(Direction snakeDirection)
{
    if (snakeDirection == Direction::left || snakeDirection == Direction::right)
        std::this_thread::sleep_for(std::chrono::milliseconds(horizontalDelayInMilliseconds));
    else  if (snakeDirection == Direction::up || snakeDirection == Direction::down)
        std::this_thread::sleep_for(std::chrono::milliseconds(verticalDelayInMilliseconds));
}

void GameLogic::RunGame()
{
    while((pressedKey = getch()) != KEY_F(1))
	{	
        DetermineMovementDelay(snake.GetDirection());

        if (snake.HasCollided())
            EndGame();
        else
            ExecuteGameLogic();

        RenderGame();
	}
}