#include <stdio.h>

#include "../3d_viewer.h"

controller_error_t scan_vertex(char* line, object_t* object) {
  controller_error_t status = no_error;

  char record_type[BUFFER_SIZE] = "";

  point_t point = {0};

  if (sscanf(line, "%s %lf %lf %lf", record_type, &point.x, &point.y,
             &point.z) == 4) {
    add_point(object, point);
  } else {
    status = data_corrupted;
  }
  return status;
}
