#include "Stage.h"

Stage::Stage(const uint8_t* roomReference, Size roomSize)
{
    ActiveRoom = nullptr;
    Reset(roomReference, roomSize);
}

Stage::~Stage()
{
    delete[] ActiveRoom;
}

void Stage::Reset(const uint8_t* roomReference, const Size roomSize)
{
    horizontalOffset = 0;
    verticalOffset = 0;   

    SetStageRoom(roomReference, roomSize);
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

uint8_t Stage::GetTileAt(Position pos)
{
    return GetRoomReference()[(pos.y)*GetStageSize().width + (pos.x)];
}

void Stage::SetTileAt(Position pos, uint8_t tileType)
{
    GetRoomReference()[(pos.y)*GetStageSize().width + (pos.x)] = tileType;
}

Position Stage::ScreenToGlobalPosition(Position position)
{
    Position pos;
    pos.x = position.x + horizontalOffset;
    pos.y = position.y + verticalOffset;
    return pos;
}