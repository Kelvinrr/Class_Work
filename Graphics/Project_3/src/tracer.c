#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "json_parser.h"
#include "pplib.h"
#include "tracer.h"
#include "vector_math.h"

bool is_object_equal(Object *first, Object *second) {
  if (first->type != second->type) {
    return false;
  }

  if (first->type == SPHERE) {
    return first->Sphere.position == second->Sphere.position;
  } else if (first->type == PLANE) {
    return first->Plane.position == second->Sphere.position;
  } else {
    return false;
  }
}

int main(int argc, char *argv[]) {

  // check if args are within range
  if (argc < 5) {
    fprintf(stderr, "Error: Not enough arguements\n");
    exit(1);
  }

  // get the width and height
  int img_width = strtol(argv[1], (char **)NULL, 10);
  int img_height = strtol(argv[2], (char **)NULL, 10);

  char *input_json = argv[3];

  // open the output file for reading
  FILE *output_ppm = fopen(argv[4], "wb");
  if (!output_ppm) {
    fprintf(stderr, "ERROR: Failed to open file %s\n", argv[4]);
    fclose(output_ppm);
    return -1;
  }

  // init the color objexts for later
  Pixel color = {.r = 0, .g = 0, .b = 0};
  Pixel bg_color = {.r = 0, .g = 0, .b = 0};

  // get the array of object pointers
  Object **objects = read_scene(input_json);
  double h = 2;
  double w = 2;
  int num_cams = 0;

  // look for the cameras
  for (int i = 0; objects[i] != 0; i++) {
    if (objects[i]->type == CAMERA) {
      w = objects[i]->Camera.width;
      h = objects[i]->Camera.height;
      num_cams++;
    }
  }

  // if no camera was found or more than one camera was found
  // throw an error
  if (num_cams != 1) {
    fprintf(stderr, "ERROR: Incorrect number of cameras specified, must have "
                    "1. Found: %d\n",
            num_cams);
  }

  // look for all the lights
  size_t num_lights = 0;
  Object **lights = malloc(INIT_NUM_OBJ * sizeof(Object));
  for (int i = 0; objects[i] != 0; i++) {
    if (objects[i]->type == LIGHT) {
      lights[num_lights] = objects[i];
      num_lights++;
    }
  }
  lights[num_lights] = NULL;

  // image variables
  double cx = 0;
  double cy = 0;
  int N = img_width;
  int M = img_height;

  // create the image buffer
  Pixel *buffer = malloc(M * N * sizeof(Pixel));

  double pixheight = h / M;
  double pixwidth = w / N;

  // Start processing the image
  for (int y = 0; y < M; y += 1) {
    for (int x = 0; x < N; x += 1) {
      color = bg_color;
      double Ro[3] = {0, 0, 0};
      double Rd[3] = {cx - (w / 2) + pixwidth * (x + 0.5),
                      -(cy - (h / 2) + pixheight * (y + 0.5)), 1};
      normalize(Rd);

      double closest_t = INFINITY;
      size_t closest_object_idx = 0;

      // find the nearest object and distance ---------------
      for (int i = 0; objects[i] != 0; i++) {
        double t = intersection_dist(Ro, Rd, objects[i]);
        if (t > 0 && t < closest_t) {
          closest_t = t;
          closest_object_idx = i;
        }
      }
      // ----------------------------------------------------

      Object *closest_object = objects[closest_object_idx];

      // get vector from surface of object to light sources
      for (int j = 0; j < num_lights; j += 1) {
        // origin of vector pointing to light from surface
        V3 Lo = malloc(3 * sizeof(double));
        closest_t = intersection_dist(Ro, Rd, closest_object);
        v3_scale(Rd, closest_t - 0.1, Lo);

        // direction of vector pointing to light from surface
        V3 Ld = malloc(3 * sizeof(double));
        v3_subtract(lights[j]->Light.position, Lo, Ld);

        double distance_to_light = v3_magnitude(Ld);
        normalize(Ld);

        Object *closest_shadow_object = NULL;
        double closest_shadow_t = distance_to_light;

        // check lighting --------------------------------------
        for (int k = 0; objects[k] != 0; k++) {

          double t = intersection_dist(Lo, Ld, objects[k]);
          if (t > 0 && t < closest_t && t < distance_to_light) {
            closest_shadow_t = t;
            closest_shadow_object = objects[k];
          }
        }

        // lighting is found ----------------------------------

        Pixel diffuse_color = (closest_object->type == SPHERE)
                                  ? closest_object->Sphere.diffuse_color
                                  : closest_object->Plane.diffuse_color;

        Pixel specular_color = (closest_object->type == SPHERE)
                                   ? closest_object->Sphere.sepcular_color
                                   : closest_object->Plane.sepcular_color;

        // get the surface normal
        V3 normal;
        if (closest_object->type == PLANE) {
          normal = closest_object->Plane.normal;
        } else {
          normal = malloc(3 * sizeof(double));
          v3_subtract(Lo, closest_object->Sphere.position, normal);
        }

        normalize(normal);
        // get the vector aiming towards the light
        V3 L = Ld;

        // reflect it relative to the normal
        // formula: r = L−2(L⋅n)n
        V3 R = malloc(3 * sizeof(double));
        v3_scale(normal, 2 * v3_dot(L, normal), R);
        v3_subtract(L, R, R);
        normalize(R);

        double diffuse_coeff = v3_dot(L, normal);
        double specular_coeff =
            (closest_shadow_object == NULL) ? pow(v3_dot(R, Rd), 100) : 0;

        // light computation for spot lights
        double Fang = 1;
        if (lights[j]->Light.is_spot) {
          normalize(lights[j]->Light.dirction);

          V3 scaled = malloc(3 * sizeof(double));
          v3_scale(L, -1, scaled);

          double cos_angle = v3_dot(lights[j]->Light.dirction, scaled);
          double angle = acos(cos_angle);
          if (angle > lights[j]->Light.theta) {
            Fang = 0;
          } else {
            Fang = pow(cos_angle, lights[j]->Light.angular_a0);
          }
        }

        double k1 = lights[j]->Light.radial_a0;
        double k2 = lights[j]->Light.radial_a1;
        double k3 = lights[j]->Light.radial_a2;
        double k =
            1 / (pow(k1, 2) * distance_to_light + k2 * distance_to_light + k3);

        color.r += ((diffuse_color.r * diffuse_coeff) +
                    (specular_coeff * specular_color.r)) *
                   lights[j]->Light.color.r * k * Fang;
        color.g += ((diffuse_color.g * diffuse_coeff) +
                    (specular_coeff * specular_color.g)) *
                   lights[j]->Light.color.g * k * Fang;
        color.b += ((diffuse_color.b * diffuse_coeff) +
                    (specular_coeff * specular_color.b)) *
                   lights[j]->Light.color.b * k * Fang;

        if (closest_shadow_object != NULL &&
            !is_object_equal(closest_shadow_object, closest_object)) {
          color = bg_color;
        }
      } // end of light source loop

      // put the final color into the buffer

      buffer[(y * N) + x].r = (uint8_t)(255 * clamp(color.r));
      buffer[(y * N) + x].g = (uint8_t)(255 * clamp(color.g));
      buffer[(y * N) + x].b = (uint8_t)(255 * clamp(color.b));

    } // end of N loop
  }   // end of M loop

  buffer_to_bin(buffer, N, M, output_ppm);
  return 0;
}
