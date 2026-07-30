#pragma once
#include <Vector.h>
#include <Defs.h>

class Object
{
public:
    Object(Vec p, ColorA c, double r = 1.0, double b = 0.0f);

    Vec pos;
    ColorA color;
    double reflexion;
    double brightness;
private:
};


class Ball: public Object
{
public:
    Ball(Vec p, ColorA c, double r = 1.0, double b = 0.0, double rad = 1.0);
    double radius;
private:
};