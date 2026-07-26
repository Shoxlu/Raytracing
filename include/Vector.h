#pragma once
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <string.h>
#include <immintrin.h>

/*
Vecteur � 3 dimensions ou moins
Attributs :
- x->position en abscisse
- y->position en ordonn�e
*/
class Vec {
public:
    inline constexpr Vec(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z){};
    //Renvoie la norme du Vecteur
    inline float dist() const {
        return sqrtf(dist_sq());
    }
    inline float dist_sq() const {
        return (x * x + y * y + z*z);
    }

    inline void clear() {
        // MSVC generates fewer instructions with memset
        // than setting individual fields to 0.
        memset(this, 0, sizeof(*this));
    }

    inline constexpr Vec operator+(const Vec& vec) const {
        return Vec(x + vec.x, y + vec.y, z+vec.z);
    }
    inline constexpr Vec operator-(const Vec& vec) const {
        return Vec(x - vec.x, y - vec.y, z-vec.z);
    }
    inline constexpr Vec operator*(const Vec& vec) const {
        return Vec(x * vec.x, y * vec.y, z*vec.z);
    }
    inline constexpr Vec operator/(const Vec& vec) const {
        return Vec(x / vec.x, y / vec.y, z/vec.z);
    }
    inline constexpr Vec operator+(float s) const {
        return Vec(x + s, y + s, z+s);
    }
    inline constexpr Vec operator-(float s) const {
        return Vec(x - s, y - s, z-s);
    }
    inline constexpr Vec operator*(float s) const {
        return Vec(x * s, y * s, z*s);
    }
    inline constexpr Vec operator/(float s) const {
        return operator*(1.0 / s);
    }
    inline constexpr Vec operator+() const {
        return *this;
    }
    inline constexpr Vec operator-() const {
        return Vec(-x, -y, -z);
    }
    inline constexpr Vec& operator+=(const Vec& vec) {
        x += vec.x; y += vec.y;
        z += vec.z;
        return *this;
    }
    inline constexpr Vec& operator-=(const Vec& vec) {
        x -= vec.x; y -= vec.y;z -= vec.z;
        return *this;
    }
    inline constexpr Vec& operator*=(const Vec& vec) {
        x *= vec.x; y *= vec.y; z *= vec.z;
        return *this;
    }
    inline constexpr Vec& operator/=(const Vec& vec) {
        x /= vec.x; y /= vec.y; z /= vec.z;
        return *this;
    }
    inline constexpr Vec& operator+=(float s) {
        x += s; y += s;
        z += s;
        return *this;
    }
    inline constexpr Vec& operator-=(float s) {
        x -= s; y -= s;
        z -= s;
        return *this;
    }
    inline constexpr Vec& operator*=(float s) {
        x *= s; y *= s; z*=s;
        return *this;
    }
    inline constexpr Vec& operator/=(float s) {
        return operator*=(1.0 / s);
    }

    float x;
    float y;
    float z;

private:

};

inline constexpr float rad(float x) {
    constexpr float conversion = M_PI / 180.0;
    return x * conversion;
}

