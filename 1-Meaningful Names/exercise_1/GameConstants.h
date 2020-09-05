#ifndef GAME_CONSTANTS_H_
#define GAME_CONSTANTS_H_

const int frameDelayInMilliseconds = 75;

const int viewportHorizontalOffset = 1;
const int viewportVerticalOffset = 3;
const int windowWidth = 80;
const int windowHeight = 24;

const int initialBodyLength = 4;
const int intiialBodyYPosition = 1;
const int eatenFruitScoreIncrement = 10;

constexpr int playfieldWidth = windowWidth - viewportHorizontalOffset - 1;
constexpr int playfieldHeight = windowHeight - viewportVerticalOffset - 1;

#endif // GAME_CONSTANTS_H_