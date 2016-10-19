#ifndef _PPLIB_H_
#define _PPLIB_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { float r, g, b; } Pixel;

void buffer_to_bin(Pixel *buffer, size_t width, size_t height,
                   FILE *output_file) {
  fprintf(output_file, "P6\n");
  fprintf(output_file, "%zu %zu\n", width, height);
  fprintf(output_file, "255\n");
  for (int i = 0; i < width * height; i++) {
    fputc(buffer[i].r, output_file);
    fputc(buffer[i].g, output_file);
    fputc(buffer[i].b, output_file);
  }
}

float clamp(float val) {
  return (val < 0.0) ? 0 : (val > 1) ? 1.0 : val;
}

#endif
