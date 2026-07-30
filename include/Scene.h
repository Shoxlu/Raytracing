#pragma once
#include <Camera.h>
#include <Object.h>
#include <Defs.h>

class Scene{
    public:
        std::vector<Ball> objects;
        std::vector<Light> lights;
        Camera camera;
    private:
        //Lights ?
        //Objects ?
        //Camera ?
};