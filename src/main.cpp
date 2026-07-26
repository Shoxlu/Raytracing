#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <Window.h>
#include <Engine.h>

int main()
{
    Window win(800, 600, 60);
    Engine eng(&win);
    eng.Start();
}