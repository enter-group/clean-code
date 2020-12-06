/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <vector>

#include "Button.h"
#include "Direction.h"

#include "InputLib/Joypad.h"

class Gamepad
{
public:
    Gamepad(uint8_t numberOfPlayers);
    void ReadInput();
    InputLib::InputEvent* GetPlayerEvent(uint8_t playerId);
    Direction InputEvent2Direction(InputLib::InputEvent* event);
    bool InputEvent2ButtonState(InputLib::InputEvent* event, Button button);

private:
    void InitializeGamepad(uint8_t numberOfPlayers);
    void InitializeEventBuffer();

    uint8_t numberOfPlayers;
    std::vector<InputLib::InputEvent> joypadEvents;
    InputLib::Joypad* joypad;
};