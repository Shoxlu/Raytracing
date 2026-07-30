#pragma once
#include <cstdint>


struct Color {
    /*Opérations pour Color*/
    inline Color operator*(float s) const {
        return Color(r * s, g * s, b*s);
    }
    /*Fonctions utilitaires pour ajouter des couleurs */
    inline Color operator+(const Color& c) const {
        return Color(std::min(255, r + c.r), std::min(255, g + c.g), std::min(255, b + c.b));
    }
    /*Fonctions utilitaires pour soustraire/multiplier/diviser des couleurs entres elles*/
    inline Color operator-(const Color& c) const {
        return Color(std::max(0, r - c.r), std::max(0, g - c.g), std::max(0, b - c.b));
    }
    inline Color operator*(const Color& c) const {
        return Color(r * c.r / 255, g * c.g / 255, b * c.b / 255);
    }
    inline Color operator/(const Color& c) const {
        return Color(r / c.r, g / c.g, b / c.b);
    }
    inline Color& operator+=(const Color& c) {
        r = std::min(255, r + c.r);
        g = std::min(255, g + c.g);
        b = std::min(255, b + c.b);
        return *this;
    }
    inline Color& operator-=(const Color    & c) {
        r = std::max(0, r - c.r);
        g = std::max(0, g - c.g);
        b = std::max(0, b - c.b);
        return *this;
    }
    inline Color& operator*=(const Color& c) {
        r = r * c.r / 255;
        g = g * c.g / 255;
        b = b * c.b / 255;
        return *this;
    }
    inline Color& operator/=(const Color& c) {
        r = r / c.r;
        g = g / c.g;
        b = b / c.b;
        return *this;
    }
	uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct ColorA {
    ColorA(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t a2) : r(r1), g(g1), b(b1), a(a2){}
    ColorA(Color c, uint8_t a2): r(c.r), g(c.g), b(c.b), a(a2){}
    ColorA(): r(0), g(0), b(0), a(0){}
    inline ColorA operator*(float s) const {
        return ColorA(r * s, g * s, b*s, a);
    }
    /*Fonctions utilitaires pour ajouter des couleurs */
    inline ColorA operator+(const ColorA& c) const {
        return ColorA(std::min(255, r + c.r), std::min(255, g + c.g), std::min(255, b + c.b), a);
    }
    /*Fonctions utilitaires pour soustraire/multiplier/diviser des couleurs entres elles*/
    inline ColorA operator-(const ColorA& c) const {
        return ColorA(std::max(0, r - c.r), std::max(0, g - c.g), std::max(0, b - c.b), a);
    }
    inline ColorA operator*(const ColorA& c) const {
        return ColorA(r * c.r / 255, g * c.g / 255, b * c.b / 255, a);
    }
    inline ColorA operator/(const ColorA& c) const {
        return ColorA(r / c.r, g / c.g, b / c.b, a);
    }
    inline ColorA& operator+=(const ColorA& c) {
        r = std::min(255, r + c.r);
        g = std::min(255, g + c.g);
        b = std::min(255, b + c.b);
        return *this;
    }
    inline ColorA& operator-=(const ColorA& c) {
        r = std::max(0, r - c.r);
        g = std::max(0, g - c.g);
        b = std::max(0, b - c.b);
        return *this;
    }
    inline ColorA& operator*=(const ColorA& c) {
        r = r * c.r / 255;
        g = g * c.g / 255;
        b = b * c.b / 255;
        return *this;
    }
    inline ColorA& operator/=(const ColorA& c) {
        r = r / c.r;
        g = g / c.g;
        b = b / c.b;
        return *this;
    }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

