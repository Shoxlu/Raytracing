#pragma once
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <string.h>
#include <immintrin.h>
#include <glm/glm.hpp>


/*
Vecteur 3 dimensions ou moins
Attributs :
- x->position en abscisse
- y->position en ordonnée
- z->position en cote
*/
class Vec {
    public:
    inline constexpr Vec(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z){};
    //Renvoie la norme du Vecteur
    inline double dist() const {
        return sqrt(dist_sq());
    }
    inline double dist_sq() const {
        return (x * x + y * y + z*z);
    }
    
    inline void clear() {
        // MSVC generates fewer instructions with memset
        // than setting individual fields to 0.
        memset(this, 0, sizeof(*this));
    }
    
    inline constexpr double dot(const Vec& vec)
    {
        return x*vec.x+y*vec.y+ z*vec.z;
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
    inline constexpr Vec operator+(double s) const {
        return Vec(x + s, y + s, z+s);
    }
    inline constexpr Vec operator-(double s) const {
        return Vec(x - s, y - s, z-s);
    }
    inline constexpr Vec operator*(double s) const {
        return Vec(x * s, y * s, z*s);
    }
    inline constexpr Vec operator/(double s) const {
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
    inline constexpr Vec& operator+=(double s) {
        x += s; y += s;
        z += s;
        return *this;
    }
    inline constexpr Vec& operator-=(double s) {
        x -= s; y -= s;
        z -= s;
        return *this;
    }
    inline constexpr Vec& operator*=(double s) {
        x *= s; y *= s; z*=s;
        return *this;
    }
    inline constexpr Vec& operator/=(double s) {
        return operator*=(1.0 / s);
    }
    /* A bit of code to convert glm::vec3 to Vec with the = operator*/
    inline Vec& operator=(const glm::vec3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }
    /* Implicit conversion from glm::vec3 */
    inline Vec(const glm::vec3& vec) {
        *this = vec;
    }
    
    
    double x;
    double y;
    double z;
    
    private:
    
};



inline constexpr double rad(double x) {
    constexpr double conversion = M_PI / 180.0;
    return x * conversion;
}

Vec normalize(Vec v);

double dot(Vec v1, Vec v2);
