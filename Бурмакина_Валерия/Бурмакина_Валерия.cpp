// Бурмакина_Валерия.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define GLEW_DLL
#define GLFW_DLL

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "ShaderLoader.h"

GLfloat points[] =
                    {
                       -0.5f,  0.5f, 0.0f, 
                        0.5f,  0.5f, 0.0f, 
                        0.5f, -0.5f, 0.0f, 
                        -0.5f, -0.5f, 0.0f  
                    };

GLuint index[] =
                    { 
                        0, 1, 2, 
                        2, 3, 0
                    };

int main() {
    setlocale(LC_ALL, "Russian");
    printf("Лабораторная 2, Бурмакина Валерия!\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "Mainwindow", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5, 0.5, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float Red = abs(sin(timeValue));

        shader.use();
        shader.setUniform("ourColour", Red, 1.0f, 0.5f, 0.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

