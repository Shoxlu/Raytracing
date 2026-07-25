#pragma once
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <string.h>
#include <immintrin.h>

/*
Vecteur à 2 dimensions ou moins
Attributs :
- x->position en abscisse
- y->position en ordonnée
*/
class Vec {
public:
    inline constexpr Vec(float x = 0.0f, float y = 0.0f) : x(x), y(y) {};
    inline Vec(__m128 xy) :y(0) {
        _mm_storeu_ps(&x, xy);
    }
    //Renvoie la norme du Vecteur
    inline float dist() const {
        return sqrtf(dist_sq());
    }
    inline float dist_sq() const {
        return (x * x + y * y);
    }

    inline void clear() {
        // MSVC generates fewer instructions with memset
        // than setting individual fields to 0.
        memset(this, 0, sizeof(*this));
    }

    inline constexpr Vec operator+(const Vec& vec) const {
        return Vec(x + vec.x, y + vec.y);
    }
    inline constexpr Vec operator-(const Vec& vec) const {
        return Vec(x - vec.x, y - vec.y);
    }
    inline constexpr Vec operator*(const Vec& vec) const {
        return Vec(x * vec.x, y * vec.y);
    }
    inline constexpr Vec operator/(const Vec& vec) const {
        return Vec(x / vec.x, y / vec.y);
    }
    inline constexpr Vec operator+(float s) const {
        return Vec(x + s, y + s);
    }
    inline constexpr Vec operator-(float s) const {
        return Vec(x - s, y - s);
    }
    inline constexpr Vec operator*(float s) const {
        return Vec(x * s, y * s);
    }
    inline constexpr Vec operator/(float s) const {
        return operator*(1.0 / s);
    }
    inline constexpr Vec operator+() const {
        return *this;
    }
    inline constexpr Vec operator-() const {
        return Vec(-x, -y);
    }
    inline constexpr Vec& operator+=(const Vec& vec) {
        x += vec.x; y += vec.y;
        return *this;
    }
    inline constexpr Vec& operator-=(const Vec& vec) {
        x -= vec.x; y -= vec.y;
        return *this;
    }
    inline constexpr Vec& operator*=(const Vec& vec) {
        x *= vec.x; y *= vec.y;
        return *this;
    }
    inline constexpr Vec& operator/=(const Vec& vec) {
        x /= vec.x; y /= vec.y;
        return *this;
    }
    inline constexpr Vec& operator+=(float s) {
        x += s; y += s;
        return *this;
    }
    inline constexpr Vec& operator-=(float s) {
        x -= s; y -= s;
        return *this;
    }
    inline constexpr Vec& operator*=(float s) {
        x *= s; y *= s;
        return *this;
    }
    inline constexpr Vec& operator/=(float s) {
        return operator*=(1.0 / s);
    }

    float x;
    float y;
private:

};

inline constexpr float rad(float x) {
    constexpr float conversion = M_PI / 180.0;
    return x * conversion;
}

typedef Vec Force;
