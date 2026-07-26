#include <Object.h>


Object::Object(Vec p,Color c, double r, double b): pos(p), color(c), reflexion(r), brightness(b)
{

}


Ball::Ball(Vec p, Color c, double r , double b, double rad):Object(p, c, r, b), radius(rad)
{

}