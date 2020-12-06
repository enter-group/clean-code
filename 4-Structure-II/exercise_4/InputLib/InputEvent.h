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
class InputEvent
{
public:
    InputEvent(bool buttons[10], int axis[6], int id);
    InputEvent();

    int GetPlayerId();
    bool GetButtonByIndex(uint8_t index);
    int GetAxis5();
    int GetAxis4();
    int GetAxis3();
    int GetAxis2();
    int GetAxis1();
    int GetAxis0();

    static InputEvent DummyEvent;

private:
    int playerId;
    bool buttons[10];
    int axis0;
    int axis1;
    int axis2;
    int axis3;
    int axis4;
    int axis5;
};
}