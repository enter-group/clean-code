#include "Gamepad.h"

using namespace InputLib;
using namespace std;

Gamepad::Gamepad()
{
    InitializeGamepad();
}

void Gamepad::InitializeGamepad()
{
    joypad = new Joypad(1);
    joypad->InitializeJoypad();
}

void Gamepad::ReadInput()
{
    try
    {
        auto inputEvent = joypad->ReadButtons(0);
        joypadEvents = inputEvent;
    }
    catch (InputException e)
    {
        GamepadException ex("Controller not found");
        throw ex;
    }
}

bool Gamepad::GetButtonState(InputLib::Button button)
{
    switch (button)
    {
        case Button::ButtonA: return joypadEvents.isAButtonPressed;
        case Button::ButtonB: return joypadEvents.isBButtonPressed;
        case Button::ButtonC: return joypadEvents.isCButtonPressed;
        case Button::ButtonStart: return joypadEvents.isStartButtonPressed;
    }

    return false;
}

Direction Gamepad::GetDirection()
{
    Direction direction = Direction::none;

    if (joypadEvents.verticalAxis == -32766)
        direction = Direction::up;
    if (joypadEvents.verticalAxis == 32768)
        direction = Direction::down;
    if (joypadEvents.horizonalAxis == -32766)
        direction = Direction::left;
    if (joypadEvents.horizonalAxis == 32768)
        direction = Direction::right;

    return direction;
}