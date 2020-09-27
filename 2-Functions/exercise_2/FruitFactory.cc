#include "FruitFactory.h"

FruitFactory::FruitFactory(Stage& stage)
{
    CreateFruitAtRandomPosition(stage);
    CreateFruitAtRandomPosition(stage);
    CreateFruitAtRandomPosition(stage);
}

void FruitFactory::CreateFruitAtRandomPosition(Stage& stage)
{
    Position pos;
    do
    {
        pos.y = rand()%(stage.GetRoomSize().height - 1);
        pos.x = rand()%(stage.GetRoomSize().width - 1);
    } 
    while (stage.GetRoomReference()[(pos.y*stage.GetRoomSize().width) + pos.x] != 0);
    
    stage.GetRoomReference()[(pos.y*stage.GetRoomSize().width) + pos.x] = 100;

    fruits.push_back(pos);
}