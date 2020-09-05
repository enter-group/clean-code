#include "Renderer.h"

void Renderer::RenderSneak(Snake snake, WINDOW* window)
{
    for (auto i = 0; i < snake.Length(); i++)
        mvwaddch(window, snake.snakeSize[i].y + viewportVerticalOffset,  
                         snake.snakeSize[i].x + viewportHorizontalOffset, ACS_CKBOARD);
}

void Renderer::RenderFruit(Fruit fruit, WINDOW* window)
{
    mvwaddch(window, fruit.y + viewportVerticalOffset, 
                     fruit.x + viewportHorizontalOffset, ACS_DIAMOND);
}

void Renderer::RefreshScreen(WINDOW* window)
{
    wrefresh(window);	
}

void Renderer::RenderUI(Snake snake, int score, WINDOW* window)
{
    werase(window);  
    box(window, 0, 0);	
    mvwprintw(window, 1, 1," Score: %d\tSize: %d", score, snake.Length());
    wmove(window, 2, 1);
    whline(window, ACS_HLINE, windowWidth - 2);	
    mvprintw(windowHeight, 1, "Press F1 to exit");
}

void Renderer::ShowGameOverScreen(WINDOW* window)
{
     mvwprintw(window, 1, 1," GAME OVER!\t Press F2 to restart");
}

WINDOW* Renderer::MakeNewWindow()
{
    WINDOW *window;

	window = newwin(windowHeight, windowWidth, 0, 0);
	box(window, 0 , 0);	
	wrefresh(window);	

	return window;
}
