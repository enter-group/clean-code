/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#include <cstring>
#include <curses.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>

#include "Renderer.h"
#include "GameLogic.h"

const int backgroundColor[] = {46, 40, 255, 160, 21, 130, 231, 242, 232, 232, 232, 232, 232, 232, 232, 95, 161};
const int foregroundColor[] = {46, 40, 232, 46, 75, 130, 231, 240, 231, 248, 251, 254, 231, 231, 231, 95, 161};

void InitializeColors()
{
    for (size_t i = 0; i < 17; i++)
        init_pair(i + 1, backgroundColor[i], foregroundColor[i]);
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

