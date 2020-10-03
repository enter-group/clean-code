#ifndef STAGE_H_
#define STAGE_H_

#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdint>
#include "Segment.h"
#include "Direction.h"
#include "Position.h"
#include "Size.h"
#include "GameConstants.h"

class Stage
{
public:
    Stage(const uint8_t* roomReference, const size_t roomWitdh, const size_t roomHeight);
    ~Stage();
    void SetStageRoom(const uint8_t* roomReference, const size_t roomWitdh, const size_t roomHeight);
    void SetRoomHorizontalOffset(int h);
    void SetRoomVerticalOffset(int v);
    int GetRoomHorizontalOffset();
    int GetRoomVerticalOffset();
    uint8_t* GetRoomReference();
    Size GetRoomSize();
    void Reset(const uint8_t* roomReference, const size_t roomWitdh, const size_t roomHeight);

private:
    int roomHorizontalOffset;
    int roomVerticalOffset;    
    Size RoomSize;
    uint8_t* ActiveRoom;
};

#endif // STAGE_H_