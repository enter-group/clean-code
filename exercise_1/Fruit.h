#ifndef FRUIT_H_
#define FRUIT_H_

#include <stdlib.h>

// Renderer Constants
#define SCREEN_OFFST_X 1
#define SCREEN_OFFST_y 3


// Fruid Class
class Fruit
{

friend class Renderer;

public:
    // Constructor
    Fruit();

    // Update location
    void Drop();

    // Return X position
    int GetX();

    // Return Y position
    int GetY();

private:
    // Coordinate 1
    int c1;

    // Coordinate 2
    int c2;
};

#endif // FRUIT_H_