#ifndef MAP_H_
#define MAP_H_

#include <cstdint>

class Room
{
public:
    static const uint32_t RoomWidth;
    static const uint32_t RoomHeight;
    static const uint8_t Layout[];
};
#endif // MAP_H_
