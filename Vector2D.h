#ifndef Vector2D_h
#define Vector2D_h

using namespace std;

class Vector2D
{
public:
    double x;
    double y;
    Vector2D();
    Vector2D(double in_x, double in_y);
};
Vector2D operator*(Vector2D v1, double d);
Vector2D operator/(Vector2D v1, double d);
Vector2D operator<<(ostream& os, Vector2D v1);

#endif /* Vector2D_h */
