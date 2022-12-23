#include "View.h"
#include <iostream>
#include <cmath>

using namespace std;

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
    if(out_x <= view_maxsize && out_y <= view_maxsize)
    {
        if(out_y == 20)
            out_y = 19;
        return true;
    }
    else
    {
        cout << "An Object is outside the display" << endl;
        return false;
    }
}
View::View()
{
    size = 11;
    scale = 2;
    origin = Point2D();
}

void View::Clear()
{
    for(int i = view_maxsize; i >= 0; i--)
    {
        for(int j = 0; j <= view_maxsize; j++)
        {
           if(i % 2 == 0 && j % 2 == 0)
           {
                grid[i][j][0] = '.';
           }
        }
    }
}

void View::Plot(GameObject *ptr)
{
    int x = ptr->GetLocation().x;
    int y = ptr->GetLocation().y;

    if(GetSubscripts(x, y, Point2D(x,y)))
    {
        char* id_ptr;
        char id = ('0' + ptr->GetId());
        ptr->DrawSelf(&id_ptr);
        grid[x][y][0] = *id_ptr;
        grid[x][y+1][0] = id;
    }
}

void View::Plot(int x, int y)
{
    if(x <= view_maxsize && y <= view_maxsize)
    {
        if(y == 20)
            y = 19;
    }
    if(x % 2 == 0 && y % 2 == 0)
    {
        grid[x][y][0] = '.';
        grid[x][y+1][0] = ' ';
    }
    else if(x%2 == 0 && y%2 == 1)
    {
        grid[x][y][0] = ' ';
        grid[x][y+1][0] = '.';
    }
    else if(x%2 == 1 && y%2 == 0)
    {
        grid[x][y][0] = ' ';
        grid[x][y+1][0] = ' ';
    }
    else
    {
        grid[x][y][0] = ' ';
        grid[x][y+1][0] = ' ';
    }

}

void View::Plot(int x, int y, int state)
{
    if(x <= view_maxsize && y <= view_maxsize)
    {
        if(y == 20)
            y = 19;
    }
    grid[x][y][0] = '*';
    grid[x][y+1][0] = '|';
}


void View::Draw()
{
    for(int i = view_maxsize; i >= 0; --i)
    {

        for(int j = 0; j <= view_maxsize; ++j)
        {
            cout << grid[i][j][0] << "  ";
        }
        cout << endl;
    }
}
