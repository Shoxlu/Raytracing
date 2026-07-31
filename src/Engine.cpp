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
    Light l{{200, 0, 40}, {255, 255, 255}};
    Light l2{{-100, 0, 40}, {0, 0, 255}};
    Light l3{{0, 0, 10}, {0, 255, 0}};
    Ball b({50, 0, 0}, {255, 0, 255, 255}, 0.5, 0.0, 10.0);
    Ball b2({0, 0, -100}, {255, 255, 255, 255}, 0.8, 1.0, 100.0);
    scene.objects.push_back(b);
    scene.objects.push_back(b2);
    // scene.objects.push_back(b3);
    scene.lights.push_back(l);
    scene.lights.push_back(l2);
    //scene.lights.push_back(l3);
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
    graEngine->UpdateCamera();
    //Actualisation des données
    rayTracer->Render(image, scene);
}

void Engine::UpdateGraphic() {
    graEngine->Update(image);
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
    double theta = 0;
    while (IsRunning())
    { 
        scene.objects[0].pos.x = cos(theta)*50;
        UpdateLogic();
        UpdateGraphic();
        real_time = glfwGetTime();
        while ( real_time - real_time_before <= 1.0 / window->fps) {
            real_time = glfwGetTime();
        }
        fps = 1.0 / (real_time - real_time_before);
        real_time_before = glfwGetTime();
        frame_counter = (frame_counter + 1) % INT32_MAX % nfps;
        last_fps[frame_counter] = round(fps);
        printf("%f\n", last_fps[frame_counter]);
        theta+= rad(2);
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
