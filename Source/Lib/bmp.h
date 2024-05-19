#ifndef DTD_LIB_BMP_H
#define DTD_LIB_BMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct bmp_t {
    int32_t width;
    int32_t height;
    void *memory;
} bmp_t;

inline bmp_t open_bmp(const char *FILEPATH)
{
    FILE *file = fopen(FILEPATH, "rb");

    bmp_t bmp = {0};

    fseek(file, 10, SEEK_SET);
    int32_t offset_to_pixarr = 0;
    fread(&offset_to_pixarr, sizeof(offset_to_pixarr), 1, file);

    fseek(file, 18, SEEK_SET);
    fread(&bmp.width, sizeof(bmp.width), 1, file);
    fread(&bmp.height, sizeof(bmp.height), 1, file);

    fseek(file, 28, SEEK_SET);
    int16_t bits = 32;
    fread(&bits, sizeof(bits), 1, file);

    void *mem = malloc(sizeof(uint32_t)*bmp.width*bmp.height);

    fseek(file, offset_to_pixarr, SEEK_SET);
    int8_t padding = (4 - bmp.width*(bits/8)%4)%4;
    for(int y = bmp.height-1; y >= 0; --y) {
        for(int x = 0; x < bmp.width; ++x) {
            uint32_t color = 0x00000000;
            uint8_t red = 0x00;
            uint8_t green = 0x00;
            uint8_t blue = 0x00;
            uint8_t alpha = 0x00;
            fread(&blue, sizeof(blue), 1, file);
            fread(&green, sizeof(green), 1, file);
            fread(&red, sizeof(red), 1, file);
            if(bits == 32) fread(&alpha, sizeof(alpha), 1, file);
            color = (alpha << 24) + (blue << 16) + (green << 8) + red; // OpenGL Moment RGBA really means ABGR layout in memory :D
            *((uint32_t *) mem + y * bmp.width + x) = color;
        }

        fseek(file, padding, SEEK_CUR);
    }
    
    bmp.memory = (void *) mem;

    fclose(file);
    return bmp;
}

#ifdef __cplusplus
}
#endif

#endif