#include "Renderer.h"

void Renderer::s_DrawSnake(Snake p_snake, WINDOW* p_w)
{
    for (auto i = 0; i < p_snake.Length(); i++)
        mvwaddch(p_w, p_snake.pieces[i].y + my_offY,  p_snake.pieces[i].x + my_offX, ACS_CKBOARD);
}

void Renderer::s_DrawFruit(Fruit p_fruit, WINDOW* p_w)
{
    mvwaddch(p_w, p_fruit.c1 + my_offY, p_fruit.c2 + my_offX, ACS_CKBOARD);
}

void Renderer::s_UpdateScreen(WINDOW* p_w)
{
    wrefresh(p_w);	
}

void Renderer::s_RenderUI(Snake p_snake, int p_score, WINDOW* p_w)
{
    werase(p_w);  
    box(p_w, 0, 0);	
    mvwprintw(p_w, 1, 1," Score: %d\tSize: %d", p_score, p_snake.Length());
    wmove(p_w, 2, 1);
    whline(p_w, ACS_HLINE, 78);	
    mvprintw(24, 1, "Press F1 to exit");
}

void Renderer::s_ShowGameOver(WINDOW* p_w)
{
     mvwprintw(p_w, 1, 1," GAME OVER!\t Press F2 to restart");
}

WINDOW* Renderer::s_MakeWindow()
{
    WINDOW *local_win;

	local_win = newwin(24, 80, 0, 0);
	box(local_win, 0 , 0);	
	wrefresh(local_win);	

	return local_win;
}
