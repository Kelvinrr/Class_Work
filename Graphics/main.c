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

// globals
static const char usage_str[] =
          "ppmrw [format] [input file] [output file]\n"
          "Description -- Converts between PPM P6 and P3\n";

static const size_t INIT_BUFFER_SIZE = 255;

int main (int argc, char* argv[]) {
  // Check Args ------------------------------------------------
  if (argc == 1) {
    printf("%s", usage_str);
  }

  if (argc != 3) {
    printf("ERROR: Incorrect number of parameters\n");
    exit(0);
  }

  char* input_file_path = argv[1];
  char* output_file_path = argv[2];
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

  // realloc buffer to read one line at a time
  buffer = realloc(buffer, width);

}
