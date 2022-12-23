#ifndef Point2D_h
#define Point2D_h
#include <iostream>
#include "Vector2D.h"

using namespace std;

class Point2D
{
public:
    double x;
    double y;
    Point2D();
    Point2D(double in_x, double in_y);
};

double GetDistanceBetween(Point2D p1, Point2D p2);
Point2D operator<<(ostream& os, Point2D p1);
Point2D operator+(Point2D p1, Vector2D v1);
Vector2D operator-(Point2D p1, Vector2D v1);

#endif /* Point2D_h */

