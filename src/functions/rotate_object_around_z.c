#include "../3d_viewer.h"

void rotate_object_around_z(object_t* object, double angle) {
  vertices_t* vertices = &(object->vertices);

  for (int i = 0; i < vertices->count; i++) {
    vertices->coords[i] = rotate_point_around_z(vertices->coords[i], angle);
  }

  vertices->closest = rotate_point_around_z(vertices->closest, angle);
  vertices->most_distant = rotate_point_around_z(vertices->most_distant, angle);
  object->center = rotate_point_around_z(vertices->most_distant, angle);
}
