/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#ifndef SIZE_H_
#define SIZE_H_

#include <cstdlib>

struct Size
{
    size_t width;
    size_t height;

    static Size MakeSize(size_t width, size_t height);
};

#endif // SIZE_H_