/**
 * Author: Kelvin Rodriguez
 * Date: September 12, 2016
 *
 *
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// globals
static const char usage_str[] =
          "ppmrw [format] [input file] [output file]\n"
          "Description -- Converts between PPM P6 and P3\n";

static const size_t INIT_BUFFER_SIZE = 255;

void from_binary(char*, size_t, size_t, FILE*, FILE*);
void from_ascii(char*, size_t, FILE*, FILE*);
void copy_data(char* buffer, size_t size, FILE* input_file, FILE* output_file);

int main (int argc, char* argv[]) {
  // Check Args ------------------------------------------------
  if (argc == 1) {
    printf("%s", usage_str);
  }

  if (argc != 4) {
    printf("ERROR: Incorrect number of parameters\n");
    exit(0);
  }

  char* to_format = argv[1];
  char* input_file_path = argv[2];
  char* output_file_path = argv[3];
  char* buffer = (char*)malloc(sizeof(char)*INIT_BUFFER_SIZE);
  FILE* input_fd = fopen(input_file_path, "r");

  // Get the Magic Number and check for validity ---------------
  fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  buffer[2] = '\0';

  char* file_format = malloc(strlen(buffer));
  strcpy(file_format, buffer);
  printf("File Format = %s\n", file_format);

  if (strcmp(file_format, "P3") && strcmp(file_format, "P6")) {
    printf("ERROR: This is not a valid format\n");
  }

  // Skiping comments ... --------------------------------------
  fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  while(buffer[0] == '#') {
    fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  }

  // Get width, height and pixel size --------------------------
  char* splitstr = NULL;

  splitstr = strtok(buffer, " ");
  size_t width = strtol(splitstr, NULL, 10);

  splitstr = strtok(NULL, " ");
  size_t height = strtol(splitstr, NULL, 10);

  printf("Dimensions = %ld %ld\n", width, height);

  fgets(buffer, INIT_BUFFER_SIZE, input_fd);
  size_t max_val = strtol(buffer, NULL, 10);

  printf("Maximum Value = %ld\n", max_val);

  // realloc buffer to read one line at a time
  size_t data_buffer_size = width*3;
  buffer = realloc(buffer, data_buffer_size);

  // Start Reading/Writing bytes -----------------------------------------
  FILE* output_file = fopen(output_file_path, "w");

  // attach header
  fputs(to_format, output_file);
  sprintf(buffer, "\n%ld %ld\n", width, height);
  fputs(buffer, output_file);
  sprintf(buffer, "%ld\n", max_val);
  fputs(buffer, output_file);

  // attach pixel data
  if (strcmp(file_format, to_format) == 0)
    copy_data(buffer, data_buffer_size, input_fd, output_file);
  else if (strcmp(to_format, "P3") == 0)
    from_binary(buffer, width, height, input_fd, output_file);
  else if (strcmp(to_format, "P6") == 0)
    from_ascii(buffer, data_buffer_size, input_fd, output_file);
  else {
    printf("ERROR:Invalid format choice\n");
  }

}


void from_binary(char* buffer, size_t width, size_t height,
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


void from_ascii(char* buffer, size_t size, FILE* input_file, FILE* output_file) {
  char *token = NULL;
  static unsigned char val = 0;
  while (fgets(buffer, size, input_file) != NULL) {
    token = strtok(buffer, "  \n");
    while (token) {
      val = atoi(token);
      fputc(val, output_file);
      token = strtok(NULL, "  \n");
    }  // end of while loop
  }  // end of outer while loop
}  // end of from_ascii


void copy_data(char* buffer, size_t size, FILE* input_file, FILE* output_file) {
  while(fread(buffer, size, 1, input_file))
    fwrite(buffer, size, 1, output_file);
}
