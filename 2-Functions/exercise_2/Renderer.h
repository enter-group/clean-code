#ifndef RENDERER_H_
#define RENDERER_H_

#include <curses.h>
#include "Snake.h"
#include "FruitFactory.h"
#include "Segment.h"
#include "Position.h"
#include "GameConstants.h"
#include "Stage.h"
class Renderer
{
public:
    static void Render (Stage& stage, Snake& snake, WINDOW* window, int score, bool isGameOver);
    static WINDOW* MakeNewWindow();
};

#endif //RENDERER_H_