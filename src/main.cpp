#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <Window.h>
#include <GraEngine.h>


void ProcessInput(GLFWwindow* window, GraEngine& graEngine) {
    Camera& camera = graEngine.drawer->camera;
    int max_z = INT_MAX;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.cameraSpeed = std::max(camera.cameraSpeed + 1.0, 1.0);  // Augmente la vitesse de la camera
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.cameraSpeed = std::max(camera.cameraSpeed - 1.0, 1.0);  // Diminue la vitesse de la camera
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) //Touche A (Qwerty)
        camera.cameraPos += camera.cameraSpeed * camera.cameraFront;  // Avance
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.cameraPos -= camera.cameraSpeed * camera.cameraFront;  // Recule
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.cameraPos += camera.cameraSpeed * camera.cameraUp;  // Monte
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.cameraPos -= camera.cameraSpeed * camera.cameraUp;  // Descend
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * camera.cameraSpeed;  // Gauche
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * camera.cameraSpeed;  // Droite
    if (camera.cameraPos.z < 1)
        camera.cameraPos.z = 1;//Bloque la caméra
    if (camera.cameraPos.z > max_z)
        camera.cameraPos.z = max_z;//Bloque la caméra
        
}
int main()
{
    Window win(800, 600, 60);
    GraEngine gEng(&win);
    double time = glfwGetTime();
    while(true)
    {
        win.PollEvents();
        ProcessInput(win.glfwWindow, gEng);
        if (win.ShouldClose()) {
            break;
        }
        gEng.Update();
        while ( glfwGetTime() - time <= 1.0 / win.fps) {
            continue;
        }
    }
}