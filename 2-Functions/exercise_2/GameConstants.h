#ifndef GAME_CONSTANTS_H_
#define GAME_CONSTANTS_H_

const int frameDelayInMilliseconds = 65;
const int frameDelayInMilliseconds2 = 85;

const int viewportHorizontalOffset = 1;
const int viewportVerticalOffset = 3;
const int windowWidth = 80;
const int windowHeight = 24;

const int initialBodyLength = 4;
const int initialBodyYPosition = 1;
const int eatenFruitScoreIncrement = 10;

constexpr int playfieldWidth = windowWidth - viewportHorizontalOffset - 1;
constexpr int playfieldHeight = windowHeight - viewportVerticalOffset - 1;

#endif // GAME_CONSTANTS_H_