/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <algorithm>
#include <iterator>

#include <cstdint>
#include <cstdlib>

namespace InputLib
{
struct InputEvent
{
    int playerId;
    bool isAButtonPressed;
    bool isBButtonPressed;
    bool isCButtonPressed;
    bool isStartButtonPressed;
    int horizonalAxis;
    int verticalAxis;
};
}