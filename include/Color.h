#pragma once
#include <cstdint>


struct Color {
	uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct ColorA {
    ColorA(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t a2) : r(r1), g(g1), b(b1), a(a2){}
    ColorA(Color c, uint8_t a2): r(c.r), g(c.g), b(c.b), a(a2){}
    ColorA(): r(0), g(0), b(0), a(0){}
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

