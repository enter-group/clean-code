#pragma once

namespace InputLib
{
// Joypad Error Flags
enum JoypadErrorCodes
{
    // No error, operation OK.
    JoypadNoError   = 0x01,

    // Joypad not found (specific requested index has not been found).
    JoypadNotFound  = 0xBC,

    // Specific joypad initiaelizaiton failed.
    JoypadInitializationError = 0x10,

    // Requested joypad is out of bounds
    InvalidJoypadId = 0x92,
};
}