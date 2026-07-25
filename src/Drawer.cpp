#include <glad/glad.h>
#include <Drawer.h>
#include <Window.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <Shader.h>
#include <cmath>
#include <string>
#include <Defs.h>
#include <GLFW/glfw3.h>
#include <Vector.h>


extern float distance_ratio;
extern int n_obj;

Drawer::Drawer() : window(nullptr), 
    VBO(0),
    VAO(0),
    EBO(EBO)
{
    lines.reserve(1000000);
    UpdateScreenSize();
    UpdateCamera();
}

Drawer::Drawer(Window* window, std::vector<Shader*> shaders) :
    window(window), 
    shaders(shaders)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &DEBUG_VBO);
    glGenBuffers(1, &EBO);

    UpdateScreenSize();
    UpdateCamera();
    camera.cameraPos.z = 1525.0f;
    model = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, n_obj * 3* sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, DEBUG_VBO);
    glBufferData(GL_ARRAY_BUFFER, n_obj * 4 * 6 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Drawer::DrawCrosses(std::vector <Vec> pos, Color color) {
    for (size_t i = 0; i < pos.size(); i++) {
        DrawCross2D({pos[i].x, pos[i].y}, color);
    }
}

void Drawer::DrawCross2D(Vec pos, Color color) {
    float size = camera.cameraPos.z / 100;;

    DrawLine({ pos.x - size, pos.y - size}, { pos.x + size, pos.y + size }, color);
    DrawLine({ pos.x + size, pos.y - size}, { pos.x - size, pos.y + size }, color);
}


Drawer::~Drawer()
{
}

void Drawer::DrawArrow(Vec origin, Vec end, Color color) {
    DrawLine(origin, end, color);
    Vec diff = origin - end;
    float size = 2;
    float angle = atan2(diff.y, diff.x);
    float pi_4 = M_PI_4;
    DrawLine({ end.x + size * cos(angle - pi_4), end.y + size * sin(angle - pi_4) }, { end.x, end.y }, color);
    DrawLine({ end.x - size * cos(angle - 3*pi_4), end.y - size * sin(angle - 3*pi_4) }, { end.x, end.y }, color);
}

void Drawer::DrawLines(std::vector <Line>& lines) {
    Shader* shader = shaders[Default];
        
    shader->use();
    ColorA color_shader = { 0, 0, 0, 0 };
    SendColorA(shader, color_shader);
    SendMatrix(shader, "model", model);
    SendMatrix(shader, "projection", projection);
    SendMatrix(shader, "view", view);
    SendVec3f(shader, "centerPos", 0.0, 0.0, 0.0);
    glBindVertexArray(VAO);
    // Charge les vertices dans le VBO et dessine le quad 
    glBindBuffer(GL_ARRAY_BUFFER, DEBUG_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(Line), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        lines.size()* sizeof(Line),
        lines.data()
    );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDrawArrays(GL_LINES, 0, lines.size()*2);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //printf("%d lines drawn \n", lines.size());
    lines.clear();
    shader->stopUse();
}

void Drawer::DrawLines(std::vector<Line>& lines, Color color)
{
    for (size_t i = 0; i < lines.size(); i++) {
        DrawLine(lines[i].v1.pos, lines[i].v2.pos, color);
    }
}
void Drawer::DrawLine(Vec origin, Vec end, Color color)
{
    DrawLine(origin, end, ColorA{ color.r, color.g, color.b, 255 });
}
void Drawer::DrawLine(Vec origin, Vec end, ColorA color)
{
    lines.emplace_back(origin, end, color);
}

void Drawer::DrawAxis() {
    float size = camera.cameraPos.z;
    //Axe Y
    DrawLine(Vec{ 0.0, -10000 * size *distance_ratio }, Vec{ 0.0, 10000 * size * distance_ratio }, Color{ 255, 255, 255 }); //Ne s'adapte pas bien à la taille de l'écran
    //Axe X
    DrawLine(Vec{ -10000 * size * distance_ratio, 0.0 }, Vec{ 10000 * size * distance_ratio, 0.0 }, Color{ 255, 255, 255 });
}

void Drawer::DrawRectangle(Vec pos, Vec size, ColorA color) {
    Shader* shader = shaders[Default];
    shader->use();
    ColorA color_shader = { 0, 0, 0, 0 };
    SendColorA(shader, color_shader);
    SendVec3f(shader, "centerPos", pos.x, pos.y, 0.0);
    SendMatrix(shader, "projection", projection);
    SendMatrix(shader, "view", view);
    SendMatrix(shader, "model", model);

    glBindVertexArray(VAO);

    float h = size.x * 0.5f;
    float w = size.y * 0.5f;

    // 2 triangles formant un rectangle
    Vertex vertices[] = {
        // Triangle 1
        { {-w, -h}, 0.0f, {color.r, color.g, color.b, color.a}},
        { {w, -h}, 0.0f, {color.r, color.g, color.b, color.a }},
        { {w, h}, 0.0f, {color.r, color.g, color.b, color.a} },

         // Triangle 2
         { {-w, -h}, 0.0f, {color.r, color.g, color.b, color.a} },
         { {w,  h}, 0.0f, {color.r, color.g, color.b, color.a} },
         { {-w, h}, 0.0f, {color.r, color.g, color.b, color.a} },
    };

    glBindBuffer(GL_ARRAY_BUFFER, DEBUG_VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_DYNAMIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        0,              // location
        3,              // vec3
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
    );
    glVertexAttribPointer(
        1,              // location
        4,              // vec4
        GL_UNSIGNED_BYTE,
        GL_TRUE,
        sizeof(Vertex),
        (void*)(offsetof(Vertex, color))
    );
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Dessin
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDepthMask(GL_TRUE);

    // Cleanup
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader->stopUse();
}


void Drawer::UpdateScreenSize()
{
    if (window->width != 0 && window->height != 0) {
        projection = glm::perspective(glm::radians(camera.fov), (float)window->width / window->height, 0.1f, 4.0f * powf(10, 30));
    }
}

void Drawer::UpdateCamera() {
    view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
}

void Drawer::MoveCamera(Camera newCamera) {
    camera = newCamera;
}


void Drawer::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.fov -= (float)yoffset;  // yoffset > 0 est le scroll vers le haut (zoom en avant)

    // Bloque le fov entre 1 et 90 pour éviter les gros zoom
    if (camera.fov < 1.0f) camera.fov = 1.0f;
    if (camera.fov > 90.0f) camera.fov = 90.0f;
}

void Drawer::SendMatrix(Shader* shader, std::string name, glm::mat4 matrix)
{
    // Active la matrice dans le shader
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name.data()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Drawer::SendProjectionMatrix(Shader* shader)
{
    // Active la matrice de projection
    SendMatrix(shader, "projection", projection);
}

void Drawer::SendColor(Shader* shader, Color color)
{
    SendColorA(shader, ColorA(color, 255));
}

void Drawer::SendColorA(Shader* shader, ColorA color)
{
    // Envoie la couleur au shader
    glUniform4f(glGetUniformLocation(shader->ID, "color"), color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a/255.0);
}

void Drawer::SendVec4f(Shader* shader, std::string name, float x, float y, float z, float w)
{
    // Envoie un vec4 de float au shader
    glUniform4f(glGetUniformLocation(shader->ID, name.data()), x, y, z, w);
}

void Drawer::SendVec3f(Shader* shader, std::string name, float x, float y, float z)
{
    // Envoie un vec3 de float au shader
    glUniform3f(glGetUniformLocation(shader->ID, name.data()), x, y, z);
}

void Drawer::SendFloat(Shader* shader, std::string name, float x)
{
    // Envoie un float au shader
    glUniform1f(glGetUniformLocation(shader->ID, name.data()), x);
}

