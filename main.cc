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

typedef enum MoveD_t
{
    d1 = 0,
    d2 = 1,
    d3 = 2,
    d4 = 3,
    noD = 4
}
MoveD;

void Loop(WINDOW *local_win, Snake& s, Fruit& f, int& sc)
{
    auto currentlyPressedKey = 0;
    auto dir = MoveD::noD;;

    // Loop until the user presses F1
    while((currentlyPressedKey = getch()) != KEY_F(1))
	{	
        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
        
        if (s.Crash())
        {
             Renderer::s_RenderText(local_win);

             if (currentlyPressedKey == KEY_F(2))
             {
                f.Drop();
                s.Setup();
                sc = 0;
                dir = MoveD::noD;
             }
        }
        else
        {
            switch (currentlyPressedKey)
            {
                case KEY_DOWN:  dir = MoveD::d1; break;
                case KEY_UP:    dir = MoveD::d2; break;
                case KEY_LEFT:  dir = MoveD::d3; break;
                case KEY_RIGHT: dir = MoveD::d4; break;
            }

            if (dir != MoveD::noD)
                s.SetD(static_cast<int>(dir));

            s.MoveMe();
            s.UpdateCrash();
            s.Yummy(f, sc);
        
            Renderer::s_RndrAll(s, sc, local_win);
            Renderer::s_Render1(s, local_win);
            Renderer::s_Render3(f, local_win);
        }

        // Refresh Screen
        Renderer::s_Render4(local_win);
	}
}

void InitializeAll()
{
    srand (time(NULL));
    initscr();		
	cbreak();	
    nodelay(stdscr, true);		
	keypad(stdscr, true);
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

        Fruit f;
        Snake s;
        int sc = 0;
        auto w = Renderer::s_MakeNew();

        // Run until the user presses F1
        Loop(w, s, f, sc);
	
    FinalizeAll();
		
	return 0;
}

