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
    static void s_DrawSnake(Snake p_snake, WINDOW* p_w);

    // Draw Fruit on Screen
    static void s_DrawFruit(Fruit p_fruit, WINDOW* p_w);

    // Update UI
    static void s_UpdateScreen(WINDOW* p_w);
    
    // Refresh Screen
    static void s_RenderUI(Snake p_snake, int p_score, WINDOW* p_w);

    // Game Over Screen
    static void s_ShowGameOver(WINDOW* p_w);

    static WINDOW* s_MakeWindow();
};

#endif //RENDERER_H_