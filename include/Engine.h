#pragma once
#include <Window.h>
#include <RayTracing.h>
#include <GraEngine.h>
#include <vector>

const int nfps = 100;

class Engine {
public:
    Engine();
    Engine(Window* win);
    ~Engine();


    void StartTests();
    //Initialisation du moteur
    void Start();
    void RestartWithMore();
    void CheckSimulationEnd();

    void CheckSimulationRestart();

    bool IsRunning() const;

    void Init();

    void Run();
    //Actualise la logique
    void UpdateLogic();
    //Actualise la logique de la fenêtre
    void UpdateWindow();
    //Actualise les éléments graphiques
    void UpdateGraphic();
    // //Ajoute un objet à la simulation
    // void AddObject(Object obj);
    // //Ajoute tous les objets de objs dans la simulation
    // void AddObjects(ObjectArray objs);
    //Vide la simulation
    void Clear();
    //Recommence la simulation
    void Restart();
    //Reinitialise des paramètres (uniquement pour le debug)
    void Reset();
    //Récupère les appuis de touches et agit en conséquence
    void ProcessInput();

    
    Window* window;
    RayTracer* rayTracer;
    GraEngine* graEngine;
    int simulationState;
    int frame_counter;
    bool isPaused;
    double last_fps[nfps];
    float current_time;
    // std::vector<Object> objects;
    std::vector<float> verticesPoints;
private:

};

enum SimulState {
    Stopped,
    Running,
    Restarting,
};
