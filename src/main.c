#include <stdio.h>
#include "starengine/segl.h"

int main()
{
    GLFWwindow *mainwin = initGL();
    render(mainwin);
}