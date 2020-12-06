#include "GamepadException.h"

GamepadException::GamepadException(std::string message)
{
    this->message = message;
}

const char* GamepadException::what() const throw()
{
    return message.c_str();
}

GamepadException::~GamepadException() _NOEXCEPT
{}
