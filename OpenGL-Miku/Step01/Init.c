#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "init.h"

/* GLFWデバッグ用コールバック */
void glfw_error_callback(int error, const char *message);

/* OpenGLデバッグ用コールバック関数 */
void APIENTRY opengl_debug_callback(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar *message, const void *param);

/* デバッグsourceを文字列に変換 */
const char *debug_source_to_string(GLenum source);

/* デバッグtypeを文字列に変換 */
const char *debug_type_to_string(GLenum type);

/* デバッグseverityを文字列に変換 */
const char *debug_severity_to_string(GLenum severity);

/*==============================*
** 初期化処理
**==============================*/
GLFWwindow *init(int width, int height, const char *title)
{
    GLFWwindow *window;
    GLenum ret_code;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window) {
        fprintf(stderr, "Failed to create window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    ret_code = glewInit();
    if (ret_code != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW.\n");
        fprintf(stderr, "%s\n", glewGetErrorString(ret_code));
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(glfw_error_callback);

    glDebugMessageCallback(opengl_debug_callback, NULL);
    glDebugMessageControl(
        GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

    return window;
}

/*------------------------------*
** GLFWデバッグ用コールバック
**------------------------------*/
void glfw_error_callback(int error, const char *message)
{
    fprintf(stderr, "GLFW: %s\n", message);
}

/*------------------------------*
** OpenGLデバッグ用コールバック関数
**------------------------------*/
void APIENTRY opengl_debug_callback(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar *message, const void *param)
{
    const char *source_str = debug_source_to_string(source);
    const char *type_str = debug_type_to_string(type);
    const char *severity_str = debug_severity_to_string(severity);

    fprintf(stderr, "%s:%s[%s](%d): %s\n",
        source_str, type_str, severity_str, id, message);
}

/*------------------------------*
** デバッグsourceを文字列に変換
**------------------------------*/
const char *debug_source_to_string(GLenum source)
{
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        return "OpenGL";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "Window system";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "Third party";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "Application";
    case GL_DEBUG_SOURCE_OTHER:
        return "Other";
    default:
        return "Unknown";
    }
}

/*------------------------------*
** デバッグtypeを文字列に変換
**------------------------------*/
const char *debug_type_to_string(GLenum type)
{
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "Deprecated behavior";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "Undefined behavior";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "Performance";
    case GL_DEBUG_TYPE_MARKER:
        return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "Push group";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "Pop group";
    case GL_DEBUG_TYPE_OTHER:
        return "Other";
    default:
        return "Unknown";
    }
}

/*------------------------------*
** デバッグseverityを文字列に変換
**------------------------------*/
const char *debug_severity_to_string(GLenum severity)
{
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        return "High";
    case GL_DEBUG_SEVERITY_MEDIUM:
        return "Medium";
    case GL_DEBUG_SEVERITY_LOW:
        return "Low";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "Notification";
    default:
        return "Unknown";
    }
}
