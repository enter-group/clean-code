#ifndef RENDERER_H_
#define RENDERER_H_

#include <curses.h>
#include "Snake.h"
#include "FruitFactory.h"
#include "Segment.h"
#include "Position.h"
#include "GameConstants.h"
#include "Stage.h"
class Renderer
{
public:
    static void RenderGame(Stage& stage, Snake& snake, int score);
    static void MakeNewWindow();
    static void RenderGameOverScreen();

    static WINDOW* GetMainWindow();

private:
    static void RefreshScreen();
    static void RenderHUD(int score, int length);
    static void RenderStageSection(Stage& stage);
    static void RenderSnake(Snake& snake);
    static void ScrollScreenElements(Snake& snake, Stage& stage);

    static void DrawTileOnScreen(Position position, int tileType,  Stage& stage);
    static void RenderGroundTile(Position position, Stage& stage);
    static void RenderWallTile(Position position);
    static void RenderMountainTile(Position position);
    static void RenderWaterTile(Position position);
    static void RenderWoodTile(Position position);
    static void RenderFruitTile(Position position);
    static void SetCharacterOnScren(int character, Position position, int colorIndex);
    static void RenderHUDText(int score, int length);
    static void RenderWindow();

    static bool ShouldScrollRight(Snake& snake, Stage& stage);
    static bool ShouldScrollLeft(Snake& snake, Stage& stage);
    static bool ShouldScrollDown(Snake& snake, Stage& stage);
    static bool ShouldScrollUp(Snake& snake, Stage& stage);


    static int ScreenSectionPositionToIndex(Position position, Stage& stage);

    static Position GetScrollPositionBasedOnSnakePosition(Snake& snake, Stage& stage);
    static Position CalculateScreenSectionPosition(Position position, Stage& stage);

    static WINDOW* window;
};

#endif //RENDERER_H_