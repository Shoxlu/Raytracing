#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Object.h"
#include "Drawer.h"
#include "Window.h"
#include "PhyEngine.h"
#include "Vector.h"
#include "Shader.h"





/*
Classe du moteur graphique.
Contient des méthodes pour afficher les objets physiques.
Attributs :
- window : Window* -> pointeur vers la classe de la fenêtre d'application (Pas considéré comme un pointeur en python)
- pShader: Shader* -> Pointeur vers un objet Shader. Peut-être à changer ?
- drawer: Drawer* -> Utilitaire de dessin.
- VBO: entier non signé(GLuint) -> id du buffer d'objet pour le rendu
- VAO: entier non signé(GLuint) -> id du buffer "array" pour le rendu
- EBO: entier non signé(GLuint) -> id du buffer d'éléments pour le rendu
- pointObjects: tableau de Points -> contient tous les objets "PointObj" ;
- verticesPoints: tableau de vertices(float) -> contient toutes les positions/couleurs de chaque point;
- shaders: tableau -> contient tous les shaders chargés
*/
class GraEngine {
public:
    GraEngine();
    GraEngine(Window* window);
    ~GraEngine();
    //Initialise le moteur graphique.
    void Init();
    //Actualise la fenêtre d'application et dessine toutes les images.
    void Update(std::vector<Object>& objects);
    void Update2(std::vector<Object>& objects);
    //Echange les buffers d'affichage (actualise la surface de dessin)
    void Swap();

    std::vector<Shader*> shaders;
    Drawer* drawer;
private:    
    Window* window;
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    
};

    
