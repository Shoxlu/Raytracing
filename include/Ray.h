#pragma once
#include <vector>
#include <Defs.h>

struct Hit{
    Vec hitPoint;
    Vec normal;
    double distance;
    double reflection_coeff;
};


struct Ray{
    Ray(Vec start, Vec dir, Color color = {255, 255, 255}, double brightness = 1.0) :
    start(start), dir(dir), color(color), brightness(brightness) {}
    Ray Reflect(Hit& hit, ColorA c);
    Vec start;
    Vec dir;
    Color color;
    double brightness;
};