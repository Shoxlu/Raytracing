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
    Light l{{0, -1000000, 0}, {255, 255, 255}};
    Light l2{{0, 0, 100}, {0, 255, 255}};
    Light l3{{0, 0, 10}, {0, 255, 0}};
    Ball b({50, 0, 0}, {255, 0, 255, 255}, 0, 0.0, 5.0);
    Ball b3({-50, 0, -90}, {255, 128, 255, 255}, 0, 0.0, 5.0);
    Ball b4({50, 0, -80}, {32, 255, 0, 255}, 0, 0.0, 5.0);
    Ball b5({-50, 0, -110}, {32, 255, 0, 255}, 1.0, 1.0, 10.0);
    Ball b2({0, -20, -100}, {255, 255, 255, 255}, 1.0, 1.0, 20.0);
    scene.AddBall(b);
    scene.AddBall(b2);
    scene.AddBall(b3);
    scene.AddBall(b4);
    scene.AddBall(b5);
    scene.AddWall(Wall({0, 10, 0}, {180, 180, 180, 255}, {100000000000000.0, 1000.0}, {0, -1, 0}, 0.0, 1.0));
    //scene.AddWall(Wall({-150, 0, -50}, {255, 255, 255, 255}, {100.0, 200.0}, {1, 0, 1}, 0.9, 1.0));
    //scene.AddWall(Wall({150, 0, -50}, {255, 255, 255, 255}, {100.0, 200.0}, {-1, 0, 1}, 0.9, 1.0));
    //scene.AddWall(Wall({0, 0, 100}, {255, 255, 255, 255}, {100.0, 200.0}, {0, 0, -1}, 0.9, 1.0));
    // scene.objects.push_back(b3);
    scene.AddLight(l);
   // scene.AddLight(l2);
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
    scene.camera = graEngine->drawer->camera;
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
        scene.objects[0]->pos.x = cos(theta)*50; 
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
