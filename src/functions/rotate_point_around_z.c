#include <math.h>

#include "../3d_viewer.h"

point_t rotate_point_around_z(point_t point, double angle) {
  point_t new_point = {0};
  new_point.x = point.x * cos(angle) - point.y * sin(angle);
  new_point.y = point.x * sin(angle) + point.y * cos(angle);
  new_point.z = point.z;
  return new_point;
}
