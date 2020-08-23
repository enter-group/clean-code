#include "Snake.h"

using namespace std;

Snake::Snake()
{
    Setup();
}

void Snake::Setup()
{
    collision = false;
    dir = USE_OF_0X27;
    snakeSize.resize(0);

    for (int i = 0; i < LEN0; i++)
    {
        Piece seg1;
        seg1.SetPosition(i, 1);
        snakeSize.push_back(seg1);
    }
}

void Snake::SetD(int value)
{
    if (value == 0 && dir != USE_OF_0X26) 
        dir = USE_OF_0X28;
    else if (value == 1 && dir != USE_OF_0X28) 
        dir = USE_OF_0X26;
    else if (value == 2 && dir != USE_OF_0X27) 
        dir = USE_OF_0X25;
    else if (value == 3 && dir != USE_OF_0X25) 
        dir = USE_OF_0X27;
}

bool Snake::Crash()
{
    return collision;
}

void Snake::MoveMe()
{
    auto head = snakeSize[snakeSize.size() - 1];
    auto x = head.__x();
    auto y = head.__y();

    if (dir == USE_OF_0X27)
        x++;
    else if (dir == USE_OF_0X28)
        y++;
    else if (dir == USE_OF_0X25)
        x--;
    else if (dir == USE_OF_0X26)
        y--;

    head.SetPosition(x, y);
    snakeSize.erase(snakeSize.begin());
    snakeSize.push_back(head);
}

void Snake::UpdateCrash()
{
    auto head = snakeSize[snakeSize.size() - 1];
    auto x = head.__x();
    auto y = head.__y();

    if (std::count(snakeSize.begin(), snakeSize.end() - 1, head))
        collision = true;
    else if (x == 0 || x == 77)
        collision = true;
     else if (y == 0 || y == 19)
        collision = true;
}

int Snake::Length()
{
    return snakeSize.size();
}

int Snake::GetDir()
{
    return dir;
}

bool Snake::Yummy(Fruit& in_out_fruit, int& out_sc)
{
    if (std::count(snakeSize.begin(), snakeSize.end() - 1, in_out_fruit))
    {
        in_out_fruit.Drop();
        auto it = snakeSize.begin();

        snakeSize.insert(it, snakeSize[0]);
        out_sc += 10 + snakeSize.size();
    }

    return true;
}