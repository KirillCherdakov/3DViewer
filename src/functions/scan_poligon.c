#include <stdio.h>
#include <string.h>

#include "../3d_viewer.h"

controller_error_t scan_poligon(char* line, object_t* object) {
  controller_error_t status = no_error;
  int poligon[BUFFER_SIZE];
  int count = 0;
  int count_of_vertices = object->vertices.count;
  char* value = strtok(line, " ");
  value = strtok(NULL, " ");

  while (value != NULL && status == no_error) {
    int connection = 0;
    if (sscanf(value, "%d", &connection) == 1) {
      if (connection > count_of_vertices || connection < 1) {
        status = vertex_doesnt_exist;
      } else {
        poligon[count++] = connection - 1;
        value = strtok(NULL, " ");
      }
    } else {
      status = data_corrupted;
    }
  }

  if (status == no_error) {
    add_poligon(object, count, poligon);
  }
  return status;
}
