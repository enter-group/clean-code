#include "Stage.h"

Stage::Stage(const uint8_t* roomReference, const size_t roomWitdh, const size_t roomHeight)
{
    ActiveRoom = nullptr;
    Reset(roomReference, roomWitdh, roomHeight);
}

Stage::~Stage()
{
    delete[] ActiveRoom;
}

void Stage::Reset(const uint8_t* roomReference, const size_t roomWitdh, const size_t roomHeight)
{
    roomHorizontalOffset = 0;
    roomVerticalOffset = 0;   

    SetStageRoom(roomReference, roomWitdh, roomHeight);
}

void Stage::SetStageRoom(const uint8_t* roomReference, const size_t roomWitdh, const size_t roomHeight)
{
    if(ActiveRoom == nullptr)
        ActiveRoom = new uint8_t[roomHeight*roomWitdh];

    std::memcpy(ActiveRoom, roomReference, roomHeight*roomWitdh);
    RoomSize.width = roomWitdh;
    RoomSize.height = roomHeight;
}

void Stage::SetRoomHorizontalOffset(int h)
{
    roomHorizontalOffset = h;
}

void Stage::SetRoomVerticalOffset(int v)
{
    roomVerticalOffset = v;
}

int Stage::GetRoomHorizontalOffset()
{
    return roomHorizontalOffset;
}

int Stage::GetRoomVerticalOffset()
{
    return roomVerticalOffset;
}

uint8_t* Stage::GetRoomReference()
{
    return ActiveRoom;
}

Size Stage::GetRoomSize()
{
    return RoomSize;
}