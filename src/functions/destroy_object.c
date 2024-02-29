#include <stdlib.h>

#include "../3d_viewer.h"

void destroy_object_contents(object_t* object) {
  destroy_vertices(object);
  destroy_poligons(object);

  object->poligons.count = 0;
  object->vertices.count = 0;
}
