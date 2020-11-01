#include "MapGenerator.h"

uint8_t* MapGenerator::AllocateMap()
{
    // *Statically* allocates the map's 2D Matrix
    uint8_t* map = new uint8_t[width*height];
    return map;
}

void MapGenerator::GenerateBaseTopology()
{
    // Main Function:
    // it uses Perlin Noise to generate the base topology of the map, given the requested dimensions.
    const int peakRange = 10;

    // Randomized noise-peaks amplitude, sinusoidal frequency and noise-plane offset, to give the topology more variety
    double amplitude  = peakRange/(rand()%peakRange + 1);
    double freq = rand()%4 + rand()%10 + 5;
    double offsetX = width*0.8/(rand()%(static_cast<int>(width*0.8)) + 1);
    double offsetY = height*0.8/(rand()%(static_cast<int>(height*0.8)) + 1);

    // Calculate Perlin noise for *every single* point in the map's plane.
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
        {
            PerlinParameters parameters{{static_cast<double>(j)/static_cast<double>(width) + offsetX, static_cast<double>(i+1)/static_cast<double>(height) + offsetY, amplitude*0.9}, 1, peakRange, freq};
            int topology = peakRange*CalculateLocalizedNoise(parameters);
            map[i*width + j] = topology > 5 ? static_cast<uint8_t>(TerrainType::MountainLv1) + (topology - 5) : static_cast<uint8_t>(TerrainType::Ground);
        }
}

double MapGenerator::GenerateLocalizedNoise(Point3D point, int octaves, double persistence, double frequency)
{
    PerlinParameters parameters{point, octaves, persistence, frequency};
    return CalculateLocalizedNoise(parameters);
}

size_t MapGenerator::GetRandomBridgeRow()
{
    return rand()%static_cast<int>(height*0.4) + static_cast<int>(height*0.3);
}

void MapGenerator::GenerateWall()
{
    for (size_t i = 0; i < width; i++)
    {
       map[SafeIndex(0, i)] = static_cast<uint8_t>(TerrainType::Wall);
       map[SafeIndex(height - 1, i)] = static_cast<uint8_t>(TerrainType::Wall);
    }

    for (size_t i = 0; i < height; i++)
    {
       map[SafeIndex(i, 0)] = static_cast<uint8_t>(TerrainType::Wall);
       map[SafeIndex(i, width - 1)] = static_cast<uint8_t>(TerrainType::Wall);
    }
}

size_t MapGenerator::GetRandomBridgeColumn()
{
    return rand()%static_cast<int>(width*0.4) + static_cast<int>(width*0.3);
}



size_t MapGenerator::CalculateBridgeWidth()
{
    for (size_t i = initialColumn; i < width; i++)
    {
        if (map[SafeIndex(initialRow, i)] != static_cast<uint8_t>(TerrainType::River))
            return i - initialColumn;

        map[SafeIndex(initialRow, i)] = static_cast<uint8_t>(TerrainType::Bridge);
    }

    return 0;
}

size_t MapGenerator::CalculateBridgeHeight()
{
     for (size_t i = initialRow; i < width; i++)
    {
        if (map[SafeIndex(i, initialColumn)] != static_cast<uint8_t>(TerrainType::River))
            return i - initialRow;
            
        map[SafeIndex(i, initialColumn)] = static_cast<uint8_t>(TerrainType::Bridge);
    }

    return 0;
}


size_t MapGenerator::FindInitialRiverColumn()
{
    for (size_t i = 0; i < width; i++)
        if (map[SafeIndex(initialRow, i)] == static_cast<uint8_t>(TerrainType::River))
            return i;

    return 0;
}


void MapGenerator::FillVerticalBridge(size_t minRow, size_t maxRow)
{
    for (size_t i = initialColumn - 4; i != initialColumn + 4; i++)
    {
        if (minRow != std::numeric_limits<size_t>::max())
            for (size_t j = minRow; j != initialRow; j++)
                map[SafeIndex(j, i)] = static_cast<uint8_t>(TerrainType::Bridge);

        if (maxRow != std::numeric_limits<size_t>::min())
            for (size_t j = maxRow; j != initialRow + targetLength - 1; j--)
                map[SafeIndex(j, i)] = static_cast<uint8_t>(TerrainType::Bridge);
    }
}

void MapGenerator::ExpandHorizontalBridge()
{
    for (int i = -2; i != 2; i++)
        for (size_t j = initialColumn; j < initialColumn + targetLength; j++)
            map[SafeIndex(initialRow + i, j)] = static_cast<uint8_t>(TerrainType::Bridge);
}


size_t MapGenerator::FindBirdgeMinColumn()
{
    size_t minColumn = std::numeric_limits<size_t>::max();
    for (size_t i = initialRow - 2; i != initialRow + 2; i++)
        for (size_t j = initialColumn - 1; j >= 0; j--)
            if (map[SafeIndex(i, j)] == static_cast<uint8_t>(TerrainType::River))
                minColumn = std::min(minColumn, j);
            else
                break;

    return minColumn;
}

size_t MapGenerator::FindBirdgeMaxColumn()
{
    size_t maxColumn = std::numeric_limits<size_t>::min();
    for (size_t i = initialRow - 2; i != initialRow + 2; i++)
        for (size_t j = initialColumn + targetLength; j < width; j++)
            if (map[SafeIndex(i, j)] == static_cast<uint8_t>(TerrainType::River))
                maxColumn = std::max(maxColumn, j);
            else
                break;

    return maxColumn;
}

size_t MapGenerator::FindInitialRiverRow()
{
    for (size_t i = 0; i < height; i++)
        if (map[SafeIndex(i, initialColumn)] == static_cast<uint8_t>(TerrainType::River))
            return i;

    return 0;
}


size_t MapGenerator::FindBirdgeMinRow()
{
    size_t minRow = std::numeric_limits<size_t>::max();
    for (size_t i = initialColumn - 4; i != initialColumn + 4; i++)
        for (size_t j = initialRow - 1; j >= 0; j--)
            if (map[SafeIndex(j, i)] == static_cast<uint8_t>(TerrainType::River))
                minRow = std::min(minRow, j);
            else
                break;

    return minRow;
}

size_t MapGenerator::FindBirdgeMaxRow()
{
    size_t maxRow = std::numeric_limits<size_t>::min();
    for (size_t i = initialColumn - 4; i != initialColumn + 4; i++)
        for (size_t j = initialRow + targetLength; j < height; j++)
            if (map[SafeIndex(j, i)] == static_cast<uint8_t>(TerrainType::River))
                maxRow = std::max(maxRow, j);
            else
                break;

    return maxRow;
}

uint8_t* MapGenerator::GenerateMap(BoundingBox box)
{
    InitializePerlin();
    this->width = box.bottomRightX - box.topLeftX;
    this->height = box.bottomRightY - box.topLeftY;
    this->map = AllocateMap();
    riverDirecton = RiverDirection::NoDirection;

    GenerateBaseTopology();
    GenerateRiver();
    ClearRiverSurroundings();
    GenerateBridge();
    GenerateWall();
    
    return this->map;
}

void MapGenerator::ExpandVerticalBridge()
{
    for (int i = -4; i != 4; i++)
        for (size_t j = initialRow; j < initialRow + targetLength; j++)
            map[SafeIndex(j, initialColumn + i)] = static_cast<uint8_t>(TerrainType::Bridge);
}


void MapGenerator::ClearRiverSurroundings()
{
    // This function looks for all river tiles (around the edges of a river) and creates ground tiles, smoothing the sharp edges.
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
            if (map[i*width + j] == static_cast<uint8_t>(TerrainType::River))
                for (int k = -8; k < 8; k++)
                    for (int l = -8; l < 8; l++)
                        if (map[SafeIndex(i + k, j + l)] != static_cast<uint8_t>(TerrainType::River))
                            map[SafeIndex(i + k, j + l)] = static_cast<uint8_t>(TerrainType::Ground);
}

void MapGenerator::FillHorizontalBridge(size_t minColumn, size_t maxColumn)
{
    for (size_t i = initialRow - 2; i != initialRow + 2; i++)
    {
        if (minColumn != std::numeric_limits<size_t>::max())
            for (size_t j = minColumn; j != initialColumn; j++)
                map[SafeIndex(i, j)] = static_cast<uint8_t>(TerrainType::Bridge);

        if (maxColumn != std::numeric_limits<size_t>::min())
            for (size_t j = maxColumn; j != initialColumn + targetLength - 1; j--)
                map[SafeIndex(i, j)] = static_cast<uint8_t>(TerrainType::Bridge);
    }
}

void MapGenerator::GenerateVerticalRiver()
{
    // Sorry for the long function. It is just very hard to split this up ;)
    size_t initialPosition = 0;
    size_t index = rand()%static_cast<int>((width*0.4)) + static_cast<int>(width*0.3);
    initialPosition = index;
    map[index] = 3;

    riverDirecton = RiverDirection::Vertical;

    int previousLength = 5;
    for (size_t i = 0; i < height; i++)
    {
        size_t length = previousLength;
        int direction = rand()%2 == 0? 1 : -1;
        int offset = rand()%2 == 0? 1 : -1;
        size_t k = 0;

        offset *= (rand()%3) + 1;

        for (; k< static_cast<size_t>(rand()%3 + 1); k++)     
            for (size_t j = -length; j != length; j++)
                if ((i + k)*width + initialPosition + offset + direction + j >= (i + k)*width && 
                    (i + k)*width + initialPosition + offset + direction + j < (i + k + 1)*width)
                    map[(i + k)*width + initialPosition + offset + direction + j] = static_cast<uint8_t>(TerrainType::River);

        i +=k - 1;
        initialPosition += direction + offset;
        previousLength += rand()%2 == 0? 1 : -1;
        previousLength = std::max(3, std::min(8, previousLength));
    }
}

void MapGenerator::GenerateHorizontalBridge()
{
    initialRow = GetRandomBridgeRow();
    initialColumn = FindInitialRiverColumn();
    targetLength = CalculateBridgeWidth();
    size_t minColumn = std::numeric_limits<size_t>::max();
    size_t maxColumn = std::numeric_limits<size_t>::min();

    ExpandHorizontalBridge();
    minColumn = FindBirdgeMinColumn();
    maxColumn = FindBirdgeMaxColumn();
    FillHorizontalBridge(minColumn, maxColumn);
}

void MapGenerator::GenerateVerticalBridge()
{
    initialColumn = GetRandomBridgeColumn();
    initialRow = FindInitialRiverRow();
    targetLength = CalculateBridgeHeight();
    size_t minRow = std::numeric_limits<size_t>::max();
    size_t maxRow = std::numeric_limits<size_t>::min();

    ExpandVerticalBridge();
    minRow = FindBirdgeMinRow();
    maxRow = FindBirdgeMaxRow();
    FillVerticalBridge(minRow, maxRow);
}

void MapGenerator::GenerateBridge()
{
    if (riverDirecton == RiverDirection::Vertical)
        GenerateHorizontalBridge();
    else if (riverDirecton == RiverDirection::Horizonal)
        GenerateVerticalBridge();
}

void MapGenerator::GenerateHorizontalRiver()
{
    // Sorry for the long function. It is just very hard to split this up ;)
    size_t initialPosition = 0;
    size_t index = rand()%static_cast<int>(height*0.4) + static_cast<int>(height*0.3);
    initialPosition = index;

    int previousLength = 3;
    for (size_t i = 0; i < width; i++)
    {
        size_t length = previousLength;
        int direction = rand()%20;
        size_t tempPreviousLength = rand()%20;

        riverDirecton = RiverDirection::Horizonal;
        direction = direction == 0? -1 : (direction == 1? 1 : 0); 

        for (int j = -length; j != static_cast<int>(length); j++)
            map[SafeIndex(initialPosition + j, i)] = static_cast<uint8_t>(TerrainType::River);

        initialPosition += direction;
        previousLength = std::min(2, std::max(4, tempPreviousLength == 0? previousLength-1 : (tempPreviousLength == 1? previousLength+1 : previousLength))); 
    }
}

void MapGenerator::GenerateRiver()
{
    auto numberRivers = rand()%2;
            
    if (numberRivers > 0)
    {
        if (rand()%2 == 0)
            GenerateVerticalRiver();
        else
            GenerateHorizontalRiver();

    }
}

size_t MapGenerator::SafeIndex(size_t row, size_t col)
{
    return std::min(static_cast<size_t>(width*height - 1), std::max(static_cast<size_t>(0), static_cast<size_t>((row)*width + (col))));
}

/************
 * Perlin Noise Calculation
 * **********/

void MapGenerator::InitializePerlin(int repeat)
{
    this->repeat = repeat;
    InitializePermuntations();
}

double MapGenerator::CalculateLocalizedNoise(PerlinParameters parameters)
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

int MapGenerator::GetPermutationAt(int index)
{
    // Wraps around 512 to avoid segmentation fault.
    return permutations[index%512];
}

void MapGenerator::InitializePermuntations()
{
    for (auto i = 0; i < 512; i++)
        permutations[i] = PermutationLUT[i%256];
}

double MapGenerator::CalculatePerlin(Point3D point) 
{
    CorrectCoordinatesForRepetition(point);
    Point3D coordinateFraction = GetCoordinateFraction(point);
    Point3D smoothedPoint = Smooth(coordinateFraction);
    GradientVector vector = CalculateGradientVector(UnitCubeCalculation(point));
    auto averagedCoordintates = AverageCoordinates(smoothedPoint, coordinateFraction, vector);
    
    return NormalizeNoise(averagedCoordintates, smoothedPoint.z);
}

Point3D MapGenerator::CorrectCoordinatesForRepetition(Point3D point)
{
    if(repeat > 0) 
    {									
        point.x = (int)point.x%repeat;
        point.y = (int)point.y%repeat;
        point.z = (int)point.z%repeat;
    }

    return point;
}

Point3D MapGenerator::GetCoordinateFraction (Point3D point)
{
    Point3D fraction;
    fraction.x = point.x - (int)point.x;
    fraction.y = point.y - (int)point.y;
    fraction.z = point.z - (int)point.z;

    return fraction;
}

Point3DInt MapGenerator::UnitCubeCalculation(Point3D point)
{
    Point3DInt correctedCoordinates;
    correctedCoordinates.x = (int)point.x & 255;
    correctedCoordinates.y = (int)point.y & 255;
    correctedCoordinates.z = (int)point.z & 255;

    return correctedCoordinates;
}

Point3D MapGenerator::Smooth(Point3D point)
{
    Point3D smoothed;
    smoothed.x = Fade(point.x);
    smoothed.y = Fade(point.y);
    smoothed.z = Fade(point.z);

    return smoothed;
}

GradientVector MapGenerator::CalculateGradientVector(Point3DInt cubeCoordinates)
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

std::pair<double, double> MapGenerator::AverageCoordinates(Point3D smoothedPoint, Point3D coordinateFraction, GradientVector vector)
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

double MapGenerator::NormalizeNoise(std::pair<double, double> ordinatePair, double smoothedZ)
{
    return (Lerp(ordinatePair.first, ordinatePair.second, smoothedZ) + 1)/2;
}

int MapGenerator::Increment(int num) 
{
    num++;
    if (repeat > 0) num %= repeat;
    
    return num;
}

double MapGenerator::Gradient(int hash, double x, double y, double z)
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

double MapGenerator::Fade(double value)
{
		return value * value * value * (value * (value * 6 - 15) + 10);
}

double MapGenerator::Lerp(double a, double b, double x) 
{
	return a + x * (b - a);
}

const int MapGenerator::PermutationLUT[] = 
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