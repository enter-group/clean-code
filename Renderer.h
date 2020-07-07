#ifndef RENDERER_H_
#define RENDERER_H_

#include <curses.h>
#include "Snake.h"
#include "Fruit.h"
#include "Piece.h"

// Renderer Constants
#define my_offX 1
#define my_offY 3

// Renderer Static Class
class Renderer
{
public:
    // Draw Snake on screen
    static void s_Render1(Snake p_snake, WINDOW* p_w);

    // Draw Fruit on Screen
    static void s_Render3(Fruit p_fruit, WINDOW* p_w);

    // Update UI
    static void s_Render4(WINDOW* p_w);
    
    // Refresh Screen
    static void s_RndrAll(Snake p_snake, int p_sc, WINDOW* p_w);

    // Game Over Screen
    static void s_RenderText(WINDOW* p_w);

    // Window rendering
    static WINDOW* s_MakeNew();
};

#endif //RENDERER_H_