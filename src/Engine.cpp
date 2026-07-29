#include <vector>
#include <Engine.h>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <utility>
#include <GraEngine.h>
#include "GLFW/glfw3.h"
#include <RayTracing.h>
#include <Window.h>
#include <cstring>

extern float distance_ratio;
extern float theta;


Engine* engine;

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    engine->graEngine->drawer->ScrollCallback(window, xoffset, yoffset);
}


Engine::Engine() :
    window(nullptr),
    rayTracer(nullptr),
    graEngine(nullptr),
    simulationState(0),
    frame_counter(0),
    isPaused(false),
    verticesPoints(),
    current_time(0)
{

    graEngine = new GraEngine();
    memset(last_fps, 0, nfps*sizeof(double));
}

Engine::Engine(Window* win): 
    window(win),
    rayTracer(nullptr),
    graEngine(nullptr),
    simulationState(0),
    frame_counter(0),
    isPaused(false),
    current_time(0),
    verticesPoints(),
    image(win->width, win->height)
{
    memset(last_fps, 0, nfps*sizeof(double));
    graEngine = new GraEngine(win);
    graEngine->drawer->ImageToTex(image);
    glfwSetScrollCallback(win->glfwWindow, scroll_callback);
}

Engine::~Engine() {
    if(rayTracer)
        delete rayTracer;
    if(graEngine)
        delete graEngine;
}

// void Engine::AddObject(Object obj) {
//     objects.emplace_back(obj);
// }

// void Engine::AddObjects(ObjectArray objs) {
//     for (int i = 0; i < objs.size(); i++) {
//         AddObject(objs[i]);
//     }
// }

void Engine::Init() {
    simulationState = Running;

}



void Engine::Start() {
    Init();
    Run();
}

void Engine::Restart() {
    Clear();
    Start();    
}

void Engine::Clear() {

}

void Engine::UpdateWindow() {
    //Gestion des évènements pré-actualisation
    window->PollEvents();
    ProcessInput();
}

void Engine::UpdateLogic() {
    UpdateWindow();
    //Actualisation des données
    rayTracer->Render(image, scene);
}

void Engine::UpdateGraphic() {
    graEngine->UpdateCamera();
    graEngine->Update(image);
    graEngine->Swap();
}

void Engine::Reset() { 
    memset(last_fps, 0, nfps*sizeof(double));
    //Clear();
    simulationState = Running;
    frame_counter = 0;
    current_time = 0;
}

void Engine::Run() {
    double real_time = 0;
    double real_time_before = 0;
    double fps = 0;
    while (IsRunning())
    { 
        UpdateLogic();
        real_time = glfwGetTime();
        while (real_time - real_time_before <= 1.0 / window->fps) {
            real_time = glfwGetTime();
        }
        fps = 1.0 / (real_time - real_time_before);
        real_time_before = glfwGetTime();
        frame_counter = (frame_counter + 1) % INT32_MAX % nfps;
        last_fps[frame_counter] = round(fps);
        UpdateGraphic();


        //Gestion des évènements post-actualisation
        CheckSimulationEnd();
    }

    CheckSimulationRestart();
}

void Engine::CheckSimulationEnd() {
    if (window->ShouldClose()) {
        simulationState = Stopped;
    }
}

void Engine::CheckSimulationRestart() {
    if (simulationState == Restarting) {
        Restart();
    }
}

bool Engine::IsRunning() const {
    return simulationState == Running;
}


void Engine::ProcessInput() {
    graEngine->UpdateCamera();
}
