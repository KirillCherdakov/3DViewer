#include "../3d_viewer.h"

void move_object_by_vector(object_t* object, vector_t vector) {
  vertices_t* vertices = &(object->vertices);
  for (int i = 0; i < vertices->count; i++) {
    vertices->coords[i] = point_plus_point(vertices->coords[i], vector);
  }
  vertices->closest = point_plus_point(vertices->closest, vector);
  vertices->most_distant = point_plus_point(vertices->most_distant, vector);
  object->center = point_plus_point(object->center, vector);
}
