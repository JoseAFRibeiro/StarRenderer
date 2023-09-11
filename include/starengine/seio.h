#ifndef SEIO_H_
#define SEIO_H_

#include <stdint.h>

typedef struct{
    uint32_t numverts;
    float *vertices;
}verts;

char* readfile(const char *path);
#endif 