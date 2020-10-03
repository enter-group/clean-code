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
    void Reset(Stage& stage);
    void CreateFruitAtRandomPosition(Stage& stage);

private:
    Position GenerateRandomPosition(Stage& stage);
    
};

#endif // FRUIT_FACTORY_H_