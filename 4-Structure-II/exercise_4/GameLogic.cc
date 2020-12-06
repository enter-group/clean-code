#include "GameLogic.h"

using namespace std;
using namespace InputLib;
using namespace LandLib;

GameLogic::GameLogic()
    : gamepad(2)
    , score(0)
    , direction(Direction::none)
{
    GenerateMap();
}

void GameLogic::GenerateRandomStageSize()
{
    stageSize = Size::MakeSize(rand()%maxStageWidth + minStageWidth, rand()%maxStageHeight + minStageHeight);
    stageSize.width = stageSize.width%2 == 1? stageSize.width : stageSize.width + 1;
    stageSize.height = stageSize.height%2 == 1? stageSize.height : stageSize.height + 1;
}

void GameLogic::GenerateRandomStage()
{
    currentMap = mapGenerator.GenerateMap(stageSize.width, stageSize.height);
    stage.SetRoom(currentMap, Size::MakeSize(stageSize.width, stageSize.height));
    fruitFactory.Reset(stage);
}

void GameLogic::GenerateMap()
{
    GenerateRandomStageSize();
    GenerateRandomStage();
    CalculateInitialPositions();
    
}

void GameLogic::CalculateInitialPositions()
{
    initialPosition = Point2D::MakePosition(0,0);
    
    do
    {
        initialStagePosition = stage.ChooseInitialPosition();
        CalculateHorizontalInitialPosition();
        CalculateVerticalInitialPosition();
    }
    while (stage.GetRoomReference()[initialSnakePosition.y*stageSize.width + initialSnakePosition.x] != 0);

    stage.SetStageOffsets(initialPosition.x, initialPosition.y);
    snake.PlaceBodyAtAbsolute(initialSnakePosition);
}

void GameLogic::CalculateHorizontalInitialPosition()
{
    if (initialStagePosition.x - windowWidth/2 < 0)
    {    
        initialPosition.x = 0;
        initialSnakePosition.x = initialStagePosition.x;
    }
    else if (initialStagePosition.x - windowWidth/2 >= static_cast<int>(stageSize.width) - windowWidth)
    {
        initialPosition.x = stageSize.width - windowWidth;
        initialSnakePosition.x = initialStagePosition.x%windowWidth;
    }
    else
    {
        initialPosition.x = initialStagePosition.x - windowWidth/2;
        initialSnakePosition.x = windowWidth/2;
    }
}

void GameLogic::CalculateVerticalInitialPosition()
{
    if (initialStagePosition.y - windowHeight/2 < 0)
    {     
        initialPosition.y = 0;
        initialSnakePosition.y = initialStagePosition.y;
    }
    else if (initialStagePosition.y - windowHeight/2 >= static_cast<int>(stageSize.height) - windowHeight)
    {    
        initialPosition.y = stageSize.height - windowHeight;
        initialSnakePosition.y = initialStagePosition.y%windowHeight;
    }
    else
    {    
        initialPosition.y = initialStagePosition.y - windowHeight/2;;
        initialSnakePosition.y = windowHeight/2;
    }
}

void GameLogic::ResetGameObjects()
{
    delete[] currentMap;
    currentMap = nullptr;
    stage.ClearRoom();
    snake.Reset();

    GenerateMap();
    stage.SetRoom(currentMap, Size::MakeSize(stageSize.width, stageSize.height));
    fruitFactory.Reset(stage);
    score = 0;
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

void GameLogic::RenderGame()
{
    if (paused)
        Renderer::RenderPauseText();
    else if (!snake.HasCollided())
        Renderer::RenderGame(stage, snake, score);
    else
        Renderer::RenderGameOverScreen();

    getch();
}

void GameLogic::ExecuteGameLogic()
{
    UpdateSnakeBasedOnPosition();
    snake.CalculateCollisionsWithHazards(stage);
    snake.CalculateCollisionsWithFruits(stage);
        
    if (snake.HasEatenFruitThisFrame())
        ProcessEatenFruit();
}

void GameLogic::EndGame()
{
    if (startPressed)
        ResetGameObjects();
}

void GameLogic::DetermineMovementDelay(Direction snakeDirection)
{
    if (!running)
    {
        if (snakeDirection == Direction::left || snakeDirection == Direction::right)
            std::this_thread::sleep_for(std::chrono::milliseconds(horizontalDelayInMilliseconds));
        else  if (snakeDirection == Direction::up || snakeDirection == Direction::down)
            std::this_thread::sleep_for(std::chrono::milliseconds(verticalDelayInMilliseconds));
    }
    else
    {
        if (snakeDirection == Direction::left || snakeDirection == Direction::right)
            std::this_thread::sleep_for(std::chrono::milliseconds(horizontalRunningDelayInMilliseconds));
        else  if (snakeDirection == Direction::up || snakeDirection == Direction::down)
            std::this_thread::sleep_for(std::chrono::milliseconds(verticalRunningDelayInMilliseconds));
    }
}

void GameLogic::UpdatePauseFlag()
{
    if (gamepad.InputEvent2ButtonState(gamepad.GetPlayerEvent(0), Button::ButtonStart) && !startPressed)
    {
        startPressed = true;
        if (!snake.HasCollided())
            paused = !paused;
    }
    if (!gamepad.InputEvent2ButtonState(gamepad.GetPlayerEvent(0), Button::ButtonStart) && startPressed)
        startPressed = false;
}

void GameLogic::ProcessPlayerInput()
{
    gamepad.ReadInput();

    if (gamepad.InputEvent2ButtonState(gamepad.GetPlayerEvent(0), Button::ButtonStart) && 
        gamepad.InputEvent2ButtonState(gamepad.GetPlayerEvent(0), Button::ButtonC))
        gameEnded = true;

    direction = gamepad.InputEvent2Direction(gamepad.GetPlayerEvent(0));
    running = gamepad.InputEvent2ButtonState(gamepad.GetPlayerEvent(0), Button::ButtonA);
    UpdatePauseFlag();
    
}

void GameLogic::RunGame()
{
    while(!gameEnded)
	{	
        ProcessPlayerInput();
        if (!paused)
        {
            DetermineMovementDelay(snake.GetDirection());
            if (snake.HasCollided())
                EndGame();
            else
                ExecuteGameLogic();
        }

        RenderGame();
	}
}