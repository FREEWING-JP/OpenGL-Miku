#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "BmpLoader.h"

/*==============================*
** BMPÉtÉ@ÉCÉãÇÃì«Ç›çûÇ›
**==============================*/
GLuint load_bmp(const char *file_name)
{
    FILE *fp;
    unsigned char header[54];
    unsigned char *data;
    size_t count, size;
    int width, height;
    GLuint texture;

    fp = fopen(file_name, "rb");
    if (!fp) {
        fprintf(stderr, "Cannot open %s.\n", file_name);
        exit(EXIT_FAILURE);
    }

    count = fread(header, 1, sizeof(header), fp);
    if (count != sizeof(header)) {
        fprintf(stderr, "Cannot read bmp file %s.\n", file_name);
        exit(EXIT_FAILURE);
    }

    if (header[0] != 'B' || header[1] != 'M') {
        fprintf(stderr, "Cannot read bmp file %s.\n", file_name);
        exit(EXIT_FAILURE);
    }

    width = *(int*)(header + 0x12);
    height = *(int*)(header + 0x16);
    size = width * height * 3;

    data = malloc(sizeof(unsigned char) * size);
    if (!data) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    count = fread(data, sizeof(unsigned char), size, fp);
    if (count != size) {
        fprintf(stderr, "Cannot read bmp file %s.\n", file_name);
        exit(EXIT_FAILURE);
    }

    fclose(fp);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        GL_BGR, GL_UNSIGNED_BYTE, data);

    free(data); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
