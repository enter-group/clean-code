#ifndef PERLIN_H_
#define PERLIN_H_

#include "GradientVector.h"
#include "PerlinParameters.h"
#include "BoundingBox.h"

#include <utility>

class Perlin
{
public:
    Perlin(int repeat = -1);
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

private:
    int repeat;
    int permutations[512];
    static const int PermutationLUT[256];
};

#endif // PERLIN_H_