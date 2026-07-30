#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <Window.h>
#include <Engine.h>

int main()
{
    Window win(1280, 720, 60);
    Engine eng(&win);
    eng.Start();
}