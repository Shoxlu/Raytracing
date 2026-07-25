#pragma once
#include <Vector.h>
#include <cstdint>
#include <utility>

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


struct Color {
	uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct ColorA {
    ColorA(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t a2) : r(r1), g(g1), b(b1), a(a2){}
    ColorA(Color c, uint8_t a2): r(c.r), g(c.g), b(c.b), a(a2){}
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
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