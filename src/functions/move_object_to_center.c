#include "../3d_viewer.h"

void move_object_to_center(object_t* object) {
  set_center_for_object(object);
  point_t scene_origin = {0};
  move_object_by_vector(object,
                        point_minus_point(scene_origin, object->center));
  object->center = (point_t){0};
}
