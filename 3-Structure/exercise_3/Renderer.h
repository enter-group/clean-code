/*
COPYRIGHT 2020 - ENTER. ALL RIGHTS RESERVED.
*/

#ifndef RENDERER_H_
#define RENDERER_H_

#include <curses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "Snake.h"
#include "FruitFactory.h"
#include "Segment.h"
#include "Point2D.h"
#include "GameConstants.h"
#include "Stage.h"

#include "LandLib/MapGenerator.h"

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

    static void DrawTileOnScreen(Point2D position, int tileType, Stage& stage);
    static void RenderGroundTile(Point2D position, Stage& stage);
    static void RenderWallTile(Point2D position);
    static void RenderMountainTile(Point2D position, Stage& stage);
    static void RenderWaterTile(Point2D position);
    static void RenderWoodTile(Point2D position);
    static void RenderFruitTile(Point2D position);
    static void SetCharacterOnScreen(int character, Point2D position, int colorIndex);
    static void RenderHUDText(int score, int length);
    static void RenderWindow();

    static bool ShouldScrollRight(Snake& snake, Stage& stage);
    static bool ShouldScrollLeft(Snake& snake, Stage& stage);
    static bool ShouldScrollDown(Snake& snake, Stage& stage);
    static bool ShouldScrollUp(Snake& snake, Stage& stage);

    static Size GetScreenSize();

    static int ScreenSectionPositionToIndex(Point2D position, Stage& stage);

    static Point2D GetScrollPositionBasedOnSnakePosition(Snake& snake, Stage& stage);
    static Point2D CalculateScreenSectionPosition(Point2D position, Stage& stage);

    static WINDOW* window;
};

#endif //RENDERER_H_