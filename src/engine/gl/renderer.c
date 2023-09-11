#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "starengine/segl.h"
#include "starengine/models.h"
#include "cglm/cglm.h"

float lastX = 400;
float lastY = 400;
float yaw = -90.0f;
float pitch = 0.0f;

vec3 camDirection;
vec3 camGoFront = {0.0f, 0.0f, -1000.0f};

bool firstMouse = true;

void mouse_callback(GLFWwindow *win, double xposIn, double yposIn)
{
    double xpos = xposIn;
    double ypos = yposIn;

    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    double sensitivity = 0.001f;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;


    if(pitch > 89.0f)
        pitch = 89.0f;

    if(pitch < -89.0f)
        pitch = -89.0f;

    camDirection[0] = (cos(glm_rad(yaw))) * cos(glm_rad(pitch));
    camDirection[1] = (sin(glm_rad(pitch)));
    camDirection[2] = (sin(glm_rad(yaw)) * cos(glm_rad(pitch)));
    glm_normalize_to(camDirection, &camGoFront);



}

static inline void *decompress(MD2Model model, float *verts)
{
    vec3 decompressed;
    MD2Vertex vert;
    MD2Frame frame;
    uint32_t numVerts;
    uint32_t cursor = 0;

    numVerts = model.hdr.numVerts;
    frame = model.frames[0];

    for(uint32_t i = 0; i < numVerts; i++)
    {
        vert = frame.vertices[i];

        verts[cursor] = (frame.scale[0] * vert.v[0] + frame.translate[0]);
        verts[cursor + 1] = (frame.scale[1] * vert.v[1] + frame.translate[1]);
        verts[cursor + 2] = (frame.scale[2] * vert.v[2] + frame.translate[2]);
        /*verts[cursor + 3] = anorms[vert.index][0];
        verts[cursor + 4] = anorms[vert.index][1];
        verts[cursor + 5] = anorms[vert.index][2];*/

        //decompressed[j] = (frame.scale[j] * vert.vert[j] + frame.translate[j]);
  
        //cursor +=6;
    }

    return;
}

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
    float *vertBuffer;
    float camSpeed = 20.5f;
    float currFrame;
    float lastFrame;
    float deltaTime;

    MD2Model *model = malloc(sizeof(MD2Model));
    MDVertexBuffer("./res/dolphin.md2", model);

    vertBuffer = malloc(model->hdr.numVerts * (sizeof(float) * 3));
    decompress(*model, vertBuffer);

    result = initShaders();

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(2, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MD2Vertex) * model->hdr.numVerts, model->frames->vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/


    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    //mats
    mat4 view_m = GLM_MAT4_IDENTITY_INIT;
    mat4 model_m = GLM_MAT4_IDENTITY_INIT;
    mat4 projection_m;
    vec3 temp;
    vec3 center = {0.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 viewVec = {0.0f, 0.0f, -3.0f};
    vec3 camPos = {0.0f, 0.0f, 300.0f};
    vec3 camTarget = {0.0f};
    vec3 camRight;
    vec3 camUp;

    glm_vec3_sub(camPos, camTarget, temp);
    glm_normalize_to(temp, camDirection);
    glm_cross(up, camDirection, camRight);
    glm_normalize(camRight);
    glm_cross(camDirection, camRight, camUp);
    glm_lookat(camPos, center, camUp, view_m);

    //locations
    uint32_t modelLoc = glGetUniformLocation(result, "model");
    uint32_t viewLoc =  glGetUniformLocation(result, "view");
    uint32_t projectionLoc =  glGetUniformLocation(result, "projection");

    glm_translate(view_m, viewVec);
    glm_perspective(glm_rad(45.0f), 1920/1080, 0.1f, 10000.0f, projection_m);
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model_m);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view_m);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection_m);

    glEnable(GL_DEPTH_TEST);

    lastFrame = 0;
    float scalefactor = 0.5f;
    while(!glfwWindowShouldClose(win))
    {

        uint32_t vertexBufferCursor = 0;
        currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        {
            glm_vec3_scale(camGoFront, (camSpeed * deltaTime), temp);
            glm_vec3_add(temp, camPos, camPos);
        }

        if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        {
            glm_vec3_scale(camGoFront, (camSpeed * deltaTime), temp);
            glm_vec3_sub(camPos, temp, camPos);
        }

        if(glfwGetKey(win, GLFW_KEY_A) ==GLFW_PRESS)
        {
            glm_cross(camGoFront, camUp, temp);
            glm_vec3_scale(temp, (camSpeed * deltaTime), temp);
            glm_vec3_sub(camPos, temp, camPos);
        }
        
        if(glfwGetKey(win, GLFW_KEY_D) ==GLFW_PRESS)
        {
            glm_cross(camGoFront, camUp, temp);
            glm_vec3_scale(temp, (camSpeed * deltaTime), temp);
            glm_vec3_add(camPos, temp, camPos);
        }

        if(glfwGetKey(win, GLFW_KEY_M) == GLFW_PRESS)
        {
            glm_scale(model_m, &scalefactor);
        }

        glm_vec3_add(camPos, camGoFront, temp);
        glm_lookat(camPos, temp, camUp, view_m);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view_m);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);
        
        for(int i = 0; i< model->hdr.numTris; i++)
        {
            glDrawArrays(GL_TRIANGLES, vertexBufferCursor, 3);
            vertexBufferCursor += 3;
        }

        glfwSwapBuffers(win);
        glfwPollEvents();
        glfwSwapInterval(1);
        

    }

    MD2Free(model);
    free(model);
    free(vertBuffer);
}