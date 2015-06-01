#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Init.h"
#include "ShaderLoader.h"
#include "Matrix.h"
#include "ObjLoader.h"
#include "BmpLoader.h"

int main(void)
{
    GLFWwindow *window;
    GLuint program;
    model model;
    GLuint texture, texl;
    GLuint mv_matrix, normal_matrix, mvp;
    int i, j;

    float *mat_proj, *mat_view, *mat_model;
    float *mat_mv, *mat_mvp;
    float mat_norm[9];

    GLuint position_buffer;
    GLuint normal_buffer;
    GLuint uv_buffer;

    GLuint vertex_array;

    const GLuint position_location = 0;
    const GLuint position_bindindex = 0;

    const GLuint normal_location = 1;
    const GLuint normal_bindindex = 1;

    const GLuint uv_location = 2;
    const GLuint uv_bindindex = 2;

    window = init(640, 480, "Step 04");

    program = load_shader("Vertex.glsl", "Fragment.glsl");

    load_obj(&model, "miku.obj");

    mat_proj = alloc_matrix();
    set_perspective_matrix(mat_proj,
        45.0, 640.0f / 480.0f, 0.1f, 100.0f);

    mat_view = alloc_matrix();
    set_lookat_matrix(mat_view,
        1.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    mat_model = alloc_matrix();
    set_identity_matrix(mat_model);

    mat_mv = alloc_matrix();
    multiply_matrix(mat_mv, mat_view, mat_model);

    mat_mvp = alloc_matrix();
    multiply_matrix(mat_mvp, mat_proj, mat_mv);

    free_matrix(mat_proj);
    free_matrix(mat_view);
    free_matrix(mat_model);

    mv_matrix = glGetUniformLocation(program, "mv_matrix");
    glUniformMatrix4fv(mv_matrix, 1, GL_FALSE, mat_mv);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mat_norm[i * 3 + j] = mat_mv[i * 4 + j];
        }
    }
    normal_matrix = glGetUniformLocation(program, "normal_matrix");
    glUniformMatrix3fv(normal_matrix, 1, GL_FALSE, mat_norm);

    mvp = glGetUniformLocation(program, "mvp");
    glUniformMatrix4fv(mvp, 1, GL_FALSE, mat_mvp);

    texture = load_bmp("miku.bmp");
    texl = glGetUniformLocation(program, "texl");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texl, 0);

    glCreateBuffers(1, &position_buffer);
    glNamedBufferData(position_buffer,
        sizeof(float) * model.num_vertices,
        model.vertices,
        GL_STATIC_DRAW);

    glCreateBuffers(1, &normal_buffer);
    glNamedBufferData(normal_buffer,
        sizeof(float) * model.num_normals,
        model.normals,
        GL_STATIC_DRAW);

    glCreateBuffers(1, &uv_buffer);
    glNamedBufferData(uv_buffer,
        sizeof(float) * model.num_uvs,
        model.uvs,
        GL_STATIC_DRAW);

    printf("%d %d %d\n", model.num_vertices, model.num_normals, model.num_uvs);

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

    glEnableVertexArrayAttrib(
        vertex_array, normal_location);
    glVertexArrayAttribFormat(
        vertex_array, normal_location,
        3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(
        vertex_array, normal_location,
        normal_bindindex);
    glVertexArrayVertexBuffer(
        vertex_array, normal_bindindex,
        normal_buffer, 0, sizeof(GLfloat) * 3);

    glEnableVertexArrayAttrib(
        vertex_array, uv_location);
    glVertexArrayAttribFormat(
        vertex_array, uv_location,
        2, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(
        vertex_array, uv_location,
        uv_bindindex);
    glVertexArrayVertexBuffer(
        vertex_array, uv_bindindex,
        uv_buffer, 0, sizeof(GLfloat) * 2);

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

    free_matrix(mat_mv);
    free_matrix(mat_mvp);

    glfwTerminate();

    return EXIT_SUCCESS;
}
