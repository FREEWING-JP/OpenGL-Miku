#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Init.h"

int main(void)
{
    GLFWwindow *window;
    
    window = init(640, 480, "Step 01");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.6, 0.8, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
