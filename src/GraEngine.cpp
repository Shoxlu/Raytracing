#include "GraEngine.h"
#include <RayTracing.h>
#include <glad/glad.h>
extern float distance_ratio;

GraEngine::GraEngine(): window(nullptr)
{
    Init();
}

GraEngine::~GraEngine()
{
    for (size_t i = 0; i < shaders.size(); i++) {
        delete shaders[i];
    }

    delete drawer;
}

GraEngine::GraEngine(Window* window) : window(window)
{
    Init();
    // texture size

}

void GraEngine::Init() {    
    shaders.resize(10);
    shaders[Default] = (new Shader("DefaultVertex.glsl", "DefaultFragment.glsl"));
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    drawer = new Drawer(window, shaders);
}

void GraEngine::UpdateCamera()
{
    Camera& camera = drawer->camera;
    GLFWwindow* win = window->glfwWindow;
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.cameraSpeed = std::max(camera.cameraSpeed + 1, 1.0f);  // Augmente la vitesse de la camera
        printf("Camera speed:%f\n", camera.cameraSpeed);
    }
    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.cameraSpeed = std::max(camera.cameraSpeed - 1, 1.0f);  // Diminue la vitesse de la camera
    if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) //Touche A (Qwerty)
        camera.cameraPos += camera.cameraSpeed * camera.cameraFront;  // Avance
    if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
        camera.cameraPos -= camera.cameraSpeed * camera.cameraFront;  // Recule
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        camera.cameraPos += camera.cameraSpeed * camera.cameraUp;  // Monte
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        camera.cameraPos -= camera.cameraSpeed * camera.cameraUp;  // Descend
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * camera.cameraSpeed;  // Gauche
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * camera.cameraSpeed;  // Droite

    drawer->UpdateCamera();
}

void GraEngine::Update(Image& image)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawer->DrawImage(image);

    Swap();
}

void GraEngine::Swap() {
    window->UpdateWindow();
    drawer->UpdateScreenSize();
}


