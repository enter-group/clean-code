/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdint>
#include <limits>

#include "Segment.h"
#include "Direction.h"
#include "Point2D.h"
#include "Size.h"
#include "GameConstants.h"
#include "LandLib/MapGenerator.h"

class Stage
{
public:
    Stage();
    ~Stage();

    void SetRoom(const uint8_t* roomReference, const Size roomSize);
    void SetTileAt(Point2D pos, uint8_t tileType);
    void SetStageRoom(const uint8_t* roomReference, const Size roomSize);
    void SetStageHorizontalOffset(int h);
    void SetStageVerticalOffset(int v);
    void SetStageOffsets(int h, int v);
    void ClearRoom();

    int GetStageHorizontalOffset();
    int GetStageVerticalOffset();

    uint8_t* GetRoomReference();
    uint8_t GetTileAt(Point2D pos);

    bool IsHazard(int tileType);

    Size GetStageSize();
    Point2D ScreenToGlobalPosition(Point2D position);
    Point2D ChooseInitialPosition();

private:
    Point2D GetRandomPosition();
    bool IsPositionValid(Point2D position);

    int horizontalOffset;
    int verticalOffset;    
    Size StageSize;
    uint8_t* ActiveRoom;
    uint8_t* CheckBoard;
};