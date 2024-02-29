#include <stdlib.h>

#include "../3d_viewer.h"

void add_point(object_t* object, point_t point) {
  static object_t* previous_call = NULL;

  vertices_t* vertices = &(object->vertices);
  size_t estimated_buffer_size = (vertices->count + 1) * sizeof(point_t);
  vertices->coords = realloc(vertices->coords, estimated_buffer_size);
  vertices->coords[vertices->count] = point;
  if (object != previous_call) {
    vertices->most_distant = point;
    vertices->closest = point;
    previous_call = object;
  } else {
    vertices->most_distant =
        calculate_max_boundaries(vertices->most_distant, point);
    vertices->closest = calculate_min_boundaries(vertices->closest, point);
  }
  vertices->count++;
}
