#include "Stage.h"

Stage::Stage()
{
    ActiveRoom = nullptr;
    CheckBoard = nullptr;
}

Stage::~Stage()
{
    delete[] ActiveRoom;
    delete[] CheckBoard;
}

void Stage::SetRoom(const uint8_t* roomReference, const Size roomSize)
{
    SetStageRoom(roomReference, roomSize);
}

void Stage::ClearRoom()
{
    delete[] ActiveRoom;
    ActiveRoom = nullptr;
}

void Stage::SetStageRoom(const uint8_t* roomReference, Size roomSize)
{
    if(ActiveRoom == nullptr)
        ActiveRoom = new uint8_t[roomSize.height*roomSize.width];

    std::memcpy(ActiveRoom, roomReference, roomSize.height*roomSize.width);
    StageSize.width = roomSize.width;
    StageSize.height = roomSize.height;
}

void Stage::SetStageHorizontalOffset(int h)
{
    horizontalOffset = h;
}

void Stage::SetStageVerticalOffset(int v)
{
    verticalOffset = v;
}

void Stage::SetStageOffsets(int h, int v)
{
    SetStageHorizontalOffset(h);
    SetStageVerticalOffset(v);
}

int Stage::GetStageHorizontalOffset()
{
    return horizontalOffset;
}

int Stage::GetStageVerticalOffset()
{
    return verticalOffset;
}

uint8_t* Stage::GetRoomReference()
{
    return ActiveRoom;
}

Size Stage::GetStageSize()
{
    return StageSize;
}

uint8_t Stage::GetTileAt(Point2D pos)
{
    return GetRoomReference()[(pos.y)*GetStageSize().width + (pos.x)];
}

void Stage::SetTileAt(Point2D pos, uint8_t tileType)
{
    GetRoomReference()[(pos.y)*GetStageSize().width + (pos.x)] = tileType;
}

Point2D Stage::ScreenToGlobalPosition(Point2D position)
{
    Point2D pos;
    pos.x = position.x + horizontalOffset;
    pos.y = position.y + verticalOffset;
    return pos;
}

Point2D Stage::ChooseInitialPosition()
{
    Point2D foundPosition;

    do foundPosition = GetRandomPosition();
    while (!IsPositionValid(foundPosition));

    return foundPosition;
}

Point2D Stage::GetRandomPosition()
{
    Point2D position;
    position.x = 6 + rand()%((static_cast<int>(StageSize.width) - playfieldWidth) - 13);
    position.y = 6 + rand()%((static_cast<int>(StageSize.height) - playfieldHeight)- 13);
    return position;
}

bool Stage::IsPositionValid(Point2D position)
{
    bool failed = false;
    for (int i = position.y - 5; i < position.y + 5; i++)
    {
        for (int j = position.x - 5; j < position.x + 5; j++)
            if (IsHazard(GetRoomReference()[(i)*StageSize.width + (j)]))
            {
                failed = true;
                break;
            }

        if (failed)
            break;
    }

    return !failed;
}

bool Stage::IsHazard(int tileType)
{
    return tileType == static_cast<uint8_t>(TerrainType::MountainLv1) ||
           tileType == static_cast<uint8_t>(TerrainType::MountainLv2) ||
           tileType == static_cast<uint8_t>(TerrainType::MountainLv3) ||
           tileType == static_cast<uint8_t>(TerrainType::MountainLv4) ||
           tileType == static_cast<uint8_t>(TerrainType::MountainLv5) ||
           tileType == static_cast<uint8_t>(TerrainType::MountainLv6) ||
           tileType == static_cast<uint8_t>(TerrainType::River) ||
           tileType == static_cast<uint8_t>(TerrainType::Wall);
}