#include <stdlib.h>

#include "../3d_viewer.h"

void destroy_poligons(object_t* object) {
  if (object->poligons.connections != NULL) {
    for (int i = 0; i < object->poligons.count; i++) {
      poligon_t* poligon = &(object->poligons.connections[i]);
      free(poligon->vertex_indices);
      poligon->vertex_indices = NULL;
    }
    free(object->poligons.connections);
    object->poligons.connections = NULL;
  }
}
