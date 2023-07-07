#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t* readfile(const char *path)
{
    off_t fSize;
    uint8_t *buffer;
    uint_least8_t result;
    size_t readResult;

    FILE *f = fopen(path, "rb");

    if(f == NULL)
        return NULL;
    
    result = fseeko(f, 0, SEEK_END);

    if(result != 0)
    {
        fclose(f);
        return NULL;
    }
    
    fSize = ftello(f);
    rewind(f);

    if(fSize == -1L)
    {
        fclose(f);
        return NULL;
    }

    buffer = malloc(fSize + 5);

    if(buffer == NULL)
    {
        fclose(f);
        return NULL;
    }

    readResult = fread(buffer, sizeof(uint8_t), fSize, f);

    if(readResult != fSize)
    {
        fclose(f);
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    buffer[fSize] = '\0';

    fclose(f);
    return buffer;
}