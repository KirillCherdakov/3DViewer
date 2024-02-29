#include <stdio.h>
#include <string.h>

#include "../3d_viewer.h"

controller_error_t scan_object_record(char* line, object_t* object) {
  controller_error_t status = no_error;

  char record_type[BUFFER_SIZE] = "";
  sscanf(line, "%s", record_type);

  if (strcmp(record_type, "v") == 0) {
    status = scan_vertex(line, object);
  } else if (strcmp(record_type, "f") == 0) {
    status = scan_poligon(line, object);
  }

  return status;
}
