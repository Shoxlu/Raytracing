#pragma once
#include <vector>
#include <Scene.h>
#include <Defs.h>



struct Image{
    std::vector<Color> pixels;
};

class RayTracer{
    public:
        RayTracer(size_t width, size_t height);
        void Render(Image &image, Scene &scene);

    private:
};