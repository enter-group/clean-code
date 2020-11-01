#include "MapGenerator.h"

uint8_t* MapGenerator::AllocateMap()
{
    uint8_t* map = new uint8_t[width*height];
    return map;
}

uint8_t* MapGenerator::GenerateMap(size_t width, size_t height)
{
    this->width = width;
    this->height = height;
    this->map = AllocateMap();
    riverDirecton = RiverDirection::NoDirection;

    GenerateBaseTopology();
    GenerateRiver();
    ClearRiverSurroundings();
    GenerateBridge();
    GenerateWall();
    
    return this->map;
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

size_t MapGenerator::GetRandomBridgeRow()
{
    return rand()%static_cast<int>(height*0.4) + static_cast<int>(height*0.3);
}

size_t MapGenerator::FindInitialRiverColumn()
{
    for (size_t i = 0; i < width; i++)
        if (map[SafeIndex(initialRow, i)] == static_cast<uint8_t>(TerrainType::River))
            return i;

    return 0;
}

size_t MapGenerator::FindInitialRiverRow()
{
    for (size_t i = 0; i < height; i++)
        if (map[SafeIndex(i, initialColumn)] == static_cast<uint8_t>(TerrainType::River))
            return i;

    return 0;
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

void MapGenerator::ExpandHorizontalBridge()
{
    for (int i = -2; i != 2; i++)
        for (size_t j = initialColumn; j < initialColumn + targetLength; j++)
            map[SafeIndex(initialRow + i, j)] = static_cast<uint8_t>(TerrainType::Bridge);
}

void MapGenerator::ExpandVerticalBridge()
{
    for (int i = -4; i != 4; i++)
        for (size_t j = initialRow; j < initialRow + targetLength; j++)
            map[SafeIndex(j, initialColumn + i)] = static_cast<uint8_t>(TerrainType::Bridge);
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

void MapGenerator::GenerateHorizontalRiver()
{
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

void MapGenerator::GenerateVerticalRiver()
{
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

void MapGenerator::GenerateBaseTopology()
{
    const int peakRange = 10;
    double amplitude  = peakRange/(rand()%peakRange + 1);
    double freq = rand()%4 + rand()%10 + 5;
    double offsetX = width*0.8/(rand()%(static_cast<int>(width*0.8)) + 1);
    double offsetY = height*0.8/(rand()%(static_cast<int>(height*0.8)) + 1);

    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
        {
            PerlinParameters parameters{{static_cast<double>(j)/static_cast<double>(width) + offsetX, static_cast<double>(i+1)/static_cast<double>(height) + offsetY, amplitude*0.9}, 1, peakRange, freq};
            int topology = peakRange*perlin.CalculateLocalizedNoise(parameters);
            map[i*width + j] = topology > 5 ? static_cast<uint8_t>(TerrainType::MountainLv1) + (topology - 5) : static_cast<uint8_t>(TerrainType::Ground);
        }
}

size_t MapGenerator::SafeIndex(size_t row, size_t col)
{
    return std::min(static_cast<size_t>(width*height - 1), std::max(static_cast<size_t>(0), static_cast<size_t>((row)*width + (col))));
}