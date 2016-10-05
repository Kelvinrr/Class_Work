/**
 * Simple Dictionary implementation in C
 *
 *
 *
 */

const uint8_t CAMERA = 0;
const uint8_t SPHERE = 1;
const uint8_t PLANE = 2;

typedef struct {
  int kind;
  double color[3];

  union {
    struct {
      double width;
      double height;
    } Camera;

    struct {
      double position[3];
      double radius;
    } Sphere;

    struct {
      double normal[3];
      double position[3];
    } Plane;
  };

} Object;