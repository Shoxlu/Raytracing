#pragma once
#include <Camera.h>
#include <Object.h>
#include <Defs.h>

class Scene{
    public:
        void AddBall(Ball b);
        void AddWall(Wall b);
        void AddLight(Light Object);
        std::vector<Object*> objects;
        std::vector<Light> lights;
        Camera camera;
    private:
        //Lights ?
        //Objects ?
        //Camera ?
};