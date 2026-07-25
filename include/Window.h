#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


/*
Classe de la fen�tre d'application.
D�sign�e pour avoir le moins d'int�raction avec les commandes bas niveau de glfw/glad dans les autres objets.
Attributs:
- glfwwindow: GLFWWindow* -> fen�tre d'application glfw
- fps: double -> nombre d'image par seconde vis�
- width: int -> largeur de la fen�tre
- height: int -> hauteur de la fen�tre
*/
class Window {
public:
    Window();
    Window(double w, double h, double fps);
    ~Window();
    //V�rifie si l'utilisateur a ferm� la fen�tre
    bool ShouldClose();
    //Actualise les �v�nements d'application
    void PollEvents();
    //Rafraichit la fen�tre
    void UpdateWindow();
    GLFWwindow* glfwWindow;
    int width;
    int height;
    double fps;
private:
    //Initialise une fen�tre GLFW
    void Init();
};