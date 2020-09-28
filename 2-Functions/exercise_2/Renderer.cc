#include "Renderer.h"

void Renderer::Render(Stage& stage, Snake& snake, WINDOW* window, int score, bool isGameOver)
{
    if (isGameOver)
    {
        mvwprintw(window, 1, 1," GAME OVER!\t Press F2 to restart");
    }
    else
    {
        werase(window);
        box(window, 0, 0);
        mvwprintw(window, 1, 1," Score: %d\tSize: %d", score, snake.Length());
        wmove(window, 2, 1);
        whline(window, ACS_HLINE, windowWidth - 2);
        mvprintw(windowHeight, 1, "Press F1 to exit");

        for (size_t i = 0; i < playfieldHeight; i++)
        {
            for (size_t j = 0; j < playfieldWidth; j++)
            {
                if (stage.GetRoomReference()[(i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset())] == 0)
                {
                    int index = (i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset());
                    wattron(window, COLOR_PAIR(index%4 < 2? 1 : 2));
                    mvwaddch(window, i + viewportVerticalOffset, j + viewportHorizontalOffset, ACS_CKBOARD);
                    wattroff(window, COLOR_PAIR(index%4 < 2? 1 : 2));
                }
                else if (stage.GetRoomReference()[(i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset())] == 1)
                {
                    wattron(window, COLOR_PAIR(8));
                    mvwaddch(window, i + viewportVerticalOffset, j + viewportHorizontalOffset, ACS_CKBOARD);
                    wattroff(window, COLOR_PAIR(8));
                }
                else if (stage.GetRoomReference()[(i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset())] == 2)
                {
                    wattron(window, COLOR_PAIR(3));
                    mvwaddch(window, i + viewportVerticalOffset, j + viewportHorizontalOffset, '^');
                    wattroff(window, COLOR_PAIR(3));
                }
                else if (stage.GetRoomReference()[(i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset())] == 3)
                {
                    wattron(window, COLOR_PAIR(5));
                    mvwaddch(window, i + viewportVerticalOffset, j + viewportHorizontalOffset, '~');
                    wattroff(window, COLOR_PAIR(5));
                }
                else if (stage.GetRoomReference()[(i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset())] == 4)
                {
                    wattron(window, COLOR_PAIR(6));
                    mvwaddch(window, i + viewportVerticalOffset, j + viewportHorizontalOffset, '-');
                    wattroff(window, COLOR_PAIR(6));
                }
                else if (stage.GetRoomReference()[(i + stage.GetRoomVerticalOffset())*stage.GetRoomSize().width + (j + stage.GetRoomHorizontalOffset())] == 100)
                {
                    wattron(window, COLOR_PAIR(4));
                    mvwaddch(window, i + viewportVerticalOffset, j + viewportHorizontalOffset, ACS_DIAMOND);
                    wattroff(window, COLOR_PAIR(4));
                }
            }
        }

        if (snake.GetHeadPosition().x >= playfieldWidth/2 && snake.GetDirection() == Direction::right && stage.GetRoomHorizontalOffset() <= (stage.GetRoomSize().width - 1) - playfieldWidth)
        {
            Position newPos;
            newPos.x = snake.GetHeadPosition().x + 1;
            newPos.y = snake.GetHeadPosition().y;
            snake.SetPosition(newPos);
            stage.SetRoomHorizontalOffset(stage.GetRoomHorizontalOffset() + 1);
        }

        if (snake.GetHeadPosition().x <= playfieldWidth/2 && snake.GetDirection() == Direction::left && stage.GetRoomHorizontalOffset() > 0)
        {
            Position newPos;
            newPos.x = snake.GetHeadPosition().x - 1;
            newPos.y = snake.GetHeadPosition().y;
            snake.SetPosition(newPos);
            stage.SetRoomHorizontalOffset(stage.GetRoomHorizontalOffset() - 1);
        }

        if (snake.GetHeadPosition().y >= playfieldHeight/2 && snake.GetDirection() == Direction::down && stage.GetRoomVerticalOffset() <= (stage.GetRoomSize().height - 1) - playfieldHeight)
        {
            Position newPos;
            newPos.x = snake.GetHeadPosition().x;
            newPos.y = snake.GetHeadPosition().y + 1;
            snake.SetPosition(newPos);
            stage.SetRoomVerticalOffset(stage.GetRoomVerticalOffset() + 1);
        }

        if (snake.GetHeadPosition().y <= playfieldHeight/2 && snake.GetDirection() == Direction::up && stage.GetRoomVerticalOffset() > 0)
        {
            Position newPos;
            newPos.x = snake.GetHeadPosition().x;
            newPos.y = snake.GetHeadPosition().y - 1;
            snake.SetPosition(newPos);
            stage.SetRoomVerticalOffset(stage.GetRoomVerticalOffset() - 1);
        }

        for (auto i = 0; i < snake.Length(); i++)
        {
            wattron(window, COLOR_PAIR(7));
            mvwaddch(window, snake.body[i].y + viewportVerticalOffset,
                            snake.body[i].x + viewportHorizontalOffset, ACS_CKBOARD);
            wattroff(window, COLOR_PAIR(7));
        }
    }
    wrefresh(window);
    refresh();
}


WINDOW* Renderer::MakeNewWindow()
{
    WINDOW *window;

	window = newwin(windowHeight, windowWidth, 0, 0);
	box(window, 0 , 0);
	wrefresh(window);

	return window;
}
