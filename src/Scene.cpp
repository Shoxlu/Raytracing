#include <Scene.h>


void Scene::AddLight(Light light)
{
    lights.push_back(light);
    Ball b(light.position, light.color, 0.0, 1.0, 10.0);
    //AddBall(b);
}


void Scene::AddBall(Ball b)
{
    Ball* ball = new Ball(b.pos, b.color,  b.reflexion, b.brightness, b.radius);
    objects.push_back(ball);
}

void Scene::AddWall(Wall b)
{
    Wall* w = new Wall(b);
    objects.push_back(w);
}