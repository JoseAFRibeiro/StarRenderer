#include "glinternal.h"
#include <stdio.h>

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

void keypressed_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GLFW_TRUE);

    return;
}
