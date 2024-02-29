#include <stdlib.h>

#include "../3d_viewer.h"

void destroy_vertices(object_t* object) {
  if (object->vertices.coords != NULL) {
    free(object->vertices.coords);
    object->vertices.coords = NULL;
  }
  object->vertices.closest = (point_t){0};
  object->vertices.most_distant = (point_t){0};
  object->center = (point_t){0};
}
