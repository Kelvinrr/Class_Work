/**
 *
 *
 * Author: Kelvin Rodriguez
 * Date: September 12, 2016
 *
 *
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>

static const char usage_str[] =
          "ppmrw [format] [input file] [output file]\n"
          "Description -- Converts between PPM P6 and P3\n";

int main (int argc, char* arv[]) {
  if (argc == 1) {
    printf("%s", usage_str);
  }

  if (argc != 3) {
    printf("ERROR: Incorrect number of parameters\n");
    exit(0);
  }




}
