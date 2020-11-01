#include "FruitFactory.h"

void FruitFactory::Reset(Stage& stage)
{
    for (size_t i = 0; i < 10; i++)
        CreateFruitAtRandomPosition(stage);
}

void FruitFactory::CreateFruitAtRandomPosition(Stage& stage)
{
    Point2D pos = GenerateRandomPosition(stage);
    stage.GetRoomReference()[(pos.y*stage.GetStageSize().width) + pos.x] = 100;
}

Point2D FruitFactory::GenerateRandomPosition(Stage& stage)
{
    Point2D pos;
    do
    {
        pos.y = rand()%(stage.GetStageSize().height - 1);
        pos.x = rand()%(stage.GetStageSize().width - 1);
    } 
    while (stage.GetRoomReference()[(pos.y*stage.GetStageSize().width) + pos.x] != 0);
    
    return pos;
}