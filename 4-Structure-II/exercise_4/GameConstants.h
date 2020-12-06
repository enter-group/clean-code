/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#pragma once

const int horizontalDelayInMilliseconds = 65*2;
const int verticalDelayInMilliseconds = 85*2;
const int horizontalRunningDelayInMilliseconds = 45*0.5;
const int verticalRunningDelayInMilliseconds = 85*0.5;

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