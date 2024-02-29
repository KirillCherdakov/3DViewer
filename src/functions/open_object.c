#include <stdio.h>

#include "../3d_viewer.h"

#define BUFFER_SIZE 200

controller_error_t open_object(const char* file_name, object_t* object) {
  FILE* object_file = fopen(file_name, "r");
  if (object_file != NULL) {
    char line[BUFFER_SIZE] = "";

    controller_error_t scanning_status = no_error;

    while (fgets(line, BUFFER_SIZE, object_file) != NULL &&
           scanning_status == no_error) {
      scanning_status = scan_object_record(line, object);
    }

    if (scanning_status != no_error) {
      return scanning_status;
    } else {
      return no_error;
    }

  } else {
    return opening_file_error;
  }
}
