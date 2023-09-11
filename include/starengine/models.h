#ifndef MODELS_H_
#define MODELS_H_

#include <stdint.h>
#include "cglm/vec3.h"

#define SKIN_SIZE sizeof(char) * 64
#define TEXT_COORDS_SIZE sizeof(MD2TexCoords)
#define TRIANGLE_SIZE sizeof (MD2Tri)
#define FRAME_SIZE sizeof (MD2Frame)

//MD2
typedef struct{
    //file identifiers
    uint32_t ident;
    uint32_t version;
    
    //counts
    uint32_t skinwidth;
    uint32_t skinheight;
    uint32_t framesize;
    uint32_t numSkins;
    uint32_t numVerts;
    uint32_t numSt;
    uint32_t numTris;
    uint32_t numGlCommands;
    uint32_t numFrames;
    
    //offsets
    uint32_t offsetSkins;
    uint32_t offsetST;
    uint32_t offsetTris;
    uint32_t offsetFrames;
    uint32_t offsetGLCommands;
    uint32_t offsetEnd;
}MD2Header;

typedef struct{
    char name[64]
}MD2TexName;

typedef struct{
    uint16_t s;
    uint16_t t;
}MD2TexCoords;

typedef struct{
    vec3 vertex;
    vec3 st;
}MD2Tri;

typedef struct{
    vec3 v;
    uint8_t index;
}MD2Vertex;


typedef struct{
    vec3 scale;
    vec3 translate;
    char name[16];
    MD2Vertex *vertices;
}MD2Frame;

typedef struct{
    MD2Header hdr;

    MD2TexName *texName;
    MD2TexCoords *texCoords;
    MD2Tri *triangles;
    MD2Frame *frames;
    uint32_t *glcommands;
    uint32_t tex_id;

}MD2Model;
static float anorms[162][3] = {
{ -0.525731f,  0.000000f,  0.850651f }, 
{ -0.442863f,  0.238856f,  0.864188f }, 
{ -0.295242f,  0.000000f,  0.955423f }, 
{ -0.309017f,  0.500000f,  0.809017f }, 
{ -0.162460f,  0.262866f,  0.951056f }, 
{  0.000000f,  0.000000f,  1.000000f }, 
{  0.000000f,  0.850651f,  0.525731f }, 
{ -0.147621f,  0.716567f,  0.681718f }, 
{  0.147621f,  0.716567f,  0.681718f }, 
{  0.000000f,  0.525731f,  0.850651f }, 
{  0.309017f,  0.500000f,  0.809017f }, 
{  0.525731f,  0.000000f,  0.850651f }, 
{  0.295242f,  0.000000f,  0.955423f }, 
{  0.442863f,  0.238856f,  0.864188f }, 
{  0.162460f,  0.262866f,  0.951056f }, 
{ -0.681718f,  0.147621f,  0.716567f }, 
{ -0.809017f,  0.309017f,  0.500000f }, 
{ -0.587785f,  0.425325f,  0.688191f }, 
{ -0.850651f,  0.525731f,  0.000000f }, 
{ -0.864188f,  0.442863f,  0.238856f }, 
{ -0.716567f,  0.681718f,  0.147621f }, 
{ -0.688191f,  0.587785f,  0.425325f }, 
{ -0.500000f,  0.809017f,  0.309017f }, 
{ -0.238856f,  0.864188f,  0.442863f }, 
{ -0.425325f,  0.688191f,  0.587785f }, 
{ -0.716567f,  0.681718f, -0.147621f }, 
{ -0.500000f,  0.809017f, -0.309017f }, 
{ -0.525731f,  0.850651f,  0.000000f }, 
{  0.000000f,  0.850651f, -0.525731f }, 
{ -0.238856f,  0.864188f, -0.442863f }, 
{  0.000000f,  0.955423f, -0.295242f }, 
{ -0.262866f,  0.951056f, -0.162460f }, 
{  0.000000f,  1.000000f,  0.000000f }, 
{  0.000000f,  0.955423f,  0.295242f }, 
{ -0.262866f,  0.951056f,  0.162460f }, 
{  0.238856f,  0.864188f,  0.442863f }, 
{  0.262866f,  0.951056f,  0.162460f }, 
{  0.500000f,  0.809017f,  0.309017f }, 
{  0.238856f,  0.864188f, -0.442863f }, 
{  0.262866f,  0.951056f, -0.162460f }, 
{  0.500000f,  0.809017f, -0.309017f }, 
{  0.850651f,  0.525731f,  0.000000f }, 
{  0.716567f,  0.681718f,  0.147621f }, 
{  0.716567f,  0.681718f, -0.147621f }, 
{  0.525731f,  0.850651f,  0.000000f }, 
{  0.425325f,  0.688191f,  0.587785f }, 
{  0.864188f,  0.442863f,  0.238856f }, 
{  0.688191f,  0.587785f,  0.425325f }, 
{  0.809017f,  0.309017f,  0.500000f }, 
{  0.681718f,  0.147621f,  0.716567f }, 
{  0.587785f,  0.425325f,  0.688191f }, 
{  0.955423f,  0.295242f,  0.000000f }, 
{  1.000000f,  0.000000f,  0.000000f }, 
{  0.951056f,  0.162460f,  0.262866f }, 
{  0.850651f, -0.525731f,  0.000000f }, 
{  0.955423f, -0.295242f,  0.000000f }, 
{  0.864188f, -0.442863f,  0.238856f }, 
{  0.951056f, -0.162460f,  0.262866f }, 
{  0.809017f, -0.309017f,  0.500000f }, 
{  0.681718f, -0.147621f,  0.716567f }, 
{  0.850651f,  0.000000f,  0.525731f }, 
{  0.864188f,  0.442863f, -0.238856f }, 
{  0.809017f,  0.309017f, -0.500000f }, 
{  0.951056f,  0.162460f, -0.262866f }, 
{  0.525731f,  0.000000f, -0.850651f }, 
{  0.681718f,  0.147621f, -0.716567f }, 
{  0.681718f, -0.147621f, -0.716567f }, 
{  0.850651f,  0.000000f, -0.525731f }, 
{  0.809017f, -0.309017f, -0.500000f }, 
{  0.864188f, -0.442863f, -0.238856f }, 
{  0.951056f, -0.162460f, -0.262866f }, 
{  0.147621f,  0.716567f, -0.681718f }, 
{  0.309017f,  0.500000f, -0.809017f }, 
{  0.425325f,  0.688191f, -0.587785f }, 
{  0.442863f,  0.238856f, -0.864188f }, 
{  0.587785f,  0.425325f, -0.688191f }, 
{  0.688191f,  0.587785f, -0.425325f }, 
{ -0.147621f,  0.716567f, -0.681718f }, 
{ -0.309017f,  0.500000f, -0.809017f }, 
{  0.000000f,  0.525731f, -0.850651f }, 
{ -0.525731f,  0.000000f, -0.850651f }, 
{ -0.442863f,  0.238856f, -0.864188f }, 
{ -0.295242f,  0.000000f, -0.955423f }, 
{ -0.162460f,  0.262866f, -0.951056f }, 
{  0.000000f,  0.000000f, -1.000000f }, 
{  0.295242f,  0.000000f, -0.955423f }, 
{  0.162460f,  0.262866f, -0.951056f }, 
{ -0.442863f, -0.238856f, -0.864188f }, 
{ -0.309017f, -0.500000f, -0.809017f }, 
{ -0.162460f, -0.262866f, -0.951056f }, 
{  0.000000f, -0.850651f, -0.525731f }, 
{ -0.147621f, -0.716567f, -0.681718f }, 
{  0.147621f, -0.716567f, -0.681718f }, 
{  0.000000f, -0.525731f, -0.850651f }, 
{  0.309017f, -0.500000f, -0.809017f }, 
{  0.442863f, -0.238856f, -0.864188f }, 
{  0.162460f, -0.262866f, -0.951056f }, 
{  0.238856f, -0.864188f, -0.442863f }, 
{  0.500000f, -0.809017f, -0.309017f }, 
{  0.425325f, -0.688191f, -0.587785f }, 
{  0.716567f, -0.681718f, -0.147621f }, 
{  0.688191f, -0.587785f, -0.425325f }, 
{  0.587785f, -0.425325f, -0.688191f }, 
{  0.000000f, -0.955423f, -0.295242f }, 
{  0.000000f, -1.000000f,  0.000000f }, 
{  0.262866f, -0.951056f, -0.162460f }, 
{  0.000000f, -0.850651f,  0.525731f }, 
{  0.000000f, -0.955423f,  0.295242f }, 
{  0.238856f, -0.864188f,  0.442863f }, 
{  0.262866f, -0.951056f,  0.162460f }, 
{  0.500000f, -0.809017f,  0.309017f }, 
{  0.716567f, -0.681718f,  0.147621f }, 
{  0.525731f, -0.850651f,  0.000000f }, 
{ -0.238856f, -0.864188f, -0.442863f }, 
{ -0.500000f, -0.809017f, -0.309017f }, 
{ -0.262866f, -0.951056f, -0.162460f }, 
{ -0.850651f, -0.525731f,  0.000000f }, 
{ -0.716567f, -0.681718f, -0.147621f }, 
{ -0.716567f, -0.681718f,  0.147621f }, 
{ -0.525731f, -0.850651f,  0.000000f }, 
{ -0.500000f, -0.809017f,  0.309017f }, 
{ -0.238856f, -0.864188f,  0.442863f }, 
{ -0.262866f, -0.951056f,  0.162460f }, 
{ -0.864188f, -0.442863f,  0.238856f }, 
{ -0.809017f, -0.309017f,  0.500000f }, 
{ -0.688191f, -0.587785f,  0.425325f }, 
{ -0.681718f, -0.147621f,  0.716567f }, 
{ -0.442863f, -0.238856f,  0.864188f }, 
{ -0.587785f, -0.425325f,  0.688191f }, 
{ -0.309017f, -0.500000f,  0.809017f }, 
{ -0.147621f, -0.716567f,  0.681718f }, 
{ -0.425325f, -0.688191f,  0.587785f }, 
{ -0.162460f, -0.262866f,  0.951056f }, 
{  0.442863f, -0.238856f,  0.864188f }, 
{  0.162460f, -0.262866f,  0.951056f }, 
{  0.309017f, -0.500000f,  0.809017f }, 
{  0.147621f, -0.716567f,  0.681718f }, 
{  0.000000f, -0.525731f,  0.850651f }, 
{  0.425325f, -0.688191f,  0.587785f }, 
{  0.587785f, -0.425325f,  0.688191f }, 
{  0.688191f, -0.587785f,  0.425325f }, 
{ -0.955423f,  0.295242f,  0.000000f }, 
{ -0.951056f,  0.162460f,  0.262866f }, 
{ -1.000000f,  0.000000f,  0.000000f }, 
{ -0.850651f,  0.000000f,  0.525731f }, 
{ -0.955423f, -0.295242f,  0.000000f }, 
{ -0.951056f, -0.162460f,  0.262866f }, 
{ -0.864188f,  0.442863f, -0.238856f }, 
{ -0.951056f,  0.162460f, -0.262866f }, 
{ -0.809017f,  0.309017f, -0.500000f }, 
{ -0.864188f, -0.442863f, -0.238856f }, 
{ -0.951056f, -0.162460f, -0.262866f }, 
{ -0.809017f, -0.309017f, -0.500000f }, 
{ -0.681718f,  0.147621f, -0.716567f }, 
{ -0.681718f, -0.147621f, -0.716567f }, 
{ -0.850651f,  0.000000f, -0.525731f }, 
{ -0.688191f,  0.587785f, -0.425325f }, 
{ -0.587785f,  0.425325f, -0.688191f }, 
{ -0.425325f,  0.688191f, -0.587785f }, 
{ -0.425325f, -0.688191f, -0.587785f }, 
{ -0.587785f, -0.425325f, -0.688191f }, 
{ -0.688191f, -0.587785f, -0.425325f }
};
#endif 