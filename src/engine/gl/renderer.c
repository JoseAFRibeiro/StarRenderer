#include <stdlib.h>
#include <stdint.h>
#include "starengine/segl.h"

float triangle[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f
};

static inline GLint initShaders(void)
{
    int result;
    GLint frag, vert, program;

    frag = compileShader("./res/fragment.frag", GL_FRAGMENT_SHADER);
    vert = compileShader("./res/vertex.vert", GL_VERTEX_SHADER);

    program = linkShaderProgram(frag, vert);

    if(program == -1)
        return -1;

    glUseProgram(program);
    return program;
}

void render(GLFWwindow *win)
{
    GLint VBO, VAO, EBO;
    GLint result = 0;

    result = initShaders();

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    while(!glfwWindowShouldClose(win))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0, 3);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}