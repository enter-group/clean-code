#include "Snake.h"

using namespace std;

Snake::Snake()
{
    Reset();
}

void Snake::ResetSnakeBody()
{
    for (int i = 0; i < initialBodyLength; i++)
    {
        Segment seg;
        seg.SetPosition(i, initialBodyYPosition);
        body.push_back(seg);
    }
}

void Snake::Reset()
{
    hasCollided = false;
    hasEatenFruitThisFrame = false;
    movingDirection = Direction::right;
    body.resize(0);
    ResetSnakeBody();
}

void Snake::UpdateDirection(Direction newDirection)
{
    if (newDirection == Direction::down && movingDirection != Direction::up) movingDirection = Direction::down;
    else if (newDirection == Direction::up && movingDirection != Direction::down) movingDirection = Direction::up;
    else if (newDirection == Direction::left && movingDirection != Direction::right) movingDirection = Direction::left;
    else if (newDirection == Direction::right && movingDirection != Direction::left)  movingDirection = Direction::right;
}

Segment Snake::GetHead()
{
    return body[body.size() - 1];
}

bool Snake::HasCollided()
{
    return hasCollided;
}

void Snake::MoveBodyToNewPosition(Position position)
{
    Segment head = GetHead();
    head.SetPosition(position.x, position.y);
    body.erase(body.begin());
    body.push_back(head);
}

Position Snake::CalculateNewPosition()
{
    Position pos = GetHeadLocalPosition();

    if (movingDirection == Direction::right) pos.x++;
    else if (movingDirection == Direction::down) pos.y++;
    else if (movingDirection == Direction::left) pos.x--;
    else if (movingDirection == Direction::up) pos.y--;
    return pos;
}

void Snake::UpdatePosition()
{
    Position pos = CalculateNewPosition();
    MoveBodyToNewPosition(pos);
}

Position Snake::CalculateHeadGlobalPosition(Stage& stage)
{
    Position pos = Position::MakePosition(GetHead().GetX(), GetHead().GetY());
    pos = stage.ScreenToGlobalPosition(pos);
    return pos;
}

bool Snake::HasCollidedWithBody()
{
    return std::count(body.begin(), body.end() - 1, body[body.size() - 1]);
}

bool Snake::HasCollidedWithWalls(Stage& stage)
{
    Position globalPosition = CalculateHeadGlobalPosition(stage);
    return globalPosition.x == 0 || 
           globalPosition.x == stage.GetStageSize().width - 1 || 
           globalPosition.y == 0 || 
           globalPosition.y == stage.GetStageSize().height - 1;
}

bool Snake::HadCollidedWithHazards(int tile)
{
    return tile == 1 || tile == 2 || tile == 3;
}

bool Snake::HadCollidedWithFruit(int tile)
{
    return tile == 100;
}

void Snake::AddNewSegment()
{
    auto it = body.begin();
    body.insert(it, body[0]);
}

void Snake::CalculateCollisionsWithHazards(Stage& stage)
{
    Position globalPosition = CalculateHeadGlobalPosition(stage);
    int currentTile = stage.GetTileAt(globalPosition);
    hasCollided = HasCollidedWithBody() || HasCollidedWithWalls(stage) || HadCollidedWithHazards(currentTile);
}

void Snake::CalculateCollisionsWithFruits(Stage& stage)
{
    Position globalPosition = CalculateHeadGlobalPosition(stage);
    int currentTile = stage.GetTileAt(globalPosition);

    if (HadCollidedWithFruit(currentTile))
        hasEatenFruitThisFrame = true;
}

void Snake::PlaceBodyAtPosition(Position position)
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

Position Snake::GetHeadLocalPosition()
{
    Position pos = Position::MakePosition(GetHead().GetX(), GetHead().GetY());
    return pos;
}

bool Snake::HasEatenFruitThisFrame()
{
    return hasEatenFruitThisFrame;
}

void Snake::ClearHasEatenFruitThisFrame()
{
    hasEatenFruitThisFrame = false;
}

void Snake::ClearHasCollided()
{
    hasCollided = false;
}