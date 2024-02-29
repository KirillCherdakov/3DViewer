#include "../3d_viewer.h"

double find_max_projection(object_t* object) {
  point_t most_distant_point = object->vertices.most_distant;
  point_t closest_point = object->vertices.closest;

  point_t size_vector = point_minus_point(most_distant_point, closest_point);
  return maximal(maximal(size_vector.x, size_vector.y), size_vector.z);
}
