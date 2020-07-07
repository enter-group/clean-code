#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include <algorithm>
#include "Piece.h"
#include "Fruit.h"

// Useful Constants!
#define USE_OF_0X28 0
#define USE_OF_0X26 1
#define USE_OF_0X27 2
#define USE_OF_0X25 3
#define LEN0 4

// Snake class
class Snake
{

friend class Renderer;

public:
    // Default Constructor
    Snake();

    // Initialize Snake
    void Setup();

    // Set Direction
    void SetD(int value);

    // Get Direction
    int GetDir();

    // Check for game over
    bool Crash();

    // Check position to see if a crash happened;
    void UpdateCrash();

    // Move Snake
    void MoveMe();

    // Get snake size.
    int Length();

    // Has eaten
    bool Yummy(Fruit& in_out_fruit, int& out_score);

private:
    // Pieces vector.
    std::vector<Piece> pieces;

    // Dir variable
    int dir;

    // collision
    bool collision;
};

#endif // SNAKE_H_