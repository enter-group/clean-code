/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <exception>
#include <string>

namespace InputLib
{
class InputException : std::exception
{
public:
    InputException(std::string message);
    virtual const char* what() const throw();
    virtual ~InputException() _NOEXCEPT;
private:
    std::string message;

};
}