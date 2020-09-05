#include "Snake.h"

using namespace std;

Snake::Snake()
{
    Reset();
}

void Snake::Reset()
{
    hasCollided = false;
    movingDirection = Direction::right;
    snakeSize.resize(0);

    for (int i = 0; i < initialBodyLength; i++)
    {
        Segment seg;
        seg.SetPosition(i, intiialBodyYPosition);
        snakeSize.push_back(seg);
    }
}

void Snake::UpdateDirection(Direction newDirection)
{
    if (newDirection == Direction::down && movingDirection != Direction::up) 
        movingDirection = Direction::down;
    else if (newDirection == Direction::up && movingDirection != Direction::down) 
        movingDirection = Direction::up;
    else if (newDirection == Direction::left && movingDirection != Direction::right) 
        movingDirection = Direction::left;
    else if (newDirection == Direction::right && movingDirection != Direction::left) 
        movingDirection = Direction::right;
}

bool Snake::HasCollided()
{
    return hasCollided;
}

void Snake::UpdatePosition()
{
    Segment head = snakeSize[snakeSize.size() - 1];
    int x = head.GetX();
    int y = head.GetY();

    if (movingDirection == Direction::right)
        x++;
    else if (movingDirection == Direction::down)
        y++;
    else if (movingDirection == Direction::left)
        x--;
    else if (movingDirection == Direction::up)
        y--;

    head.SetPosition(x, y);
    snakeSize.erase(snakeSize.begin());
    snakeSize.push_back(head);
}

void Snake::UpdateCollisionState()
{
    Segment head = snakeSize[snakeSize.size() - 1];
    int x = head.GetX();
    int y = head.GetY();

    if (std::count(snakeSize.begin(), snakeSize.end() - 1, head))
        hasCollided = true;
    else if (x == 0 || x == playfieldWidth - 1)
        hasCollided = true;
     else if (y == 0 || y == playfieldHeight - 1)
        hasCollided = true;
}

int Snake::Length()
{
    return snakeSize.size();
}

Direction Snake::GetDir()
{
    return movingDirection;
}

void Snake::TryToEatFruit(Fruit& fruit, int& score)
{
    if (std::count(snakeSize.begin(), snakeSize.end() - 1, fruit))
    {
        fruit.PlaceAtRandomPosition();
        auto it = snakeSize.begin();

        snakeSize.insert(it, snakeSize[0]);
        score += eatenFruitScoreIncrement + snakeSize.size();
    }
}