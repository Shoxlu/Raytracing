#pragma once
#include <vector>
#include <Scene.h>
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

class RayTracer{
    public:
        void Render(Image &image, Scene &scene);
        
        bool Intersect(const Ray& ray,
        const Ball& sphere,Hit& hit);
        bool isOccluded(Ray& ray, float distance, Scene& scene);
        ColorA Trace(Ray &ray, Scene &scene, int depth, Hit& res);
        Color ComputeLighting(Hit& hit, Scene &scene);
        ColorA MixColorsSub(Ray &ray, Vec hitPoint, ColorA &color, double brightness, double reflexion);

    private:
};