#include "../3d_viewer.h"

point_t calculate_max_boundaries(point_t current_max_boundaries,
                                 point_t new_potential_boundaries) {
  current_max_boundaries.x =
      maximal(current_max_boundaries.x, new_potential_boundaries.x);
  current_max_boundaries.y =
      maximal(current_max_boundaries.y, new_potential_boundaries.y);
  current_max_boundaries.z =
      maximal(current_max_boundaries.z, new_potential_boundaries.z);
  return current_max_boundaries;
}
