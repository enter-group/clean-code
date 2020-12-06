/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <exception>
#include <string>

class GamepadException : std::exception
{
public:
    GamepadException(std::string message);
    virtual const char* what() const throw();
    virtual ~GamepadException() _NOEXCEPT;
private:
    std::string message;

};