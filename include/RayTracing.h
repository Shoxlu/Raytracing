#pragma once
#include <vector>
#include <Scene.h>
#include <Defs.h>
#include <Ray.h>




class RayTracer{
    public:
        void Render(Image &image, Scene &scene);
        
        bool isOccluded(Ray& ray, float distance, Scene& scene, double& transmission);
        ColorA Trace(Ray &ray, Scene &scene, int depth, Hit& res);
        Color ComputeLighting(Hit& hit, Scene &scene);
        ColorA MixColorsSub(Ray &ray, Vec hitPoint, ColorA &color, double brightness, double reflexion);

    private:
};