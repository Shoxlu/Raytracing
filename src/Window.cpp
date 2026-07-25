#include "Window.h"
#include <Windows.h>
#include <cassert>

//Fonction utilitaire appel�e � chaque fois que la fen�tre change de taille.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


Window::Window(): fps(0), glfwWindow(nullptr), width(0), height(0)
{
}

Window::Window(double w, double h, double fps): fps(fps), width(w), height(h)
{
    Init();
    assert(glfwWindow != nullptr);
}

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cerr << "[OpenGL Debug] "
        << "Type: " << type << ", Severity: " << severity << "\n"
        << "Message: " << message << "\n" << std::endl;
}

void Window::Init() 
{
    //Cr�e la fen�tre glfw
    glfwInit();
    glfwWindow = glfwCreateWindow(width, height, "Raytracing", NULL, NULL);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    //Gestion des erreurs
    if (glfwWindow == nullptr)
    {
        printf("Echec de la cr�ation de la fen�tre GLFW: %lx \n", GetLastError());
        glfwTerminate();
        return;
    }
    //Fixe la fen�tre cr�e comme �tant le contexte actuelle
    glfwMakeContextCurrent(glfwWindow);
    //Charge la biblioth�que glad.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }
    // Fixe la couleur de rafraichissement. Noire ici.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    printf("%s\n", glGetString(GL_VERSION));
    printf("%s\n", glGetString(GL_VENDOR));
    printf("%s\n", glGetString(GL_RENDERER));
    printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // appels synchrones (plus s�r en debug)
    glDebugMessageCallback(MessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif // !NDEBUG



}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(glfwWindow);
}
void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::UpdateWindow()
{
    glfwGetWindowSize(glfwWindow, &width, &height);
    // Echange les m�moires tampons graphiques. (Actualise l'�cran)
    glfwSwapBuffers(glfwWindow);
}

Window::~Window()
{
    glfwTerminate();
    //free(glfwWindow); // Pas tr�s s�r
}


//Remplit la fen�tre avec une couleur.
//void Window::Fill(int color[3]) {
//    //self.display.fill([color[0], color[1], color[2]])
//}
    