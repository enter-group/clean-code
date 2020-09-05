#include <string>
#include <curses.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <thread>

#include "Snake.h"
#include "Fruit.h"
#include "Renderer.h"
#include "Direction.h"
#include "GameConstants.h"

void RunGame(WINDOW *window, Snake& snake, Fruit& fruit, int& score)
{
    int pressedKey = 0;
    Direction direction = Direction::none;

    while((pressedKey = getch()) != KEY_F(1))
	{	
        // TODO: Use a delta time instead of sleep;
        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayInMilliseconds));
        
        if (snake.HasCollided())
        {
             Renderer::ShowGameOverScreen(window);

             if (pressedKey == KEY_F(2))
             {
                fruit.PlaceAtRandomPosition();
                snake.Reset();
                score = 0;
                direction = Direction::none;
             }
        }
        else
        {
            switch (pressedKey)
            {
                case KEY_DOWN:  direction = Direction::down; break;
                case KEY_UP:    direction = Direction::up; break;
                case KEY_LEFT:  direction = Direction::left; break;
                case KEY_RIGHT: direction = Direction::right; break;
            }

            if (direction != Direction::none)
                snake.UpdateDirection(direction);

            snake.UpdatePosition();
            snake.UpdateCollisionState();
            snake.TryToEatFruit(fruit, score);
        
            Renderer::RenderUI(snake, score, window);
            Renderer::RenderSneak(snake, window);
            Renderer::RenderFruit(fruit, window);
        }

        Renderer::RefreshScreen(window);
	}
}

void Initialize()
{
    srand(time(NULL));
    initscr();		
	cbreak();	
    nodelay(stdscr, true);		
	keypad(stdscr, true);
    noecho();	
    curs_set(0);
}

void Finalize()
{
    endwin();	
}

int main(int argc, char *argv[])
{	
    Initialize();

        Fruit fruit;
        Snake snake;
        int score = 0;
        WINDOW* window = Renderer::MakeNewWindow();

        RunGame(window, snake, fruit, score);
	
    Finalize();
		
	return 0;
}

