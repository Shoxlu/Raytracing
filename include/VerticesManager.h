#pragma once
#include <vector>
#include "Vector.h"


class VerticesManager {
public:
	// Fonction qui g�n�re les points d'une ligne
	std::vector<float> static GenerateLine(Vec origin, Vec end);
	std::vector<float> static GenerateRectTex(float cx, float cy, float rx, float ry);
};


