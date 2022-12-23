#include <iostream>
#include <math.h>
#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

Point2D::Point2D()
{
    x = 0;
    y = 0;
}
Point2D::Point2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(Point2D p1, Point2D p2)
{
    return sqrt((pow((p2.x - p1.x),2)) + (pow((p2.y - p1.y),2)));
}

Point2D operator<<(ostream& os, Point2D p1)
{
    cout << "(" << p1.x << ", " << p1.y << ")";
}

Point2D operator+(Point2D p1, Vector2D v1)
{
    p1.x += v1.x;
    p1.y += v1.y;

    return p1;
}

Vector2D operator-(Point2D p1, Vector2D v1)
{
    v1.x -= p1.x;
    v1.y -= p1.y;

    return v1;
}
