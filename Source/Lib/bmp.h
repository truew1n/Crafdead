#ifndef CFD_LIB_BMP_H
#define CFD_LIB_BMP_H

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
    uint8_t channels;
} bmp_t;

inline void read_and_write(void *memory, FILE *file, int32_t width, int32_t height, int8_t padding, uint8_t channels);

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

    bmp.channels = bits / 8;
    void *mem = malloc(bmp.channels*bmp.width*bmp.height);

    fseek(file, offset_to_pixarr, SEEK_SET);
    int8_t padding = (4 - bmp.width*(bmp.channels)%4)%4;
    
    read_and_write(mem, file, bmp.width, bmp.height, padding, bmp.channels);

    bmp.memory = (void *) mem;

    fclose(file);
    return bmp;
}

inline void read_and_write(void *memory, FILE *file, int32_t width, int32_t height, int8_t padding, uint8_t channels)
{
    if(channels == 4) {
        for(int y = height-1; y >= 0; --y) {
            for(int x = 0; x < width; ++x) {
                uint32_t color = 0x00000000;
                uint8_t red = 0x00;
                uint8_t green = 0x00;
                uint8_t blue = 0x00;
                uint8_t alpha = 0x00;
                fread(&blue, sizeof(blue), 1, file);
                fread(&green, sizeof(green), 1, file);
                fread(&red, sizeof(red), 1, file);
                fread(&alpha, sizeof(alpha), 1, file);
                color = (alpha << 24) + (blue << 16) + (green << 8) + red; // OpenGL Moment RGBA really means ABGR layout in memory :D
                *((uint32_t *) memory + y * width + x) = color;
            }

            fseek(file, padding, SEEK_CUR);
        }
    } else if(channels == 3) {
        for(int y = height-1; y >= 0; --y) {
            for(int x = 0; x < width; ++x) {
                uint8_t red = 0x00;
                uint8_t green = 0x00;
                uint8_t blue = 0x00;
                fread(&blue, sizeof(blue), 1, file);
                fread(&green, sizeof(green), 1, file);
                fread(&red, sizeof(red), 1, file);
                *((uint8_t *) memory + y * width + x) = blue;
                *((uint8_t *) memory + y * width + x + 1) = green;
                *((uint8_t *) memory + y * width + x + 2) = red;
            }

            fseek(file, padding, SEEK_CUR);
        }
    } else if(channels == 2) {
        for(int y = height-1; y >= 0; --y) {
            for(int x = 0; x < width; ++x) {
                uint8_t black = 0x00;
                uint8_t white = 0x00;
                fread(&black, sizeof(black), 1, file);
                fread(&white, sizeof(white), 1, file);
                *((uint8_t *) memory + y * width + x) = black;
                *((uint8_t *) memory + y * width + x + 1) = white;
            }

            fseek(file, padding, SEEK_CUR);
        }
    } else if(channels == 1) {
        for(int y = height-1; y >= 0; --y) {
            for(int x = 0; x < width; ++x) {
                uint8_t grayscale = 0x00;
                fread(&grayscale, sizeof(grayscale), 1, file);
                *((uint8_t *) memory + y * width + x) = grayscale;
            }

            fseek(file, padding, SEEK_CUR);
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif