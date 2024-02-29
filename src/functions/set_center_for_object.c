#include "../3d_viewer.h"

void set_center_for_object(object_t* object) {
  object->center =
      find_center(object->vertices.closest, object->vertices.most_distant);
}
