#include "../3d_viewer.h"

void scale_object(object_t* object, double scale) {
  vertices_t* vertices = &(object->vertices);
  double max_projection = find_max_projection(object);

  if (max_projection != 0 && scale > 0)
    scale = (scale * 2) / max_projection;
  else
    scale = 0.000001;

  for (int i = 0; i < object->vertices.count; i++) {
    vertices->coords[i] = multiply_point_on_double(vertices->coords[i], scale);
  }
  vertices->closest = multiply_point_on_double(vertices->closest, scale);
  vertices->most_distant =
      multiply_point_on_double(vertices->most_distant, scale);
}
