#include <stdlib.h>
#include <string.h>

#include "../3d_viewer.h"

void add_poligon(object_t* object, int count, int* poligon) {
  poligons_t* poligons = &(object->poligons);
  size_t estimated_connections_buffer_size =
      (poligons->count + 1) * sizeof(poligon_t);
  poligons->connections =
      realloc(poligons->connections, estimated_connections_buffer_size);
  poligons->connections[poligons->count].count = count;
  poligons->connections[poligons->count].vertex_indices =
      malloc(count * sizeof(int));
  memcpy(poligons->connections[poligons->count].vertex_indices, poligon,
         count * sizeof(int));
  poligons->count++;
}
