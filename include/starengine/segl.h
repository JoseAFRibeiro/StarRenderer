#ifndef SEGL_H_
#define SEGL_H_

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "starengine/models.h"
GLFWwindow *initGL(void);
GLint compileShader(const char *path, GLenum shaderType);
GLint linkShaderProgram(GLint frag, GLint vert);
void render(GLFWwindow *win);
void MDVertexBuffer(const char *path, MD2Model *model);
#endif 