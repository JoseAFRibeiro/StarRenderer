#include "starengine/models.h"
#include "starengine/seio.h"
#include <stdio.h>
#include <stdlib.h>

static inline uint8_t MD2alloc(MD2Model *model)
{   

    uint8_t numSkins = model->hdr.numSkins;
    uint16_t numTexCoord = model->hdr.numSt;
    uint16_t numTris = model->hdr.numTris;
    uint16_t numFrames = model->hdr.numFrames;
    uint16_t numGLCommands = model->hdr.numGlCommands;


    model->texName = malloc(sizeof(MD2TexName)*numSkins);
    model->texCoords = malloc(numTexCoord * TEXT_COORDS_SIZE);
    model->frames = malloc(numFrames * FRAME_SIZE);
    model->triangles = malloc(numTris * TRIANGLE_SIZE);
    model->glcommands = malloc(sizeof(uint32_t) * numGLCommands);

    for(uint16_t i = 0; i < model->hdr.numFrames; i++)
   
        model->frames[i].vertices = malloc(sizeof(MD2Vertex) * model->hdr.numVerts);

    if((model->frames == NULL) || (model->triangles == NULL) || (model->texCoords == NULL))
    {   
        free(model->frames->vertices);
        free(model->frames);
        free(model->triangles);
        free(model->texCoords);
        free(model->glcommands);
        free(model->texName);

        return 1;
    }

    return 0;
}


void MD2Free(MD2Model *model)
{
    free(model->frames->vertices);
    free(model->frames);
    free(model->triangles);
    free(model->texCoords);
    free(model->glcommands);
    free(model->texName);

}

void MDVertexBuffer(const char *path, MD2Model *model)
{
    FILE *f = fopen(path, "rb");
    fread(&model->hdr, sizeof(MD2Header), 1, f);
    
    MD2alloc(model);
    
    fseek(f, model->hdr.offsetSkins, SEEK_SET);
    fread(model->texName, sizeof(MD2TexName), model->hdr.numSkins, f);

    fseek(f, model->hdr.offsetST, SEEK_SET);
    fread(model->texCoords, sizeof(MD2TexCoords), model->hdr.numSt, f);

    fseek(f, model->hdr.offsetTris, SEEK_SET);
    fread(model->triangles, sizeof(MD2Tri), model->hdr.numTris, f);

    fseek(f, model->hdr.offsetGLCommands, SEEK_SET);
    fread(model->glcommands, sizeof(int), model->hdr.numGlCommands, f);

    fseek(f, model->hdr.offsetFrames, SEEK_SET);

    for(uint16_t i = 0; i < model->hdr.numFrames; i++)
    {
        fread(model->frames[i].scale, sizeof(vec3), 1, f);
        fread(model->frames[i].translate, sizeof(vec3), 1, f);
        fread(model->frames[i].name, sizeof(char), 16, f);
        fread(model->frames[i].vertices, sizeof(MD2Vertex), model->hdr.numVerts, f);

        for(int b = 0; b < model->hdr.numVerts; b++)
        {
            if(model->frames[i].vertices[b].index > 135)
            {
                printf("Frame %d vertex %d: Invalid normal index %d. Current file position %d\n", i, b, model->frames[i].vertices[b].index, ftell(f));
            }
        }
    }

    fclose(f);
    return;

}
//
//void MDVertexBuffer(const char *path, MD2Model *mdl)
//{
//FILE *fp;
//  int i;
//
//  fp = fopen (path, "rb");
//  if (!fp)
//    {
//      fprintf (stderr, "Error: couldn't open \"%s\"!\n", path);
//      return 0;
//    }
//
//  /* Read header */
//  fread (&mdl->hdr, 1, sizeof(MD2Header), fp);
//
//  if ((mdl->hdr.ident != 844121161) ||
//      (mdl->hdr.version != 8))
//    {
//      /* Error! */
//      fprintf (stderr, "Error: bad version or identifier\n");
//      fclose (fp);
//      return 0;
//    }
//
//  /* Memory allocations */
//  mdl->texName =
//    malloc (sizeof (MD2TexName) * mdl->hdr.numSkins);
//  mdl->texCoords =
//    malloc (sizeof (MD2TexCoords) * mdl->hdr.numSt);
//  mdl->triangles =
//    malloc (sizeof (MD2Tri) * mdl->hdr.numTris);
//  mdl->frames =
//    malloc (sizeof (MD2Frame) * mdl->hdr.numFrames);
//  mdl->glcommands = (int *)malloc (sizeof (int) * mdl->hdr.numGlCommands);
//
//  /* Read model data */
//  fseek (fp, mdl->hdr.offsetSkins, SEEK_SET);
//  fread (mdl->texName, sizeof (MD2TexName),
//	 mdl->hdr.numSkins, fp);
//
//  fseek (fp, mdl->hdr.offsetST, SEEK_SET);
//  fread (mdl->texCoords, sizeof (MD2TexCoords),
//	 mdl->hdr.numSt, fp);
//
//  fseek (fp, mdl->hdr.offsetTris, SEEK_SET);
//  fread (mdl->triangles, sizeof (MD2Tri),
//	 mdl->hdr.numTris, fp);
//
//  fseek (fp, mdl->hdr.offsetGLCommands, SEEK_SET);
//  fread (mdl->glcommands, sizeof (int), mdl->hdr.numGlCommands, fp);
//
//  /* Read frames */
//  fseek (fp, mdl->hdr.offsetFrames, SEEK_SET);
//  for (i = 0; i < mdl->hdr.numFrames; ++i)
//    {
//      /* Memory allocation for vertices of this frame */
//      mdl->frames[i].vertices = 
//	malloc (sizeof (MD2Vertex) * mdl->hdr.numVerts);
//
//      /* Read frame data */
//      fread (mdl->frames[i].scale, sizeof (vec3), 1, fp);
//      fread (mdl->frames[i].translate, sizeof (vec3), 1, fp);
//      fread (mdl->frames[i].name, sizeof (char), 16, fp);
//      fread (mdl->frames[i].vertices, sizeof (MD2Vertex),
//	     mdl->hdr.numVerts, fp);
//
//        for(int b = 0; b < mdl->hdr.numVerts; b++)
//        {
//            if(mdl->frames[i].vertices[b].index > 135)
//            {
//                printf("Frame %d vertex %d: Invalid normal index %d. Current file position %d\n", i, b, mdl->frames[i].vertices[b].index, ftell(fp));
//            }
//        }
//    }
//
//  fclose (fp);
//  return;
//}
//