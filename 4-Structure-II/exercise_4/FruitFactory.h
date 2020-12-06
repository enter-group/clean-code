/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

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