#pragma once
#include <vector>
#include <Scene.h>
#include <Defs.h>


struct Ray{
    Ray(Vec start, Vec dir, Color color = {255, 255, 255}, double brightness = 1.0) :
    start(start), dir(dir), color(color), brightness(brightness) {}
    Vec start;
    Vec dir;
    Color color;
    double brightness;
};

class RayTracer{
    public:
        void Render(Image &image, Scene &scene);
        
        bool Intersect(const Ray& ray,
        const Ball& sphere,
        double& t);
        ColorA Trace(Ray &ray, Scene &scene);
        Color ComputeLighting(Vec hitPoint, Vec normal, Scene &scene);
        ColorA MixColorsSub(Ray &ray, Vec hitPoint, ColorA &color, double brightness, double reflexion);

    private:
};