#include "GraEngine.h"
#include "Object.h"
#include "QuadTree.h"
#include <glad/glad.h>
extern float distance_ratio;

std::vector < std::string> computeShaderFiles = { "ComputeShader.glsl", "UpdateObjects.glsl"};

GraEngine::GraEngine(): window(nullptr)
{
    Init();
}

GraEngine::~GraEngine()
{
    for (int i = 0; i < shaders.size(); i++) {
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
    shaders[Particles] = (new Shader("ParticlesVertex.glsl", "DefaultFragment.glsl"));
    shaders[Default] = (new Shader("DefaultVertex.glsl", "DefaultFragment.glsl"));
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    drawer = new Drawer(window, shaders, VBO, VAO, EBO);
}


void GraEngine::Update(std::vector<Object>& objects)
{
    drawer->UpdateCamera();
    drawer->DrawPoints(objects.size());
    //drawer->DrawAxis();
}

void GraEngine::Update2(std::vector<Object>&objects)
{
    drawer->UpdateCamera();
    drawer->DrawPoints(objects.size());
    //drawer->DrawAxis();
}

void GraEngine::Swap() {
    window->UpdateWindow();
    drawer->UpdateScreenSize();
}


