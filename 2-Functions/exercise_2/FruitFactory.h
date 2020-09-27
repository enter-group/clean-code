#ifndef FRUIT_FACTORY_H_
#define FRUIT_FACTORY_H_

#include <cstdint>
#include <stdlib.h>
#include <vector>
#include "GameConstants.h"
#include "Position.h"
#include "Stage.h"

class FruitFactory
{

public:
    FruitFactory(Stage& stage);
    void CreateFruitAtRandomPosition(Stage& stage);

private:
    std::vector<Position> fruits;
};

#endif // FRUIT_FACTORY_H_