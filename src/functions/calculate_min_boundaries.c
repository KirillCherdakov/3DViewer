#include "../3d_viewer.h"

point_t calculate_min_boundaries(point_t current_min_boundaries,
                                 point_t new_potential_boundaries) {
  current_min_boundaries.x =
      minimal(current_min_boundaries.x, new_potential_boundaries.x);
  current_min_boundaries.y =
      minimal(current_min_boundaries.y, new_potential_boundaries.y);
  current_min_boundaries.z =
      minimal(current_min_boundaries.z, new_potential_boundaries.z);
  return current_min_boundaries;
}
