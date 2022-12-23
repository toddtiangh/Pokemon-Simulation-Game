#ifndef View_h
#define View_h
#include "Point2D.h"
#include "GameObject.h"

const int view_maxsize = 20;

class View
{
private:
    int size;
    double scale;
    Point2D origin = Point2D();
    char grid[view_maxsize + 1][view_maxsize + 1][2];
    bool GetSubscripts(int &out_x, int &out_y, Point2D location);
public:
    View();

    void Clear();

    void Plot(GameObject *ptr);

    void Plot(int x, int y);

    void Plot(int x, int y, int state);

    void Draw();

};
#endif /* View_h */
