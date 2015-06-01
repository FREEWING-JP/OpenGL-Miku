#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Init.h"
#include "ShaderLoader.h"

int main(void)
{
    GLFWwindow *window;
    GLuint program;

    GLuint position_buffer;
    GLfloat position_data[] = {
        0.0f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    GLuint color_buffer;
    GLfloat color_data[] = {
        0.6f, 0.2f, 0.2f,
        0.2f, 0.6f, 0.2f,
        0.2f, 0.2f, 0.6f
    };

    GLuint vertex_array;

    const GLuint position_location = 0;
    const GLuint position_bindindex = 0;

    const GLuint color_location = 1;
    const GLuint color_bindindex = 1;
    
    window = init(640, 480, "Step 02");

    program = load_shader("Vertex.glsl", "Fragment.glsl");

    glCreateBuffers(1, &position_buffer);
    glNamedBufferData(position_buffer,
        sizeof(position_data), position_data,
        GL_STATIC_DRAW);

    glCreateBuffers(1, &color_buffer);
    glNamedBufferData(color_buffer,
        sizeof(color_data), color_data,
        GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vertex_array);

    glEnableVertexArrayAttrib(
        vertex_array, position_location);
    glVertexArrayAttribFormat(
        vertex_array, position_location, 
        2, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(
        vertex_array, position_location,
        position_bindindex);
    glVertexArrayVertexBuffer(
        vertex_array, position_bindindex,
        position_buffer, 0, sizeof(GLfloat) * 2);

    glEnableVertexArrayAttrib(
        vertex_array, color_location);
    glVertexArrayAttribFormat(
        vertex_array, color_location,
        3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(
        vertex_array, color_location,
        color_bindindex);
    glVertexArrayVertexBuffer(
        vertex_array, color_bindindex,
        color_buffer, 0, sizeof(GLfloat) * 3);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.6, 0.8, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(8.0);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
