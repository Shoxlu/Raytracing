#pragma once
#include <Vector.h>
#include <Defs.h>
#include <Ray.h>
class Object
{
public:
    Object(Vec p, ColorA c, double r = 1.0, double b = 0.0f);
    virtual bool Intersect(const Ray& obj, Hit& result) = 0;
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
    Ball(Vec p, Color c, double r = 1.0, double b = 0.0, double rad = 1.0);
    bool Intersect(const Ray& obj, Hit& result);
    double radius;
private:
};

class Wall: public Object
{
    public:
    Wall(Vec center, Vec size, double r = 1.0);
    double size;
    private:
};