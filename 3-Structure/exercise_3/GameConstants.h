#ifndef GAME_CONSTANTS_H_
#define GAME_CONSTANTS_H_

const int horizontalDelayInMilliseconds = 65;
const int verticalDelayInMilliseconds = 85;

const int viewportHorizontalOffset = 1;
const int viewportVerticalOffset = 3;
const int windowWidth = 80;
const int windowHeight = 30;

const int initialBodyLength = 4;
const int initialBodyYPosition = 1;
const int eatenFruitScoreIncrement = 10;

const size_t minStageWidth = 120;
const size_t minStageHeight = 60;
const size_t maxStageWidth = 160;
const size_t maxStageHeight = 100;

constexpr int playfieldWidth = windowWidth - viewportHorizontalOffset - 1;
constexpr int playfieldHeight = windowHeight - viewportVerticalOffset - 1;

#endif // GAME_CONSTANTS_H_