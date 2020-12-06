/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "Direction.h"
#include "GamepadException.h"

#include "InputLib/Joypad.h"
#include "InputLib/Button.h"

class Gamepad
{
public:
    Gamepad();
    void ReadInput();
    bool GetButtonState(InputLib::Button button);
    Direction GetDirection();

private:
    void InitializeGamepad();

    InputLib::InputEvent joypadEvents;
    InputLib::Joypad* joypad;
};