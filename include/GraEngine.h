#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Drawer.h>
#include <Window.h>
#include <Vector.h>
#include <Shader.h>


class GraEngine {
public:
    GraEngine();
    GraEngine(Window* window);
    ~GraEngine();
    //Initialise le moteur graphique.
    void Init();
    //Actualise la fenêtre d'application et dessine toutes les images.
    void Update(Image& image);
    //Echange les buffers d'affichage (actualise la surface de dessin)
    void Swap();

    void UpdateCamera();

    std::vector<Shader*> shaders;
    Drawer* drawer;
private:    
    Window* window;
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    
};

    
