#include <iostream>
#include "Vector2D.h"
using namespace std;


Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}


Vector2D operator*(Vector2D v1, double d)
{
    v1.x = v1.x * d;
    v1.y = v1.y * d;

    return v1;
}

Vector2D operator/(Vector2D v1, double d)
{
    v1.x = v1.x / d;
    v1.y = v1.y / d;

    return v1;
}

Vector2D operator<<(ostream& os, Vector2D v1)
{
    cout << "<" << v1.x << ", " << v1.y << ">";
}
