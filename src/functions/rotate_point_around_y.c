#include <math.h>

#include "../3d_viewer.h"

point_t rotate_point_around_y(point_t point, double angle) {
  point_t new_point = {0};
  new_point.x = point.x * cos(angle) + point.z * sin(angle);
  new_point.y = point.y;
  new_point.z = point.z * cos(angle) - point.x * sin(angle);
  return new_point;
}
