#ifndef POINT_2D_
#define POINT_2D_

struct Point2D
{
    int x;
    int y;

    static Point2D MakePosition(int x, int y);
};

#endif // POINT_2D_