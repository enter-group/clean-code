#include <string>
#include <curses.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <thread>

#include "Snake.h"
#include "FruitFactory.h"
#include "Renderer.h"
#include "Direction.h"
#include "GameConstants.h"
#include "Room.h"
#include "Stage.h"

void RunGame(WINDOW *window, Snake& snake, FruitFactory& fruitFactory, Stage& stage, int& score)
{
    int pressedKey = 0;
    Direction direction = Direction::none;

    while((pressedKey = getch()) != KEY_F(1))
	{	
        if (snake.GetDirection() == Direction::left || snake.GetDirection() == Direction::right)
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayInMilliseconds));
        else  if (snake.GetDirection() == Direction::up || snake.GetDirection() == Direction::down)
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayInMilliseconds2));
        
        if (snake.HasCollided())
        {
            Renderer::Render(stage, snake, window, score, true);

            if (pressedKey == KEY_F(2))
            {
                snake.Reset();
                stage.Reset(Room::Layout, Room::RoomWidth, Room::RoomHeight);
                fruitFactory.CreateFruitAtRandomPosition(stage);
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

            bool hasEatenFruit = false;
            snake.UpdateCollisionState(stage, score, hasEatenFruit);

            if (hasEatenFruit)
                fruitFactory.CreateFruitAtRandomPosition(stage);
        
            Renderer::Render(stage, snake, window, score, false);
        }
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
    start_color();

    init_pair(1, 46, 46);
    init_pair(2, 40, 40);
    init_pair(3, 232, 255);
    init_pair(4, 160, 46);
    init_pair(5, 21, 75);
    init_pair(6, 130, 130);
    init_pair(7, 231, 231);
    init_pair(8, 242, 240);
}

void Finalize()
{
    endwin();	
}

int main(int argc, char *argv[])
{	
    Initialize();

        Stage stage(Room::Layout, Room::RoomWidth, Room::RoomHeight);
        FruitFactory fruitFactory(stage);

        Snake snake;
        int score = 0;
        WINDOW* window = Renderer::MakeNewWindow();

        RunGame(window, snake, fruitFactory, stage, score);
	
    Finalize();
		
	return 0;
}

