#include "../3d_viewer.h"

point_t point_plus_point(point_t a, point_t b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}
