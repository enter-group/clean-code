#include "InputEvent.h"

using namespace std;

namespace InputLib
{

InputEvent InputEvent::DummyEvent;

InputEvent::InputEvent()
    : playerId(-1)
    , axis0(0)
    , axis1(0)
    , axis2(0)
    , axis3(0)
    , axis4(0)
    , axis5(0)
{
    for (int i = 0; i < 10; i++)
        buttons[i]= 0;
}

InputEvent::InputEvent(bool buttons[10], int axis[6], int id)
    : playerId(id)
    , axis0(axis[0])
    , axis1(axis[1])
    , axis2(axis[2])
    , axis3(axis[3])
    , axis4(axis[4])
    , axis5(axis[5])
{
    copy(buttons, buttons + 10, this->buttons);
}

int InputEvent::GetPlayerId()
{
    return playerId;
}

bool InputEvent::GetButtonByIndex(uint8_t index)
{
    return buttons[index];
}

int InputEvent::GetAxis5()
{
    return axis5;
}

int InputEvent::GetAxis4()
{
    return axis4;
}

int InputEvent::GetAxis3()
{
    return axis3;
}

int InputEvent::GetAxis2()
{
    return axis2;
}

int InputEvent::GetAxis1()
{
    return axis1;
}

int InputEvent::GetAxis0()
{
    return axis0;
}

}