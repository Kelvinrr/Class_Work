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


int main (int argc, char* argv[]) {
  // Check Args ------------------------------------------------
  if (argc == 1) {
    printf("%s", usage_str);
  }

  if (argc != 4) {
    printf("ERROR: Incorrect number of parameters\n");
    exit(0);
  }

  char* to_format = malloc(3);
  if (!strcmp(argv[1], "3"))
    to_format = "P3";
  else if (!strcmp(argv[1], "6"))
    to_format = "P6";

  char* input_file_path = argv[2];
  char* output_file_path = argv[3];

  // Attempt to open and allocate all the things ---------------

  FILE* input_fd = fopen(input_file_path, "rb");
  if (!input_fd) {
    fprintf(stderr, "ERROR: Failed to open file %s\n", input_file_path);
    return -1;
    fclose(input_fd);
  }

  FILE* output_file = fopen(output_file_path, "w");
  if (!input_fd) {
    fprintf(stderr, "ERROR: Failed to open file %s\n", output_file_path);
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }

  char* buffer = (char*)malloc(sizeof(char)*INIT_BUFFER_SIZE);
  if (!buffer) {
    fprintf(stderr, "ERROR: Failed to allocate buffer\n");
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }

  // Get the Magic Number and check for validity ---------------
  fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  buffer[2] = '\0';

  char* file_format = malloc(strlen(buffer));
  strcpy(file_format, buffer);
  printf("File Format = %s -> %s\n", file_format, to_format);

  if (strcmp(file_format, "P3") && strcmp(file_format, "P6")) {
    fprintf(stderr, "ERROR: This is not a valid format\n");
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }

  // Skiping comments ... --------------------------------------
  fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  while(buffer[0] == '#') {
    fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  }

  // Get width, height and pixel size --------------------------
  char* splitstr = strtok(buffer, " ");
  if (!splitstr) {
    fprintf(stderr, "ERROR: invalid width");
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }
  size_t width = strtol(splitstr, NULL, 10);

  splitstr = strtok(NULL, " ");
  if (!splitstr) {
    fprintf(stderr, "ERROR: invalid height");
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }
  size_t height = strtol(splitstr, NULL, 10);

  printf("Dimensions = %ld %ld\n", width, height);

  fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  size_t max_val = strtol(buffer, NULL, 10);

  printf("Maximum Value = %ld\n", max_val);

  if (max_val > 255) {
    fprintf(stderr,"ERROR: This image requires multi-byte channels "
           "which is not supported.");
    return -1;
  }

  if (max_val < 1) {
    fprintf(stderr,"ERROR: Max value cannot be less than 1\n");
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }

  // realloc buffer to read one line at a time
  size_t data_buffer_size = width*3;
  buffer = realloc(buffer, data_buffer_size);
  if (!buffer) {
    fprintf(stderr, "ERROR: Not enough memory to open image\n");
    fclose(output_file);
    fclose(input_fd);
    return -1;
  }

  // check if file size is correct ------------------------------
  size_t size = 0;

  if (strcmp(file_format, "P6") == 0) {
    if (!(size = check_bin_image_size(width, height, input_fd))) {
      fprintf(stderr, "ERROR: Real image size does not match header.\n");
      fclose(output_file);
      fclose(input_fd);
      return -1;
    }
  } // end of checking P6 integrity

  if (strcmp(file_format, "P3") == 0) {
    if (!(size = check_ascii_image_size(width, height, buffer, INIT_BUFFER_SIZE, input_fd))) {
      fprintf(stderr, "ERROR: Real image size does not match header.\n");
      fclose(output_file);
      fclose(input_fd);
      return -1;
    }
  } // end of checking P6 integrity

  // Start Reading/Writing bytes --------------------------------

  // attach header
  fputs(to_format, output_file);
  sprintf(buffer, "\n%ld %ld\n", width, height);
  fputs(buffer, output_file);
  sprintf(buffer, "%ld\n", max_val);
  fputs(buffer, output_file);

  // attach pixel data
  if (strcmp(file_format, to_format) == 0) {
    copy_data(buffer, data_buffer_size, input_fd, output_file);
  }
  else if (strcmp(to_format, "P3") == 0) {
    bin_to_ascii(buffer, width, height, input_fd, output_file);
  }
  else if (strcmp(to_format, "P6") == 0) {
    ascii_to_bin(buffer, data_buffer_size, input_fd, output_file);
  }
  else {
    printf("ERROR:Invalid format choice\n");
  }

}

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
