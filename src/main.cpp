#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *pWindow, int width, int height);
void processInput(GLFWwindow *pWindow);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(void)
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *pWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Battle City", NULL, NULL);
    if (!pWindow)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);

    glfwMakeContextCurrent(pWindow);
    glfwSetWindowSizeCallback(pWindow, framebuffer_size_callback);

    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(pWindow))
    {
        processInput(pWindow);

        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *pWindow)
{
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow *pWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}