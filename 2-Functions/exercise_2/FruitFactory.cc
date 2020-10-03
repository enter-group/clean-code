#include "FruitFactory.h"

void FruitFactory::Reset(Stage& stage)
{
    CreateFruitAtRandomPosition(stage);
    CreateFruitAtRandomPosition(stage);
    CreateFruitAtRandomPosition(stage);
}

void FruitFactory::CreateFruitAtRandomPosition(Stage& stage)
{
    Position pos = GenerateRandomPosition(stage);
    stage.GetRoomReference()[(pos.y*stage.GetStageSize().width) + pos.x] = 100;
}

Position FruitFactory::GenerateRandomPosition(Stage& stage)
{
    Position pos;
    do
    {
        pos.y = rand()%(stage.GetStageSize().height - 1);
        pos.x = rand()%(stage.GetStageSize().width - 1);
    } 
    while (stage.GetRoomReference()[(pos.y*stage.GetStageSize().width) + pos.x] != 0);
    
    return pos;
}