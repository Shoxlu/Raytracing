#pragma once
#include <vector>
#include <Scene.h>
#include <Defs.h>
#include <Ray.h>




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