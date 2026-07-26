#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <Defs.h>
#include <Shader.h>
#include <Vector.h>
#include <Camera.h>


class Window;



/*
Utilitaire pour dessiner sur la fenêtre d'application.
Attributs:
- window: Window* -> pointeur vers la fenêtre d'application
- VBO: entier non signé(GLuint) -> id du buffer d'objet pour le rendu
- VAO: entier non signé(GLuint) -> id du buffer "array" pour le rendu
- EBO: entier non signé(GLuint) -> id du buffer d'éléments pour le rendu
- projection : matrice 4 -> matrice de projection pour projeter les coordonnées sur la fenêtre en 3D.
- model : matrice 4 -> matrice pour bouger/effectuer des rotations sur les objets
- view : matrice 4 -> matrice contrôlant le point de vue
- shaders: tableau -> contient tous les shaders chargés
- camera: Camera -> Caméra actuelle
*/

class Drawer {
public:
	Drawer();
	Drawer(Window* window, std::vector<Shader*> shaders);
	~Drawer();
	void DrawArrow(Vec origin, Vec end, Color color);
	//Met à jour la camera (la matrice view)
	void UpdateCamera();
	//Bouge la camera à une autre camera
	void MoveCamera(Camera newCamera);
	//Fonction de callback lorsque le scroll est effectué (Pertinence ici ?)
	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void DrawLines(std::vector<Line>& lines);
	//Dessine une ligne
	void DrawLine(Vec origin, Vec end, Color color);
	void DrawLine(Vec origin, Vec end, ColorA color);

	void DrawLines(std::vector <Line>& lines, Color color);
	void DrawCrosses(std::vector<Vec> lines, Color color);
	void DrawCross2D(Vec pos, Color color);

	void DrawRectangle(Vec pos, Vec size, ColorA color);

	//Desine les axes du plan 
	void DrawAxis();
	//Actualise la matrice de projection pour correspondre à la taille de fenêtre
	void UpdateScreenSize();
	Camera camera;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	std::vector<Line> lines;
private:

	//Envoie une matrice au shader
	void SendMatrix(Shader* shader, std::string name, glm::mat4 matrix);
	//Envoie la matrice de projection au shader
	void SendProjectionMatrix(Shader* shader);
	//Envoie la couleur de l'objet au shader
	void SendColor(Shader* shader, Color color);
	void SendColorA(Shader* shader, ColorA color);
	//Envoie un Vec4 au shader
	void SendVec4f(Shader* shader, std::string name, float x, float y, float z, float w);
	//Envoie un Vec3 au shader
	void SendVec3f(Shader* shader, std::string name, float x, float y, float z);
	//Envoie un float au shader
	void SendFloat(Shader* shader, std::string name, float x);

	Window* window;
	GLuint VBO;
	GLuint DEBUG_VBO;
	GLuint VAO;
	GLuint EBO;
	std::vector<Shader*> shaders;

};