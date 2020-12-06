#include "Renderer.h"

WINDOW* Renderer::window;

using namespace LandLib;

void Renderer::RefreshScreen()
{
    wrefresh(window);
}

Point2D Renderer::CalculateScreenSectionPosition(Point2D position, Stage& stage)
{
    return stage.ScreenToGlobalPosition(position);
}

int Renderer::ScreenSectionPositionToIndex(Point2D position, Stage& stage)
{
     return (position.y + stage.GetStageVerticalOffset())*stage.GetStageSize().width + (position.x + stage.GetStageHorizontalOffset());
}

void Renderer::SetCharacterOnScreen(int character, Point2D position, int colorIndex)
{
    wattron(window, COLOR_PAIR(colorIndex));
    mvwaddch(window, position.y + viewportVerticalOffset, position.x + viewportHorizontalOffset, character);
    wattroff(window, COLOR_PAIR(colorIndex));
}

void Renderer::RenderGroundTile(Point2D position, Stage& stage)
{
    int index = ScreenSectionPositionToIndex(CalculateScreenSectionPosition(position, stage), stage);

    if (index%4 < 2)
        SetCharacterOnScreen(' ', position, 1);
    else
        SetCharacterOnScreen(' ', position, 2);
}

void Renderer::RenderWallTile(Point2D position)
{
    SetCharacterOnScreen(' ', position, 8);
}

void Renderer::RenderMountainTile(Point2D position, Stage& stage)
{
    int tile = stage.GetTileAt(CalculateScreenSectionPosition(position, stage));
    SetCharacterOnScreen(static_cast<int>(' '), position, 8 + tile);
}

void Renderer::RenderWaterTile(Point2D position)
{
    SetCharacterOnScreen(static_cast<int>(' '), position, 5);
}

void Renderer::RenderWoodTile(Point2D position)
{
    SetCharacterOnScreen(static_cast<int>(' '), position, 6);
}

void Renderer::RenderFruitTile(Point2D position)
{
    SetCharacterOnScreen(ACS_DIAMOND, position, 4);
}

void Renderer::DrawTileOnScreen(Point2D position, int tileType, Stage& stage)
{
    if (tileType == static_cast<int>(TerrainType::Ground))  RenderGroundTile(position, stage);
    else if (tileType == static_cast<int>(TerrainType::Wall)) RenderWallTile(position);
    else if (tileType == static_cast<int>(TerrainType::MountainLv1) || tileType == static_cast<int>(TerrainType::MountainLv2) ||
             tileType == static_cast<int>(TerrainType::MountainLv3) || tileType == static_cast<int>(TerrainType::MountainLv4) ||
             tileType == static_cast<int>(TerrainType::MountainLv5)) RenderMountainTile(position, stage);
    else if (tileType == static_cast<int>(TerrainType::River)) RenderWaterTile(position);
    else if (tileType == static_cast<int>(TerrainType::Bridge))  RenderWoodTile(position);
    else if (tileType == 100) RenderFruitTile(position);
}

bool Renderer::ShouldScrollRight(Snake& snake, Stage& stage)
{
    return snake.GetHeadLocalPosition().x >= playfieldWidth/2 && 
           snake.GetDirection() == Direction::right && 
           stage.GetStageHorizontalOffset() <= (static_cast<int>(stage.GetStageSize().width) - 1) - playfieldWidth;
}

bool Renderer::ShouldScrollLeft(Snake& snake, Stage& stage)
{
    return snake.GetHeadLocalPosition().x <= playfieldWidth/2 && 
           snake.GetDirection() == Direction::left && 
           stage.GetStageHorizontalOffset() > 0;
}

bool Renderer::ShouldScrollDown(Snake& snake, Stage& stage)
{
    return snake.GetHeadLocalPosition().y >= playfieldHeight/2 && 
           snake.GetDirection() == Direction::down && 
           stage.GetStageVerticalOffset() <= (static_cast<int>(stage.GetStageSize().height) - 1) - playfieldHeight;
}

bool Renderer::ShouldScrollUp(Snake& snake, Stage& stage)
{
    return snake.GetHeadLocalPosition().y <= playfieldHeight/2 && 
           snake.GetDirection() == Direction::up && 
           stage.GetStageVerticalOffset() > 0;
}

Point2D Renderer::GetScrollPositionBasedOnSnakePosition(Snake& snake, Stage& stage)
{
    if (ShouldScrollRight(snake, stage)) return Point2D::MakePosition(1, 0);
    if (ShouldScrollLeft(snake, stage))  return Point2D::MakePosition(-1, 0);
    if (ShouldScrollDown(snake, stage)) return Point2D::MakePosition(0, 1);
    if (ShouldScrollUp(snake, stage)) return Point2D::MakePosition(0, -1);

    return Point2D::MakePosition(0, 0);
}

void Renderer::RenderStageSection(Stage &stage)
{
    for (size_t i = 0; i < playfieldHeight; i++)
        for (size_t j = 0; j < playfieldWidth; j++)
        {
            Point2D screenPosition = Point2D::MakePosition(j, i);
            int tileType = stage.GetTileAt(CalculateScreenSectionPosition(screenPosition, stage));
            DrawTileOnScreen(screenPosition, tileType, stage);
        }
}

void Renderer::RenderHUDText(int score, int length)
{
    mvprintw(1, 1, 
" ______         __         __   __               _______               __            \n\
 |   __ \\.-----.|  |--.    |  |_|  |--.-----.    |     __|.-----.---.-.|  |--.-----. \n\
 |   __ <|  _  ||  _  |    |   _|     |  -__|    |__     ||     |  _  ||    <|  -__| \n\
 |______/|_____||_____|    |____|__|__|_____|    |_______||__|__|___._||__|__|_____| ver 0.4");

    wattron(window, COLOR_PAIR(3));
    mvwprintw(window, 1, 1," Score: %d\tSize: %d", score, length);                   
    mvprintw(GetScreenSize().height/2 + windowHeight/2, GetScreenSize().width/2 - 12, "Press START + C to exit");
    wattroff(window, COLOR_PAIR(3));
}

void Renderer::RenderPauseText()
{
    wattron(window, COLOR_PAIR(3));
    mvprintw(GetScreenSize().height/2 + windowHeight/2, GetScreenSize().width/2 - 12, "     *** PAUSED ***     ");
    wattroff(window, COLOR_PAIR(3));
}

void Renderer::RenderWindow()
{
    werase(window);
    box(window, 0, 0);
    wmove(window, 2, 1);
    whline(window, ACS_HLINE, windowWidth - 2);
}

void Renderer::RenderHUD(int score, int length)
{
    wattron(window, COLOR_PAIR(3));
    RenderWindow();
    RenderHUDText(score, length);
    wattroff(window, COLOR_PAIR(3));
}

void Renderer::ScrollScreenElements(Snake& snake, Stage& stage)
{
    Point2D scrollAmount = GetScrollPositionBasedOnSnakePosition(snake, stage);
    stage.SetStageOffsets(stage.GetStageHorizontalOffset() + scrollAmount.x, stage.GetStageVerticalOffset() + scrollAmount.y);
    snake.PlaceBodyAtPosition(Point2D::MakePosition(snake.GetHeadLocalPosition().x + scrollAmount.x, snake.GetHeadLocalPosition().y + scrollAmount.y));
}

void Renderer::RenderSnake(Snake& snake)
{
    for (auto i = 0; i < snake.Length(); i++)
    {
        Point2D snakePosition = Point2D::MakePosition(snake.body[i].x, snake.body[i].y);
        if (i%2)
            SetCharacterOnScreen(' ', snakePosition, 16);
        else
            SetCharacterOnScreen(' ', snakePosition, 17);
    }
}

void Renderer::RenderGame(Stage& stage, Snake& snake, int score)
{
    RenderHUD(score, snake.Length());
    ScrollScreenElements(snake, stage);
    RenderStageSection(stage);
    RenderSnake(snake);
    RefreshScreen();
}

void Renderer::RenderGameOverScreen()
{
    wattron(window, COLOR_PAIR(3));
    mvwprintw(window, 1, 1," GAME OVER!\t Press START to try again");
    wattroff(window, COLOR_PAIR(3));
    RefreshScreen();
}

void Renderer::MakeNewWindow()
{
    WINDOW *wnd;
	wnd = newwin(windowHeight, windowWidth, GetScreenSize().height/2 - windowHeight/2, GetScreenSize().width/2 - windowWidth/2);
	box(wnd, 0 , 0);
	wrefresh(wnd);
	window = wnd;
}

Size Renderer::GetScreenSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return Size::MakeSize(w.ws_col, w.ws_row);
}

WINDOW* Renderer::GetMainWindow()
{
    return window;
}
