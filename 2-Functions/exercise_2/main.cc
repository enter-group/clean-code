#include <cstring>
#include <curses.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>

#include "Renderer.h"
#include "GameLogic.h"

void InitializeColors()
{
    init_pair(1, 46, 46);
    init_pair(2, 40, 40);
    init_pair(3, 232, 255);
    init_pair(4, 160, 46);
    init_pair(5, 21, 75);
    init_pair(6, 130, 130);
    init_pair(7, 231, 231);
    init_pair(8, 242, 240);
}

void InitializeNCurses()
{
    initscr();		
	cbreak();	
    nodelay(stdscr, true);		
	keypad(stdscr, true);
    noecho();	
    curs_set(0);
    start_color();
}

void InitializeRandom()
{
    srand(time(NULL));
}

void Initialize()
{
    InitializeRandom();
    InitializeNCurses();
    InitializeColors();
}

void Finalize()
{
    endwin();	
}

int main(int argc, char *argv[])
{	
    Initialize();
        GameLogic game;
        Renderer::MakeNewWindow();
        game.RunGame();
    Finalize();
		
	return 0;
}

