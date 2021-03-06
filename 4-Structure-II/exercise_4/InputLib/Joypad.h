/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <array>
#include <string>
#include <utility>

#include "InputEvent.h"
#include "JoypadErrorCodes.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#include <ois/OIS.h>
#pragma GCC diagnostic pop

namespace InputLib
{
class Joypad
{
public:
    Joypad(uint8_t maxDevices);
    ~Joypad();
    
    uint8_t GetNumberOfDetectedPlayers();

    Joypad* CreateNativeWindow();
    JoypadErrorCodes InitializeJoypad();

    std::pair<InputEvent, JoypadErrorCodes> UpdateUnbufferedDeviceState(uint8_t playerIndex);

private:
    void InitializeInputManager(size_t windowHandle);
    JoypadErrorCodes CreateJoypads();

    InputEvent AcquireJoypadInput(uint8_t index);
    std::array<int, 6> ReadJoypadAxis(uint8_t index);
    std::array<bool, 10> ReadJoypadButtons(uint8_t index);

    size_t windowHandle;
    uint8_t numberOfPlayers;
    uint8_t maxDevices;
    OIS::InputManager* inputManager;
    OIS::JoyStick** joypads;
};
}