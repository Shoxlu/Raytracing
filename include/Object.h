#pragma once
#include <Vector.h>
#include <Defs.h>
#include <Ray.h>
class Object
{
public:
    Object(Vec p, ColorA c, double r = 1.0, double b = 0.0f, double t = 0.0);
    virtual bool Intersect(const Ray& obj, Hit& result) = 0;
    Vec pos;
    ColorA color;
    double reflexion;
    double brightness;
    double transparency;
private:
};


class Ball: public Object
{
public:
    Ball(Vec p, ColorA c, double r = 1.0, double b = 0.0, double rad = 1.0, double t = 0.0);
    Ball(Vec p, Color c, double r = 1.0, double b = 0.0, double rad = 1.0, double t = 0.0);
    bool Intersect(const Ray& obj, Hit& result);
    double radius;
private:
};

class Wall: public Object
{
    public:
    Wall(Vec center,ColorA color, Vec size, Vec normal, double r = 1.0, double b= 0.0, double t= 0.0);
    Wall(Wall& w);
    bool IsPointInRectangle(const Vec &point) const;
    bool Intersect(const Ray& obj, Hit& result);
    Vec size;
    Vec normal;
    private:
};