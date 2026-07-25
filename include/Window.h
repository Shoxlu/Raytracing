#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


/*
Classe de la fenêtre d'application.
Désignée pour avoir le moins d'intéraction avec les commandes bas niveau de glfw/glad dans les autres objets.
Attributs:
- glfwwindow: GLFWWindow* -> fenêtre d'application glfw
- fps: double -> nombre d'image par seconde visé
- width: int -> largeur de la fenêtre
- height: int -> hauteur de la fenêtre
*/
class Window {
public:
    Window();
    Window(double w, double h, double fps);
    ~Window();
    //Vérifie si l'utilisateur a fermé la fenêtre
    bool ShouldClose();
    //Actualise les évènements d'application
    void PollEvents();
    //Rafraichit la fenêtre
    void UpdateWindow();
    GLFWwindow* glfwWindow;
    double fps;
    int width;
    int height;
private:
    //Initialise une fenêtre GLFW
    void Init();
};