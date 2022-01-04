#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"

// Screen size
#define DEFAULT_MONITOR_WIDTH 720
#define DEFAULT_MONITOR_HEIGHT 480

void renderRectangle();

int main()
{
    // glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test window", glfwGetPrimaryMonitor(), NULL);
    GLFWwindow* window = glfwCreateWindow(DEFAULT_MONITOR_WIDTH, DEFAULT_MONITOR_HEIGHT, "Test window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Final preparation
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);


    Shader fractalShader("Shaders\\FractalFragShader.vert", "Shaders\\FractalFragShader.frag"); 
    fractalShader.activateShader();
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        fractalShader.activateShader();
        fractalShader.setFloat("time", glfwGetTime());
        renderRectangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int rectVAO = 0;
unsigned int rectVBO = 0;
void renderRectangle() {
    if (rectVAO == 0) {
        float vertices[] = {
            -1.0, -1.0, 0.0f,
            1.0, -1.0, 0.0f,
            -1.0, 1.0, 0.0f,
            1.0, 1.0, 0.0f
        };

        glGenVertexArrays(1, &rectVAO);
        glGenBuffers(1, &rectVBO);

        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(rectVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // render rectangle
    glBindVertexArray(rectVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}