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


