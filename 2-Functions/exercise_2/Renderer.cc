#include "Renderer.h"

WINDOW* Renderer::window;

void Renderer::RefreshScreen()
{
    wrefresh(window);
    refresh();
}

Position Renderer::CalculateScreenSectionPosition(Position position, Stage& stage)
{
    return stage.ScreenToGlobalPosition(position);
}

int Renderer::ScreenSectionPositionToIndex(Position position, Stage& stage)
{
     return (position.y + stage.GetStageVerticalOffset())*stage.GetStageSize().width + (position.x + stage.GetStageHorizontalOffset());
}

void Renderer::SetCharacterOnScren(int character, Position position, int colorIndex)
{
    wattron(window, COLOR_PAIR(colorIndex));
    mvwaddch(window, position.y + viewportVerticalOffset, position.x + viewportHorizontalOffset, character);
    wattroff(window, COLOR_PAIR(colorIndex));
}

void Renderer::RenderGroundTile(Position position, Stage& stage)
{
    int index = ScreenSectionPositionToIndex(CalculateScreenSectionPosition(position, stage), stage);

    if (index%4 < 2)
        SetCharacterOnScren(ACS_CKBOARD, position, 1);
    else
        SetCharacterOnScren(ACS_CKBOARD, position, 2);
}

void Renderer::RenderWallTile(Position position)
{
    SetCharacterOnScren(ACS_CKBOARD, position, 8);
}

void Renderer::RenderMountainTile(Position position)
{
    SetCharacterOnScren(static_cast<int>('^'), position, 3);
}

void Renderer::RenderWaterTile(Position position)
{
    SetCharacterOnScren(static_cast<int>('~'), position, 5);
}

void Renderer::RenderWoodTile(Position position)
{
    SetCharacterOnScren(static_cast<int>('-'), position, 6);
}

void Renderer::RenderFruitTile(Position position)
{
    SetCharacterOnScren(ACS_DIAMOND, position, 4);
}

void Renderer::DrawTileOnScreen(Position position, int tileType, Stage& stage)
{
    if (tileType == 0)  RenderGroundTile(position, stage);
    else if (tileType == 1) RenderWallTile(position);
    else if (tileType == 2) RenderMountainTile(position);
    else if (tileType == 3) RenderWaterTile(position);
    else if (tileType == 4)  RenderWoodTile(position);
    else if (tileType == 100) RenderFruitTile(position);
}

bool Renderer::ShouldScrollRight(Snake& snake, Stage& stage)
{
    return snake.GetHeadLocalPosition().x >= playfieldWidth/2 && 
           snake.GetDirection() == Direction::right && 
           stage.GetStageHorizontalOffset() <= (stage.GetStageSize().width - 1) - playfieldWidth;
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
           stage.GetStageVerticalOffset() <= (stage.GetStageSize().height - 1) - playfieldHeight;
}

bool Renderer::ShouldScrollUp(Snake& snake, Stage& stage)
{
    return snake.GetHeadLocalPosition().y <= playfieldHeight/2 && 
           snake.GetDirection() == Direction::up && 
           stage.GetStageVerticalOffset() > 0;
}

Position Renderer::GetScrollPositionBasedOnSnakePosition(Snake& snake, Stage& stage)
{
    if (ShouldScrollRight(snake, stage)) return Position::MakePosition(1, 0);
    if (ShouldScrollLeft(snake, stage))  return Position::MakePosition(-1, 0);
    if (ShouldScrollDown(snake, stage)) return Position::MakePosition(0, 1);
    if (ShouldScrollUp(snake, stage)) return Position::MakePosition(0, -1);

    return Position::MakePosition(0, 0);
}

void Renderer::RenderStageSection(Stage &stage)
{
    for (size_t i = 0; i < playfieldHeight; i++)
        for (size_t j = 0; j < playfieldWidth; j++)
        {
            Position screenPosition = Position::MakePosition(j, i);
            int tileType = stage.GetTileAt(CalculateScreenSectionPosition(screenPosition, stage));
            DrawTileOnScreen(screenPosition, tileType, stage);
        }
}

void Renderer::RenderHUDText(int score, int length)
{
    mvwprintw(window, 1, 1," Score: %d\tSize: %d", score, length);
    mvprintw(windowHeight, 1, "Press F1 to exit");
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
    RenderWindow();
    RenderHUDText(score, length);
}

void Renderer::ScrollScreenElements(Snake& snake, Stage& stage)
{
    Position scrollAmount = GetScrollPositionBasedOnSnakePosition(snake, stage);

    stage.SetStageOffsets(stage.GetStageHorizontalOffset() + scrollAmount.x, stage.GetStageVerticalOffset() + scrollAmount.y);
    snake.PlaceBodyAtPosition(Position::MakePosition(snake.GetHeadLocalPosition().x + scrollAmount.x, snake.GetHeadLocalPosition().y + scrollAmount.y));
}

void Renderer::RenderSnake(Snake& snake)
{
    for (auto i = 0; i < snake.Length(); i++)
    {
        Position snakePosition = Position::MakePosition(snake.body[i].x, snake.body[i].y);
        SetCharacterOnScren(ACS_CKBOARD, snakePosition, 7);
    }
}

void Renderer::RenderGame(Stage& stage, Snake& snake, int score)
{
    RenderHUD(score, snake.Length());
    RenderStageSection(stage);
    ScrollScreenElements(snake, stage);
    RenderSnake(snake);
    RefreshScreen();
}

void Renderer::RenderGameOverScreen()
{
    mvwprintw(window, 1, 1," GAME OVER!\t Press F2 to restart");
    RefreshScreen();
}

void Renderer::MakeNewWindow()
{
    WINDOW *wnd;

	wnd = newwin(windowHeight, windowWidth, 0, 0);
	box(wnd, 0 , 0);
	wrefresh(wnd);

	window = wnd;
}

WINDOW* Renderer::GetMainWindow()
{
    return window;
}
