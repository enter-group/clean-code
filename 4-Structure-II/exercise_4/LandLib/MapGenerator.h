/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <limits>
#include <thread>

#include "Perlin.h"

namespace LandLib
{

// Supported Terrain Types
// It is up to the application to define which terrain type is a hazard.
enum class TerrainType
{
    Ground = 0,
    Wall = 1,
    MountainLv1 = 2,
    MountainLv2 = 3,
    MountainLv3 = 4,
    MountainLv4 = 5,
    MountainLv5 = 6,
    MountainLv6 = 7,
    River = 8,
    Bridge = 9
};

// Enumeration identifying the randomly-generated river (horizontal, vertical).
// NoDirection means *abscense* of rivers in the generated map.
enum class RiverDirection
{
    Vertical = 0,
    Horizonal = 1,
    NoDirection = 2
};

class MapGenerator
{
public:
    MapGenerator() = default;
    ~MapGenerator() = default;

    // Automatically Generates a Random Map with dimensions (width x height) using Perlin Noise.
    // @param width: Map Width
    // @param height: Map Height;
    // @ret: Reference to an internally-dynamically allocated 2D array of points.
    uint8_t* GenerateMap(size_t width, size_t height);

private:
    uint8_t* AllocateMap();

    size_t GetRandomBridgeColumn();
    size_t GetRandomBridgeRow();
    size_t SafeIndex(size_t row, size_t col);
    size_t FindInitialRiverColumn();
    size_t FindInitialRiverRow();
    size_t CalculateBridgeWidth();
    size_t CalculateBridgeHeight();
    size_t FindBirdgeMinColumn();
    size_t FindBirdgeMaxColumn();
    size_t FindBirdgeMinRow();
    size_t FindBirdgeMaxRow();

    void GenerateBaseTopology();
    void GenerateRiver();
    void GenerateHorizontalRiver();
    void GenerateVerticalRiver();
    void ClearRiverSurroundings();
    void GenerateBridge();
    void GenerateHorizontalBridge();
    void GenerateVerticalBridge();
    void ExpandHorizontalBridge();
    void ExpandVerticalBridge();
    void GenerateWall();
    void FillHorizontalBridge(size_t minColumn, size_t maxColumn);
    void FillVerticalBridge(size_t minRow, size_t maxRow);

    RiverDirection riverDirecton;
    Perlin perlin;
    uint8_t* map;
    size_t width;
    size_t height;
    size_t targetLength;
    size_t initialRow;
    size_t initialColumn;
};
}