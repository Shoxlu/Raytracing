#pragma once
#include <vector>
#include <Scene.h>
#include <Defs.h>




struct Ray{
    Vec start;
    Color color;
    double brightness;
};

class RayTracer{
    public:
        void Render(Image &image, Scene &scene);

    private:
};