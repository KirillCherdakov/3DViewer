#include <stdio.h>

#include "../3d_viewer.h"

void print_object(object_t* object) {
  vertices_t vertices = object->vertices;
  for (int i = 0; i < vertices.count; i++) {
    point_t point = vertices.coords[i];
    printf("v %lf %lf %lf\n", point.x, point.y, point.z);
  }
  printf("\n");

  poligons_t poligons = object->poligons;
  for (int i = 0; i < poligons.count; i++) {
    poligon_t poligon = poligons.connections[i];
    printf("f");
    for (int j = 0; j < poligon.count; j++) {
      printf(" %d", poligon.vertex_indices[j]);
    }
    printf("\n");
  }
  printf("\n");
}
