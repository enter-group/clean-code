/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <cstdlib>

struct Size
{
    size_t width;
    size_t height;

    static Size MakeSize(size_t width, size_t height);
};