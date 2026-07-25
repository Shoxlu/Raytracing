#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main()
{
    if (!glfwInit())
    {
        std::cout << "Initialisation glfw échouée";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Impossible de charger OpenGL\n";
        return -1;
    }
    
}