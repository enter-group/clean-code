#ifndef PIECE_H_
#define PIECE_H_

#include "Fruit.h"

// Pieces Class
class Piece
{

friend class Renderer;

public:
    // Default Constructor
    Piece() = default;

    // Set Position in pairs
    void SetPosition(int x, int y);

    // Get Position X
    int GetPositionX();

    // Get Position Y
    int GetPositionY();

    // Operator overload for comparison
    bool operator==(Piece bodyObjectToBeCompared);
    bool operator==(Fruit bodyObjectToBeCompared);

private:
    int x;
    int y;
};

#endif // PIECE_H_