#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Init.h"
#include "ShaderLoader.h"
#include "Matrix.h"
#include "ObjLoader.h"

int main(void)
{
    GLFWwindow *window;
    GLuint program;
    model model;
    GLuint mvp;

    float *mat_proj, *mat_view, *mat_model;
    float *mat_mvp;
    float *mat_tmp;

    GLuint position_buffer;

    GLuint vertex_array;

    const GLuint position_location = 0;
    const GLuint position_bindindex = 0;

    window = init(640, 480, "Step 03");

    program = load_shader("Vertex.glsl", "Fragment.glsl");

    load_obj(&model, "cube.obj");

    mat_proj = alloc_matrix();
    set_perspective_matrix(mat_proj,
        45.0, 640.0f / 480.0f, 0.1f, 100.0f);

    mat_view = alloc_matrix();
    set_lookat_matrix(mat_view,
        4.0f, 3.0f, -3.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    mat_model = alloc_matrix();
    set_identity_matrix(mat_model);

    mat_tmp = alloc_matrix();
    multiply_matrix(mat_tmp, mat_proj, mat_view);

    mat_mvp = alloc_matrix();
    multiply_matrix(mat_mvp, mat_tmp, mat_model);

    free_matrix(mat_proj);
    free_matrix(mat_view);
    free_matrix(mat_model);
    free_matrix(mat_tmp);

    mvp = glGetUniformLocation(program, "mvp");
    glUniformMatrix4fv(mvp, 1, GL_FALSE, mat_mvp);

    glCreateBuffers(1, &position_buffer);
    glNamedBufferData(position_buffer,
        sizeof(float) * model.num_vertices,
        model.vertices,
        GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vertex_array);

    glEnableVertexArrayAttrib(
        vertex_array, position_location);
    glVertexArrayAttribFormat(
        vertex_array, position_location,
        3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(
        vertex_array, position_location,
        position_bindindex);
    glVertexArrayVertexBuffer(
        vertex_array, position_bindindex,
        position_buffer, 0, sizeof(GLfloat) * 3);

    glClearColor(0.6, 0.8, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, model.num_vertices / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free_matrix(mat_mvp);

    glfwTerminate();

    return EXIT_SUCCESS;
}
