#include "glinternal.h"

void error_callback(GLint error, const char *message)
{
    printf("GLFW error %d: %s\n", error, message);
    return;
}

void framebuffersize_callback(GLFWwindow *win, GLint widht, GLint height)
{
    glViewport(0,0, widht, height);
    return;
}