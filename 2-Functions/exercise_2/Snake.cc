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
    body.resize(0);

    for (int i = 0; i < initialBodyLength; i++)
    {
        Segment seg;
        seg.SetPosition(i, initialBodyYPosition);
        body.push_back(seg);
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
    Segment head = body[body.size() - 1];
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
    body.erase(body.begin());
    body.push_back(head);
}

void Snake::UpdateCollisionState(Stage& stage, int& score, bool& operationStatus)
{
    Segment head = body[body.size() - 1];
    head.SetPosition(head.GetX() + stage.GetRoomHorizontalOffset(), head.GetY() + stage.GetRoomVerticalOffset());
    uint32_t x = head.GetX();
    uint32_t y = head.GetY();

    int currentTile = stage.GetRoomReference()[(y)*stage.GetRoomSize().width + (x)];
    if (std::count(body.begin(), body.end() - 1, body[body.size() - 1]))
        hasCollided = true;
    else if (x == 0 || x == stage.GetRoomSize().width - 1)
        hasCollided = true;
     else if (y == 0 || y == stage.GetRoomSize().height - 1)
        hasCollided = true;
    else if (currentTile == 1 ||
             currentTile == 2 || 
             currentTile == 3)
    {
        hasCollided = true;
    }
    else
    {
        if (stage.GetRoomReference()[(y)*stage.GetRoomSize().width + (x)] == 100)
        {
            stage.GetRoomReference()[(y)*stage.GetRoomSize().width + (x)] = 0;
        
            auto it = body.begin();
            body.insert(it, body[0]);
            score += eatenFruitScoreIncrement + body.size();

            operationStatus = true;
            return;
        }

        operationStatus = false;
    }
    
}

void Snake::SetPosition(Position position)
{
    Segment head = body[body.size() - 1];
    int xOffset = head.GetX() - position.x;
    int yOffset = head.GetY() - position.y;

    for (size_t i = 0; i < body.size(); i++)
        body[i].SetPosition(body[i].GetX() + xOffset, body[i].GetY() + yOffset);
}

int Snake::Length()
{
    return body.size();
}

Direction Snake::GetDirection()
{
    return movingDirection;
}

Position Snake::GetHeadPosition()
{
    Position pos;
    Segment head = body[body.size() - 1];
    pos.x = head.GetX();
    pos.y = head.GetY();

    return pos;
}