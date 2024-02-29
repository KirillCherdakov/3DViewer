#include "../3d_viewer.h"

point_t multiply_point_on_double(point_t point, double number) {
  point.x *= number;
  point.y *= number;
  point.z *= number;
  return point;
}
