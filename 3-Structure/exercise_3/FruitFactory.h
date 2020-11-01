/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#ifndef FRUIT_FACTORY_H_
#define FRUIT_FACTORY_H_

#include <cstdint>
#include <stdlib.h>
#include <vector>

#include "GameConstants.h"
#include "Point2D.h"
#include "Stage.h"

class FruitFactory
{
public:
    void Reset(Stage& stage);
    void CreateFruitAtRandomPosition(Stage& stage);

private:
    Point2D GenerateRandomPosition(Stage& stage);
    
};

#endif // FRUIT_FACTORY_H_