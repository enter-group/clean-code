#include "Size.h"

Size Size::MakeSize(size_t width, size_t height)
{
    Size s;
    s.width = width;
    s.height = height;

    return s;
}