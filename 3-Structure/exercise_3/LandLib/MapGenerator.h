/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#ifndef MAP_GENERATOR_H_
#define MAP_GENERATOR_H_

#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <limits>
#include <thread>

#include "GradientVector.h"
#include "PerlinParameters.h"
#include "BoundingBox.h"

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

    // Random map generator.
    uint8_t* GenerateMap(BoundingBox box);

    // Generates *Localized* Noise
    double GenerateLocalizedNoise(Point3D point, int octaves, double persistence, double frequency);

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

    /*
    Perlin Noise Calculation
    */
    void InitializePerlin(int repeat = -1);
    void InitializePermuntations();

    int GetPermutationAt(int index);
    int Increment(int num);

    double CalculateLocalizedNoise(PerlinParameters parameters);
    double CalculatePerlin(Point3D point);
    double Gradient(int hash, double x, double y, double z);
    double Fade(double value);
    double Lerp(double a, double b, double x);
    double NormalizeNoise(std::pair<double, double> ordinatePair, double smoothedZ);

    Point3D CorrectCoordinatesForRepetition(Point3D point);
    Point3D GetCoordinateFraction (Point3D point); 
    Point3D Smooth(Point3D point);
    Point3DInt UnitCubeCalculation(Point3D point);

    GradientVector CalculateGradientVector(Point3DInt cubeCoordinates);
    std::pair<double, double> AverageCoordinates(Point3D smoothedPoint, Point3D coordinateFraction, GradientVector vector);

    int repeat;
    int permutations[512];
    static const int PermutationLUT[256];

    RiverDirection riverDirecton;
    uint8_t* map;
    size_t width;
    size_t height;
    size_t targetLength;
    size_t initialRow;
    size_t initialColumn;
};

#endif // MAP_GENERATOR_H_