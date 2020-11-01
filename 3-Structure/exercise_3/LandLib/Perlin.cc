#include "Perlin.h"

Perlin::Perlin(int repeat)
{
    this->repeat = repeat;
    InitializePermuntations();
}

double Perlin::CalculateLocalizedNoise(PerlinParameters parameters)
{
    double total = 0;
    double amplitude = 1;
    double maxValue = 0;

    for(int i = 0;i < parameters.octaves; i++) 
    {
        Point3D point = {parameters.point.x * parameters.frequency, parameters.point.y * parameters.frequency, parameters.point.z * parameters.frequency};
        total += CalculatePerlin(point) * amplitude;    
        maxValue += amplitude;
        amplitude *= parameters.persistence;
        parameters.frequency *= 2;
    }

    return total/maxValue;
}

int Perlin::GetPermutationAt(int index)
{
    // Wraps around 512 to avoid segmentation fault.
    return permutations[index%512];
}

void Perlin::InitializePermuntations()
{
    for (auto i = 0; i < 512; i++)
        permutations[i] = PermutationLUT[i%256];
}

double Perlin::CalculatePerlin(Point3D point) 
{
    CorrectCoordinatesForRepetition(point);
    Point3D coordinateFraction = GetCoordinateFraction(point);
    Point3D smoothedPoint = Smooth(coordinateFraction);
    GradientVector vector = CalculateGradientVector(UnitCubeCalculation(point));
    auto averagedCoordintates = AverageCoordinates(smoothedPoint, coordinateFraction, vector);
    
    return NormalizeNoise(averagedCoordintates, smoothedPoint.z);
}

Point3D Perlin::CorrectCoordinatesForRepetition(Point3D point)
{
    if(repeat > 0) 
    {									
        point.x = (int)point.x%repeat;
        point.y = (int)point.y%repeat;
        point.z = (int)point.z%repeat;
    }

    return point;
}

Point3D Perlin::GetCoordinateFraction (Point3D point)
{
    Point3D fraction;
    fraction.x = point.x - (int)point.x;
    fraction.y = point.y - (int)point.y;
    fraction.z = point.z - (int)point.z;

    return fraction;
}

Point3DInt Perlin::UnitCubeCalculation(Point3D point)
{
    Point3DInt correctedCoordinates;
    correctedCoordinates.x = (int)point.x & 255;
    correctedCoordinates.y = (int)point.y & 255;
    correctedCoordinates.z = (int)point.z & 255;

    return correctedCoordinates;
}

Point3D Perlin::Smooth(Point3D point)
{
    Point3D smoothed;
    smoothed.x = Fade(point.x);
    smoothed.y = Fade(point.y);
    smoothed.z = Fade(point.z);

    return smoothed;
}

GradientVector Perlin::CalculateGradientVector(Point3DInt cubeCoordinates)
{
    GradientVector vector;
    vector.aaa = permutations[permutations[permutations[cubeCoordinates.x] + cubeCoordinates.y] + cubeCoordinates.z];
    vector.aba = permutations[permutations[permutations[cubeCoordinates.x] + Increment(cubeCoordinates.y)] + cubeCoordinates.z];
    vector.aab = permutations[permutations[permutations[cubeCoordinates.x] + cubeCoordinates.y] + Increment(cubeCoordinates.z)];
    vector.abb = permutations[permutations[permutations[cubeCoordinates.x] + Increment(cubeCoordinates.y)] + Increment(cubeCoordinates.z)];
    vector.baa = permutations[permutations[permutations[Increment(cubeCoordinates.x)] + cubeCoordinates.y] + cubeCoordinates.z];
    vector.bba = permutations[permutations[permutations[Increment(cubeCoordinates.x)] + Increment(cubeCoordinates.y)] + cubeCoordinates.z];
    vector.bab = permutations[permutations[permutations[Increment(cubeCoordinates.x)] + cubeCoordinates.y] + Increment(cubeCoordinates.z)];
    vector.bbb = permutations[permutations[permutations[Increment(cubeCoordinates.x)] + Increment(cubeCoordinates.y)] + Increment(cubeCoordinates.z)];

    return vector;
}

std::pair<double, double> Perlin::AverageCoordinates(Point3D smoothedPoint, Point3D coordinateFraction, GradientVector vector)
{
    double x1, x2, y1, y2;
    x1 = Lerp(Gradient(vector.aaa, coordinateFraction.x, coordinateFraction.y, coordinateFraction.z), Gradient(vector.baa, coordinateFraction.x - 1, coordinateFraction.y, coordinateFraction.z), smoothedPoint.x);	
    x2 = Lerp(Gradient(vector.aba, coordinateFraction.x, coordinateFraction.y - 1, coordinateFraction.z), Gradient(vector.bba, coordinateFraction.x - 1, coordinateFraction.y-1, coordinateFraction.z), smoothedPoint.x);
    y1 = Lerp(x1, x2, smoothedPoint.y);
    x1 = Lerp(Gradient(vector.aab, coordinateFraction.x, coordinateFraction.y, coordinateFraction.z - 1), Gradient(vector.bab, coordinateFraction.x - 1, coordinateFraction.y, coordinateFraction.z - 1), smoothedPoint.x);
    x2 = Lerp(Gradient(vector.abb, coordinateFraction.x, coordinateFraction.y - 1, coordinateFraction.z - 1), Gradient(vector.bbb, coordinateFraction.x - 1, coordinateFraction.y - 1, coordinateFraction.z - 1), smoothedPoint.x);
    y2 = Lerp (x1, x2, smoothedPoint.y);

    return std::make_pair(y1, y2);
}

double Perlin::NormalizeNoise(std::pair<double, double> ordinatePair, double smoothedZ)
{
    return (Lerp(ordinatePair.first, ordinatePair.second, smoothedZ) + 1)/2;
}

int Perlin::Increment(int num) 
{
    num++;
    if (repeat > 0) num %= repeat;
    
    return num;
}

double Perlin::Gradient(int hash, double x, double y, double z)
{
    int h = hash & 15;		
    double v;							
    double u = h < 8 ? x : y;	
    
    if(h < 4)						
        v = y;
    else if(h == 12 || h == 14)
        v = x;
    else
        v = z;
    
    return ((h&1) == 0 ? u : -u)+((h&2) == 0 ? v : -v);
}

double Perlin::Fade(double value)
{
		return value * value * value * (value * (value * 6 - 15) + 10);
}

double Perlin::Lerp(double a, double b, double x) 
{
	return a + x * (b - a);
}

const int Perlin::PermutationLUT[] = 
{ 
    151, 160, 137,  91,  90,  15, 190,   6, 148, 247, 120,
    234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,
     35,  11,  32,  57, 177,  33,  88, 237, 149,  56,  87,
    174,  20, 125, 136, 171, 168,  68, 175,  74, 165,  71,
    134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111,
    229, 122,  60, 211, 133, 230, 220, 105,  92,  41,  55,
     46, 245,  40, 244,	102, 143,  54,  65,  25,  63,  61,
      1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18,
    169, 200, 196, 135, 130, 116, 188, 159,  86, 164, 100,
    109, 198, 173, 186,   3,  64,  52, 217, 226, 250, 124,
    123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
    207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,
     42, 223, 183, 170, 213, 119, 248, 152,   2,  44, 154,
    163,  70, 221, 153, 101, 155, 167,  43, 172,   9, 129,
     22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232,
    178, 185, 112, 104, 218, 246,  97, 228,	251,  34, 242,
    193, 238, 210, 144,  12, 191, 179, 162, 241,  81,  51,
    145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181,
    199, 106, 157, 184,  84, 204, 176, 115, 121,  50,  45,
    127,   4, 150, 254,	138, 236, 205,  93, 222, 114,  67,
     29,   24,  72, 243, 141, 128, 195,  78,  66, 215,  61,
    156, 180, 151, 160, 137,  91,  90,  15, 190,   6, 148,
    234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,
     35,  11,  32, 
};