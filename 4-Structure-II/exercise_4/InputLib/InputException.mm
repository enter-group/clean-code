#include "InputException.h"

namespace InputLib
{

InputException::InputException(std::string message)
{
    this->message = message;
}

const char* InputException::what() const throw()
{
    return message.c_str();
}

InputException::~InputException() _NOEXCEPT
{}

}