/**
 * Author: Kelvin Rodriguez
 * Date: September 12, 2016
 *
 *
 *
 *
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// globals
static const size_t INIT_BUFFER_SIZE = 255;
static const char usage_str[] =
          "ppmrw [format] [input file] [output file]\n"
          "Description -- Converts between PPM P6 and P3\n";

void bin_to_ascii(char*, size_t, size_t, FILE*, FILE*);
void ascii_to_bin(char*, size_t, FILE*, FILE*);
void copy_data(char* buffer, size_t size, FILE*, FILE*);
size_t check_bin_image_size(size_t, size_t, FILE*);
size_t check_ascii_image_size(size_t, size_t, char*, size_t, FILE*);
size_t size_to_endl(char* buffer, size_t size, FILE *const fin);


typedef struct pix {
  uint8_t r, g, b;
} Pixel;


size_t check_bin_image_size(size_t width, size_t height, FILE* file_to_check) {
  fpos_t original_pos = 0;
  fpos_t end_pos = 0;

  fgetpos(file_to_check, &original_pos);
  fseek(file_to_check, 0, SEEK_END);
  fgetpos(file_to_check, &end_pos);

  if (end_pos < original_pos || end_pos - original_pos != width*height*3) {
    printf("ERROR: Image does not have a correct size\n");
    return (int)NULL;
  }

  fsetpos(file_to_check, &original_pos);
  return end_pos - original_pos;
}


size_t check_ascii_image_size(size_t width, size_t height,
                  char* buffer, size_t size, FILE* file_to_check){
  fpos_t original_pos = 0;
  char *token         = NULL;
  size_t num_toks     = 0;

  fgetpos(file_to_check, &original_pos);
  size_to_endl(buffer, size, file_to_check);

  while (fgets(buffer, size, file_to_check) != NULL) {
    token = strtok(buffer, " \n");
    while (token) {
      num_toks++;
      token = strtok(NULL, " \n");
    }  // end of while loop
  }  // end of outer while loop

  fsetpos(file_to_check, &original_pos);

  if (num_toks != width*height*3) {
    return 0;
  } else {
    return num_toks;
  }
}


void bin_to_ascii(char* buffer, size_t width, size_t height,
                                  FILE* input_file, FILE* output_file) {

  unsigned char* unint8_buffer = (unsigned char*)buffer;

  for (size_t i = 0; i < height; i++) {
    fread(unint8_buffer, width*3, 1, input_file);
    for (size_t j = 0; j < width; j++) {
      sprintf(buffer, "%u ", unint8_buffer[3*j]);
      fputs(buffer, output_file);
      sprintf(buffer, "%u ", unint8_buffer[3*j+1]);
      fputs(buffer, output_file);
      sprintf(buffer, "%u\n",unint8_buffer[3*j+2]);
      fputs(buffer, output_file);
    }  // end of inner for loop
  }  // end of outer for loop
}  // end of from_binary

void buffer_to_bin(Pixel* buffer, size_t width, size_t height, FILE* output_file) {
  fprintf(output_file, "P6\n");
  fprintf(output_file, "%zu %zu\n", width, height);
  fprintf(output_file, "255\n");
  for(int i = 0; i < width*height; i++) {
      fputc(buffer[i].r, output_file);
      fputc(buffer[i].g, output_file);
      fputc(buffer[i].b, output_file);
  }
}


void ascii_to_bin(char* buffer, size_t size, FILE* input_file, FILE* output_file) {
  char *token = NULL;
  static unsigned char val = 0;

  size = size_to_endl(buffer, size, input_file);

  while (fgets(buffer, size, input_file)) {
    token = strtok(buffer, " \n");
    while (token) {
      val = (unsigned char)atoi(token);
      fputc(val, output_file);
      token = strtok(NULL, "  \n");
    }  // end of while loop
  }  // end of outer while loop
}

void copy_data(char* buffer, size_t size, FILE* input_file, FILE* output_file) {
  while(fread(buffer, size, 1, input_file))
    fwrite(buffer, size, 1, output_file);
}

size_t size_to_endl(char* buffer, size_t size, FILE *const fin) {
    fpos_t pos = 0;
    int c      = 0;
    int count  = 0;
    count      = 0;

    fgetpos(fin, &pos);
    while (true) {
        c = fgetc(fin);
        if (c == EOF || c == '\n')
            break;
        ++count;
    }
    fsetpos(fin, &pos);

    if (count > size) {
      buffer = realloc(buffer, count+1);
      size = count+1;
    }

    return size;
}
