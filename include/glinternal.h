#ifndef GLINTERNAL_H_
#define GLINTERNAL_H_

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void error_callback(GLint error, const char *message);
void framebuffersize_callback(GLFWwindow *win, GLint widht, GLint height);
void mouse_callback(GLFWwindow *win, double xposIn, double yposIn);
void keypressed_callback(GLFWwindow *win, int key, int scancode, int action, int mods);



#endif 