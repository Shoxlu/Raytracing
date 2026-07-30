#pragma once
#include <Vector.h>
#include <vector>
#include <cstdint>
#include <utility>
#include <Color.h>

enum ObjTypes {
    None,
    Circle,
    Sphere,
    Square,
    Point
};

enum Shaders {
    Default
};


struct Light
{
    Vec position;
    Color color;
};


struct Vertex
{
    Vertex(Vec a, float z1, ColorA c):pos(a), z(z1), color(c){}
    Vec pos;
	float z;
	ColorA color;
};

struct Line
{
    Vertex v1;
    Vertex v2;

    Line() = default;

    Line(Vec a, Vec b): Line(a, b, { 255,255,255, 255 }, { 255,255,255, 255 }) {}

    Line(Vec a, Vec b, ColorA c): Line(a, b, c, c) {}

    Line(Vec a, Vec b, ColorA c1, ColorA c2):
        v1( a, 0.f, c1), v2 ( b, 0.f, c2)
    {
    }
};


struct Image{
    Image(size_t width, size_t height): width(width), height(height), pixels(width*height) {}
    Image(): width(0), height(0) {}
    size_t width;
    size_t height;
    unsigned int texture = -1;
    std::vector<ColorA> pixels;
};