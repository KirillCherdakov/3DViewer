#include <math.h>

#include "../3d_viewer.h"

point_t rotate_point_around_x(point_t point, double angle) {
  point_t new_point = {0};
  new_point.x = point.x;
  new_point.y = point.y * cos(angle) - point.z * sin(angle);
  new_point.z = point.y * sin(angle) + point.z * cos(angle);
  return new_point;
}
