#include <VerticesManager.h>
#include <Defs.h>

// Fonction qui g�n�re les points d'un Line
std::vector<float> VerticesManager::GenerateLine(Vec origin, Vec end) {
    std::vector<float> vertices;
    vertices.push_back(origin.x); 
    vertices.push_back(origin.y);
    vertices.push_back(0.0);
    vertices.push_back(end.x);
    vertices.push_back(end.y);
    vertices.push_back(0.0);
    return vertices;
}


std::vector<float> VerticesManager::GenerateRectTex(float cx, float cy, float rx, float ry) {

    std::vector<float> vertices = {
            // positions                      // texture coords
            cx + rx / 2, cy + ry / 2, 0.0f,   1.0f, 1.0f,   // top right
            cx + rx / 2, cy - ry / 2, 0.0f,   1.0f, 0.0f,   // bottom right
            cx - rx / 2, cy - ry / 2, 0.0f,   0.0f, 0.0f,   // bottom left
            cx + rx / 2, cy + ry / 2, 0.0f,   1.0f, 1.0f,   // top right
            cx - rx / 2, cy + ry / 2, 0.0f,   0.0f, 1.0f,   // top left 
            cx - rx / 2, cy - ry / 2, 0.0f,   0.0f, 0.0f,   // bottom left
        };

    //vertices.push_back(cx + rx / 2); // Droite haut x
    //vertices.push_back(cy - ry / 2); // Droite haut y
    //vertices.push_back(0.0f); // Droite haut z
    //vertices.push_back(1.0f); // Droite haut z
    //vertices.push_back(1.0f); // Droite haut z

    //vertices.push_back(cx + rx / 2); // Droite bas x
    //vertices.push_back(cy + ry / 2); // Droite bas y
    //vertices.push_back(1.0f); // Gauche bas z
    //vertices.push_back(0.0f); // Gauche bas z

    //vertices.push_back(cx - rx / 2); // Gauche bas x
    //vertices.push_back(cy + ry / 2); // Gauche bas y
    //vertices.push_back(0.0f); // Gauche bas z
    //vertices.push_back(0.0f); // Gauche bas z
    //vertices.push_back(0.0f); // Gauche bas z

    //vertices.push_back(cx - rx / 2); // Gauche bas x
    //vertices.push_back(cy + ry / 2); // Gauche bas y
    //vertices.push_back(0.0f); // Gauche bas z
    //vertices.push_back(0.0f); // Gauche bas z
    //vertices.push_back(0.0f); // Gauche bas z
    //

    //vertices.push_back(cx - rx / 2); // Gauche haut x
    //vertices.push_back(cy - ry / 2); // Gauche haut y
    //vertices.push_back(0.0f); // Gauche haut z
    //vertices.push_back(0.0f); // Gauche haut z
    //vertices.push_back(1.0f); // Gauche haut z


    //vertices.push_back(cx + rx / 2); // Droite haut x
    //vertices.push_back(cy - ry / 2); // Droite haut y
    //vertices.push_back(0.0f); // Droite haut z
    //vertices.push_back(1.0f); // Droite haut z
    //vertices.push_back(1.0f); // Droite haut z


    return vertices;
}
