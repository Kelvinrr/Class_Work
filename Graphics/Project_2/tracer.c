#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "json_parser.h"

#include "VectorMath.h"
#include "pplib.h"
#include "tracer.h"

double sphere_intersection(double *Ro, double *Rd, double *Center, double r) {
  double a = (sqr(Rd[0]) + sqr(Rd[1]) + sqr(Rd[2]));
  double b = (2 * (Ro[0] * Rd[0] - Rd[0] * Center[0] + Ro[1] * Rd[1] -
                   Rd[1] * Center[1] + Ro[2] * Rd[2] - Rd[2] * Center[2]));
  double c = sqr(Ro[0]) - 2 * Ro[0] * Center[0] + sqr((Center[1]) + Ro[1]) -
             2 * Ro[1] * Center[1] + sqr(Center[1]) + sqr(Ro[2]) -
             2 * Ro[2] * Center[2] + sqr(Center[2]) - sqr(r);

  double det = sqr(b) - 4 * a * c;
  if (det < 0)
    return -1;

  det = sqrt(det);

  double t0 = (-b - det) / (2 * a);
  if (t0 > 0)
    return t0;

  double t1 = (-b + det) / (2 * a);
  if (t1 > 0)
    return t1;

  return -1;
}

double plane_intersection(double *Ro, double *Rd, double *position,
                          double *normal) {
  // distance = dot(Po-Lo,N)/dot(L,N)
  V3 temp = malloc(sizeof(double) * 3);
  v3_subtract(Ro, position, temp);
  double distance = v3_dot(normal, temp);

  double denominator = v3_dot(normal, Rd);
  distance = -(distance / denominator);
  if (distance > 0)
    return distance;

  return 0;
}

int main(int argc, char *argv[]) {

  if (argc < 5) {
    fprintf(stderr, "Error: Not enough arguements\n");
    exit(1);
  }

  int img_width = strtol(argv[1], (char **)NULL, 10);
  int img_height = strtol(argv[2], (char **)NULL, 10);
  char *input_json = argv[3];

  FILE *output_ppm = fopen(argv[4], "wb");
  if (!output_ppm) {
    fprintf(stderr, "ERROR: Failed to open file %s\n", argv[4]);
    fclose(output_ppm);
    return -1;
  }

  Pixel color = {.r = 0, .g = 0, .b = 0};
  Pixel black = {.r = 0, .g = 0, .b = 0};

  Object **objects = read_scene(input_json);

  double cx = 0;
  double cy = 0;
  double h = 2;
  double w = 2;

  int M = img_width;
  int N = img_height;

  Pixel *buffer = malloc(M * N * sizeof(Pixel));

  double pixheight = h / M;
  double pixwidth = w / N;

  printf("%d %d\n", M, N);

  for (int y = 0; y < M; y += 1) {
    for (int x = 0; x < N; x += 1) {
      double Ro[3] = {0, 0, 0};
      // Rd = normalize(P - Ro)
      double Rd[3] = {cx - (w / 2) + pixwidth * (x + 0.5),
                      -(cy - (h / 2) + pixheight * (y + 0.5)), 1};
      normalize(Rd);

      double best_t = INFINITY;
      bool found_shape = false;
      for (int i = 0; objects[i] != 0; i++) {
        if (found_shape)
          break;

        double t = 0;
        switch (objects[i]->type) {
        case PLANE:
          t = plane_intersection(Ro, Rd, objects[i]->Plane.position,
                                 objects[i]->Plane.normal);
          if (t > 0 && t < best_t) {
            found_shape = true;
            color = objects[i]->color;
          }
          break;
        case SPHERE:
          t = sphere_intersection(Ro, Rd, objects[i]->Sphere.position,
                                  objects[i]->Sphere.radius);

          if (t > 0 && t < best_t) {
            found_shape = true;
            color = objects[i]->color;
          }
          break;
        case CAMERA:
          break;
        default: // error
          exit(1);
        } // end of switch

        if (t > 0 && t < best_t)
          best_t = t;
      } // end of loop

      if (best_t > 0 && best_t != INFINITY) {
        buffer[y * M + x] = color;
      } else {
        buffer[y * M + x] = black;
      }
    }
  }

  buffer_to_bin(buffer, M, N, output_ppm);
  return 0;
}
