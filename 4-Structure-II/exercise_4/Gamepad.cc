#include "Gamepad.h"

using namespace InputLib;

Gamepad::Gamepad(uint8_t numberOfPlayers)
    : numberOfPlayers(numberOfPlayers)
{
    InitializeGamepad(numberOfPlayers);
    InitializeEventBuffer();
}

void Gamepad::InitializeEventBuffer()
{
    for (size_t i = 0; i < numberOfPlayers; i++)
        joypadEvents.push_back(InputEvent::DummyEvent);
}

void Gamepad::InitializeGamepad(uint8_t numberOfPlayers)
{
    joypad = new Joypad(numberOfPlayers);
    JoypadErrorCodes status = joypad->CreateNativeWindow()->InitializeJoypad();
    
    if (status != JoypadErrorCodes::JoypadNoError)
        exit((uint8_t)status);
}

void Gamepad::ReadInput()
{
    for (size_t i = 0; i < numberOfPlayers; i++)
    {
        auto deviceState = joypad->UpdateUnbufferedDeviceState(i);
        
        if (deviceState.second == JoypadErrorCodes::JoypadNoError)
            joypadEvents[i] = deviceState.first;
        else
            joypadEvents[i] = InputEvent::DummyEvent;
    }
}

Direction Gamepad::InputEvent2Direction(InputEvent* event)
{
    Direction direction = Direction::none;

    // if the controller is not found or has been disconnected, the event might be null.
    if (event != nullptr)
    {
        // -32766  and 32768 means the button is fully pressed!
        if (event->GetAxis5() == -32766)
            direction = Direction::up;
        if (event->GetAxis5() == 32768)
            direction = Direction::down;

        if (event->GetAxis4() == -32766)
            direction = Direction::left;
        if (event->GetAxis4() == 32768)
            direction = Direction::right;
    }

    return direction;
}

bool Gamepad::InputEvent2ButtonState(InputEvent* event, Button button)
{
    // if the controller is not found or has been disconnected, the event might be null.
    if (event != nullptr)
    {
        if (event->GetButtonByIndex(static_cast<uint8_t>(button)) == true)
            return true;
        else
            return false;
    }

    return false;
}

InputEvent* Gamepad::GetPlayerEvent(uint8_t playerId)
{
    if (playerId > numberOfPlayers)
        return nullptr;
    else if (joypadEvents[playerId].GetPlayerId() == -1)
        return nullptr;
    else
        return &joypadEvents[playerId];
}