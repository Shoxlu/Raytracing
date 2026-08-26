#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <Vector.h>

class Window;

// Object de Camera
/*
cameraPos : vec3 ->position de la camera
cameraFront : vec3 -> Pour avancer/reculer la camera
cameraUp: vec3 -> Pour monter/descendre la camera
cameraSpeed: float -> vitesse de la camera
fov: float -> "field of view", contrôle l'angle du champ de vision
*/
struct Camera {
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 75.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float cameraSpeed = 1.0f;
	float fov = 45.0;
};