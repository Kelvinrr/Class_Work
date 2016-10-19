#ifndef _TRACER_H_
#define _TRACER_H_

/**
 * Simple Dictionary implementation in C
 *
 *
 *
 */

#include "pplib.h"
#include "vector_math.h"


const uint8_t CAMERA = 0;
const uint8_t SPHERE = 1;
const uint8_t PLANE = 2;
const uint8_t LIGHT = 3;

typedef struct {
  int type;

  union {
    struct {
      double width;
      double height;
    } Camera;

    struct {
      Pixel diffuse_color;
      Pixel sepcular_color;
      
      double position[3];
      double radius;
    } Sphere;

    struct {
      Pixel diffuse_color;
      Pixel sepcular_color;
      
      double normal[3];
      double position[3];
    } Plane;
    
    struct {
      Pixel color;
      
      double theta;
      
      double angular_a0;
      double dirction[3];
      
      double radial_a0;
      double radial_a1;
      double radial_a2;
      
      double position[3];
    } Light;
  };

} Object;

#endif
