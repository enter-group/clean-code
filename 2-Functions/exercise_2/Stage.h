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
    Stage(const uint8_t* roomReference, const Size roomSize);
    ~Stage();

    void Reset(const uint8_t* roomReference, const Size roomSize);
    void SetTileAt(Position pos, uint8_t tileType);
    void SetStageRoom(const uint8_t* roomReference, const Size roomSize);
    void SetStageHorizontalOffset(int h);
    void SetStageVerticalOffset(int v);
    void SetStageOffsets(int h, int v);

    int GetStageHorizontalOffset();
    int GetStageVerticalOffset();

    uint8_t* GetRoomReference();
    uint8_t GetTileAt(Position pos);

    Size GetStageSize();
    Position ScreenToGlobalPosition(Position position);

private:
    int horizontalOffset;
    int verticalOffset;    
    Size StageSize;
    uint8_t* ActiveRoom;
};

#endif // STAGE_H_