#ifndef RENDERER_H_
#define RENDERER_H_

#include <curses.h>
#include "Snake.h"
#include "Fruit.h"
#include "Segment.h"
#include "GameConstants.h"


class Renderer
{
public:
    static void RenderSneak(Snake p_snake, WINDOW* p_w);
    static void RenderFruit(Fruit p_fruit, WINDOW* p_w);
    static void RefreshScreen(WINDOW* p_w);
    static void RenderUI(Snake p_snake, int p_sc, WINDOW* p_w);
    static void ShowGameOverScreen(WINDOW* p_w);
    static WINDOW* MakeNewWindow();
};

#endif //RENDERER_H_