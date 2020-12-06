/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

#include <utility>
#include "PerlinParameters.h"
#include "GradientVector.h"

namespace LandLib
{
class Perlin
{
public:
    Perlin(int repeat = -1);

    // Calculate Normalized Perlin Noise at a 3D point with coordinates XYZ, with custom parameters
    // @param parameters: Perlin Paramters input Object.
    // @ret: Normalized Perlin Noise at position XYZ.
    double CalculateLocalizedNoise(PerlinParameters parameters);

private:
    void InitializePermuntations();
    
    int Increment(int num);

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
};
}