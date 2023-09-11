#include <stdlib.h>
#include <stdio.h>
#include "starengine/seio.h"
#include "glad/glad.h"
#include "glinternal.h"

GLuint linkShaderProgram(GLint frag, GLint vert)
{   
    char errorString[2048];
    GLsizei len = 0;
    GLuint program = 0;
    GLuint success = 0;
    
    if((frag == 0) || (vert == 0))
        return -1;

    program = glCreateProgram();
    glAttachShader(program, frag);
    glAttachShader(program, vert);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(success == GL_FALSE)
    {
        glGetProgramInfoLog(program, 2048, &len, &errorString);
        printf("Error linking: %s\n", errorString);
        glDeleteShader(frag);
        glDeleteShader(vert);
        glDeleteProgram(program);
        return -1;
    }

    glDeleteShader(frag);
    glDeleteShader(vert);

    return program;
}

GLint compileShader(const char *path, GLenum shaderType)
{
    char errorString[2048] = {0};
    uint8_t *shaderSource = NULL;
    GLuint success = 0;
    GLuint shader = 0;

    shader = glCreateShader(shaderType);
    shaderSource = readfile(path);

    if(shaderSource == NULL)
        return -1;
    
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 2048, NULL, errorString);
        printf("Shader compilation failed: %s\n", errorString );
        free(shaderSource);
        glDeleteShader(shader);
        return -1;
    }
    
    free(shaderSource);

    return shader;
}

GLFWwindow *initGL(void)
{
    GLFWwindow *win = NULL;
    glfwSetErrorCallback(error_callback);

    if(!glfwInit())
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(1920, 1080, "StarRenderer", NULL, NULL);

    if(win == NULL)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, framebuffersize_callback);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(win, mouse_callback);
    glfwSetKeyCallback(win, keypressed_callback);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 1920, 1080);
    return win;

}