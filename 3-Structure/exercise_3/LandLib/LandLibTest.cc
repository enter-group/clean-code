#include <cstring>
#include <curses.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <limits>
#include <thread>
#include "Perlin.h"
#include "MapGenerator.h"
#include "Point3D.h"

const int demoWindowHeight = 40;
const int demoWindowWidth = 92;

int main (int argc, char *argv[])
{
    initscr();		
	cbreak();	
    nodelay(stdscr, true);		
	keypad(stdscr, true);
    noecho();	
    curs_set(0);
    start_color();

    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    init_color(1, 1000, 1000, 1000);
    init_color(0, 0, 0, 0);

    init_pair(2, 232, 255);
    init_pair(3, 46, 46);
    init_pair(4, 40, 40);
    init_pair(5, 130, 130);
    init_pair(8, 242, 240);

    init_pair(12, 21, 75);

    init_pair(13, 232, 231);
    init_pair(14, 232, 248);
    init_pair(15, 232, 251);
    init_pair(16, 232, 254);
    init_pair(17, 232, 231);

    WINDOW* window;

    window = newwin(demoWindowHeight + 2, demoWindowWidth, 1, 1);
	box(window, 0 , 0);
	wrefresh(window);

    wattron(window, COLOR_PAIR(0));


    werase(window);
    box(window, 0, 0);
    wmove(window, 2, 1);
    whline(window, ACS_HLINE, demoWindowWidth - 2);

    mvwprintw(window, 1, 1," Random Map Generation Demo");
    Perlin perlin;

    int key;
    bool firstTime = true;
    while((key = getch()) != KEY_F(2)) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(70));

        if (firstTime || key == KEY_F(3))
        {
            firstTime = false;
            MapGenerator generator;
            uint8_t*map = generator.GenerateMap((demoWindowWidth - 2), (demoWindowHeight - 2));

            for (int i = 0; i < (demoWindowHeight - 2); i++)
            {
                for (int j = 0; j < (demoWindowWidth - 2); j++)
                {
                    if (map[i*(demoWindowWidth - 2) + j] == static_cast<uint8_t>(TerrainType::Ground))
                    {
                        if ((i*(demoWindowWidth - 2) + j)%4 < 2)
                        {
                            wattron(window, COLOR_PAIR(3));
                            mvwprintw(window, 3 + i, 1 + j," ");
                            wattroff(window, COLOR_PAIR(3));
                        }
                        else
                        {
                            wattron(window, COLOR_PAIR(4));
                            mvwprintw(window, 3 + i, 1 + j," ");
                            wattroff(window, COLOR_PAIR(4));
                        }
                    }
                    else if (map[i*(demoWindowWidth - 2) + j] >= static_cast<uint8_t>(TerrainType::MountainLv1) && map[i*(demoWindowWidth - 2) + j] <= static_cast<uint8_t>(TerrainType::MountainLv6))
                    {
                        wattron(window, COLOR_PAIR(11 + map[i*(demoWindowWidth - 2) + j]));
                        mvwprintw(window, 3 + i, 1 + j," ");
                        wattroff(window,  COLOR_PAIR(11 + map[i*(demoWindowWidth - 2) + j]));
                    }
                    else if (map[i*(demoWindowWidth - 2) + j] == static_cast<uint8_t>(TerrainType::Bridge))
                    {
                        wattron(window, COLOR_PAIR(5));
                        mvwprintw(window, 3 + i, 1 + j," ");
                        wattroff(window, COLOR_PAIR(5));
                    }
                    else if (map[i*(demoWindowWidth - 2) + j] == static_cast<uint8_t>(TerrainType::Wall))
                    {
                        wattron(window, COLOR_PAIR(8));
                        mvwprintw(window, 3 + i, 1 + j," ");
                        wattroff(window, COLOR_PAIR(8));
                    }
                    else
                    {
                        wattron(window, COLOR_PAIR(12));
                        mvwprintw(window, 3 + i, 1 + j," ");
                        wattroff(window, COLOR_PAIR(12));
                    }
                }
            }

            delete map;
        }

        wrefresh(window);
        refresh();

    }

    endwin();	
}