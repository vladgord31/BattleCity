#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

void framebuffer_size_callback(GLFWwindow *pWindow, int width, int height);
void processInput(GLFWwindow *pWindow);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLfloat vertices[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *pWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);
    glfwSetWindowSizeCallback(pWindow, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 0, 0, 0);

    {
        ResourceManager resourceManager(argv[0]);

        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }

        GLuint verticesVBO = 0;
        glGenBuffers(1, &verticesVBO);
        glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLuint colorsVBO = 0;
        glGenBuffers(1, &colorsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        while (!glfwWindowShouldClose(pWindow))
        {
            processInput(pWindow);

            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
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