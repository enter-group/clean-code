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

typedef enum MovementDirection_t
{
    Down = 0,
    Up = 1,
    Left = 2,
    Right = 3,
    NoDirection = 4
}
MovementDirection;

void Loop(WINDOW *local_win, Snake& gameSnake, Fruit& myFruit, int& score)
{
    int currentlyPressedKey;
    MovementDirection direction = MovementDirection::NoDirection;;

    // Loop until the user presses F1
    while((currentlyPressedKey = getch()) != KEY_F(1))
	{	
        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
        
        if (gameSnake.Crash())
        {
             Renderer::s_ShowGameOver(local_win);

             if (currentlyPressedKey == KEY_F(2))
             {
                myFruit.UpdateLocation();
                gameSnake.Setup();
                score = 0;
                direction = MovementDirection::NoDirection;
             }
        }
        else
        {
            switch (currentlyPressedKey)
            {
                case KEY_DOWN:  direction = MovementDirection::Down; break;
                case KEY_UP:    direction = MovementDirection::Up; break;
                case KEY_LEFT:  direction = MovementDirection::Left; break;
                case KEY_RIGHT: direction = MovementDirection::Right; break;
            }

            if (direction != MovementDirection::NoDirection)
                gameSnake.SetD(static_cast<int>(direction));

            gameSnake.MoveMe();
            gameSnake.UpdateCrash();
            gameSnake.Yummy(myFruit, score);
        
            Renderer::s_RenderUI(gameSnake, score, local_win);
            Renderer::s_DrawSnake(gameSnake, local_win);
            Renderer::s_DrawFruit(myFruit, local_win);
        }

        // Refresh Screen
        Renderer::s_UpdateScreen(local_win);
	}
}

void InitializeAll()
{
    srand (time(NULL));
    initscr();		
	cbreak();	
    nodelay(stdscr, TRUE);		
	keypad(stdscr, TRUE);
    noecho();	
    curs_set(0);
}

void FinalizeAll()
{
    endwin();	
}

int main(int argc, char *argv[])
{	
   	
    InitializeAll();

        Fruit myFruit;
        Snake gameSnake;
        int score = 0;
        auto view_window = Renderer::s_MakeWindow();

        // Run until the user presses F1
        Loop(view_window, gameSnake, myFruit, score);
	
    FinalizeAll();
		
	return 0;
}

