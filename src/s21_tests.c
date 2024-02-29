#include <check.h>

#include "3d_viewer.h"

#define PI 3.141592654

START_TEST(test_1) {
  object_t object = {0};
  controller_error_t status = no_error;
  const char *file_name = "example.obj";
  status = open_object(file_name, &object);
  ck_assert_int_eq(status, 1);
  destroy_object_contents(&object);
}
END_TEST

START_TEST(test_2) {
  object_t object = {0};
  controller_error_t status = no_error;
  status = scan_object_record("v 1 1 1 1", &object);
  ck_assert_int_eq(status, 0);
  destroy_object_contents(&object);
}
END_TEST

START_TEST(test_3) {
  object_t object = {0};
  controller_error_t status = no_error;
  status = scan_object_record("v f 3.4 -23 0.1", &object);
  ck_assert_int_eq(status, 2);
  destroy_object_contents(&object);
}
END_TEST

START_TEST(test_4) {
  object_t object = {0};
  controller_error_t status = no_error;
  status = scan_vertex("v -12.280334 2.145221 0.887660", &object);
  ck_assert_int_eq(status, 0);
  destroy_vertices(&object);
  destroy_object_contents(&object);
}
END_TEST

START_TEST(test_5) {
  point_t A1 = {5, 10, 140};
  point_t A2 = {-10, 21, 78};
  point_t result = find_center(A1, A2);
  ck_assert_double_eq(result.x, -2.5);
  ck_assert_double_eq(result.y, 15.5);
  ck_assert_double_eq(result.z, 109);
}
END_TEST

START_TEST(test_6) {
  object_t object = {0};
  point_t A = {-23, 0, 48};
  object.vertices.closest = A;
  point_t B = {56, 21, -4};
  object.vertices.most_distant = B;
  set_center_for_object(&object);
  ck_assert_double_eq(object.center.x, 16.5);
  ck_assert_double_eq(object.center.y, 10.5);
  ck_assert_double_eq(object.center.z, 22.0);
  destroy_object_contents(&object);
}
END_TEST

START_TEST(test_7) {
  object_t cube = {0};
  controller_error_t status = open_object("./cube.obj", &cube);
  vector_t A = {-27, 32, 12};
  move_object_by_vector(&cube, A);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(cube.center.x, -27);
  ck_assert_double_eq(cube.center.y, 32);
  ck_assert_double_eq(cube.center.z, 12);
  destroy_object_contents(&cube);
}
END_TEST

START_TEST(test_8) {
  object_t cube_translated = {0};
  controller_error_t status =
      open_object("./cube_translated.obj", &cube_translated);
  move_object_to_center(&cube_translated);
  ck_assert_int_eq(status, 0);
  ck_assert_double_eq(cube_translated.center.x, 0);
  ck_assert_double_eq(cube_translated.center.y, 0);
  ck_assert_double_eq(cube_translated.center.z, 0);
  destroy_object_contents(&cube_translated);
}
END_TEST

START_TEST(test_9) {
  point_t A = {-126.7, 456.9, 21};
  point_t B = {712, -54.3, 95};
  point_t C = point_minus_point(A, B);
  ck_assert_double_eq(C.x, -838.7);
  ck_assert_double_eq(C.y, 511.2);
  ck_assert_double_eq(C.z, -74);
  double number = 45.;
  point_t D = multiply_point_on_double(C, number);
  ck_assert_double_eq(D.x, -37741.5);
  ck_assert_double_eq(D.y, 23004);
  ck_assert_double_eq(D.z, -3330);
  point_t E = point_plus_point(C, D);
  ck_assert_double_eq(E.x, -38580.2);
  ck_assert_double_eq(E.y, 23515.2);
  ck_assert_double_eq(E.z, -3404);
  point_t test_point = {10, 10, 10};
  double angle = -1;
  point_t F = rotate_point_around_x(test_point, angle);
  ck_assert_double_eq(F.x, 10);
  // ck_assert_double_eq_tol(F.y, 13.8177, 1E-6);
  // ck_assert_double_eq_tol(F.z, -3.01169, 1E-6);
  F = rotate_point_around_y(test_point, angle);
  ck_assert_double_eq(F.y, 10);
  F = rotate_point_around_z(test_point, angle);
  ck_assert_double_eq(F.z, 10);
  object_t test_cube = {0};
  controller_error_t status = open_object("./cube_translated.obj", &test_cube);
  ck_assert_int_eq(status, 0);
  angle = (90 * PI) / 180;
  rotate_object_around_x(&test_cube, angle);
  ck_assert_double_eq_tol(test_cube.center.y, -7, 1e-6);
  ck_assert_double_eq_tol(test_cube.center.z, -10, 1e-6);
  rotate_object_around_y(&test_cube, angle);
  ck_assert_double_eq_tol(test_cube.center.x, -6, 1e-6);
  ck_assert_double_eq_tol(test_cube.center.z, -7, 1e-6);
  rotate_object_around_z(&test_cube, angle);
  ck_assert_double_eq_tol(test_cube.center.x, -7, 1e-6);
  ck_assert_double_eq_tol(test_cube.center.y, 10, 1e-6);
  destroy_object_contents(&test_cube);
}
END_TEST

START_TEST(test_10) {
  point_t A = {100, -50, 40};
  point_t B = {-80, 70, -130};
  point_t max_b = calculate_max_boundaries(A, B);
  point_t min_b = calculate_min_boundaries(A, B);
  ck_assert_double_eq(max_b.x, 100);
  ck_assert_double_eq(min_b.x, -80);
  ck_assert_double_eq(max_b.y, 70);
  ck_assert_double_eq(min_b.y, -50);
  ck_assert_double_eq(max_b.z, 40);
  ck_assert_double_eq(min_b.z, -130);
}
END_TEST

START_TEST(test_11) {
  object_t obj = {0};
  controller_error_t status = open_object("./capybara.obj", &obj);
  ck_assert_int_eq(status, 0);
  scale_object(&obj, 0.5);
  ck_assert_double_eq_tol(obj.vertices.closest.x, -0.255284, 1E-6);
  ck_assert_double_eq_tol(obj.vertices.closest.y, -0.426934, 1E-6);
  ck_assert_double_eq_tol(obj.vertices.closest.z, -0.453868, 1E-6);
  ck_assert_double_eq_tol(obj.vertices.most_distant.x, 0.113902, 1E-6);
  ck_assert_double_eq_tol(obj.vertices.most_distant.y, 0.573066, 1E-6);
  ck_assert_double_eq_tol(obj.vertices.most_distant.z, 0.255665, 1E-6);
  destroy_object_contents(&obj);
}
END_TEST

START_TEST(test_12) {
  double number1 = 12342.3;
  double number2 = -2342.2;
  double mid = median(number1, number2);
  ck_assert_double_eq(maximal(number1, number2), number1);
  ck_assert_double_eq(minimal(number1, number2), number2);
  ck_assert_double_eq(median(number1, number2), mid);
}
END_TEST

int main(void) {
  Suite *test_suite = suite_create("3D_Viewer Tests");
  TCase *test_case = tcase_create("3D_Viewer Tests");
  SRunner *suite_run = srunner_create(test_suite);
  int result = 0;

  suite_add_tcase(test_suite, test_case);

  tcase_add_test(test_case, test_1);
  tcase_add_test(test_case, test_2);
  tcase_add_test(test_case, test_3);
  tcase_add_test(test_case, test_4);
  tcase_add_test(test_case, test_5);
  tcase_add_test(test_case, test_6);
  tcase_add_test(test_case, test_7);
  tcase_add_test(test_case, test_8);
  tcase_add_test(test_case, test_9);
  tcase_add_test(test_case, test_10);
  tcase_add_test(test_case, test_11);
  tcase_add_test(test_case, test_12);

  srunner_run_all(suite_run, CK_ENV);
  result = srunner_ntests_failed(suite_run);
  srunner_free(suite_run);

  return (result == 0 ? 0 : 1);
}
