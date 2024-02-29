#include "../3d_viewer.h"

point_t find_center(point_t a, point_t b) {
  point_t center = {0};

  center.x = median(a.x, b.x);
  center.y = median(a.y, b.y);
  center.z = median(a.z, b.z);

  return center;
}
