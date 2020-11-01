#include "GameLogic.h"

GameLogic::GameLogic()
    : score(0)
    , pressedKey(0)
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
    if (pressedKey == KEY_F(3))
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
    while((pressedKey = getch()) != KEY_F(2))
	{	
        DetermineMovementDelay(snake.GetDirection());
        
        if (snake.HasCollided())
            EndGame();
        else
            ExecuteGameLogic();

        RenderGame();
	}
}