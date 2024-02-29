#ifndef VIEWER_H  // This name is essential. Identifiers must not start with a
                  // digit
#define VIEWER_H

// Object structure
typedef struct {
  double x;
  double y;
  double z;
} point_t;

typedef point_t vector_t;

typedef struct {
  int* vertex_indices;
  int count;
} poligon_t;

typedef struct {
  point_t* coords;
  int count;
  point_t most_distant;
  point_t closest;
} vertices_t;

typedef struct {
  poligon_t* connections;
  int count;
} poligons_t;

typedef struct {
  vertices_t vertices;
  poligons_t poligons;
  point_t center;
} object_t;

// Controller
typedef enum {
  no_error,
  opening_file_error,
  data_corrupted,
  vertex_doesnt_exist
} controller_error_t;

#define BUFFER_SIZE 200

// Load object to memory from file
controller_error_t open_object(const char* file_name, object_t* object);
// Scan single record from line
controller_error_t scan_object_record(char* line, object_t* object);
// Scan single poligon from line
controller_error_t scan_poligon(char* line, object_t* object);
// Scan single vertex from line
controller_error_t scan_vertex(char* line, object_t* object);

// Free memeory that was allocated by open_object
void destroy_object_contents(object_t* object);
// Free memory allocated for vertices
void destroy_vertices(object_t* object);
/// Free memory allocated for poligon
void destroy_poligons(object_t* object);

// Operations on object
// Find center point between two others
point_t find_center(point_t a, point_t b);
// Set center for object
void set_center_for_object(object_t* object);
// Moving object towards vector;
void move_object_by_vector(object_t* object, vector_t);
// Move object to center
void move_object_to_center(object_t* object);
// Return a that a.x -= b.x and so on
point_t point_minus_point(point_t a, point_t b);
// Return point that point.x *= number and so on
point_t multiply_point_on_double(point_t point, double number);
// Return point taht a.x += b.x and so on
point_t point_plus_point(point_t a, point_t b);
// return point that correspond to point rotation around x axys
point_t rotate_point_around_x(point_t point, double angle);
// return point that correspond to point rotation around y axys
point_t rotate_point_around_y(point_t point, double angle);
// return point that correspond to point rotation around z axys
point_t rotate_point_around_z(point_t point, double angle);
// rotate object around x axys
void rotate_object_around_x(object_t* object, double angle);
// rotate object around y axys
void rotate_object_around_y(object_t* object, double angle);
// rotate object around z axys
void rotate_object_around_z(object_t* object, double angle);

// Add single point to object // Creating new pointers
void add_point(object_t* object, point_t point);
// Add single poligon to object // Creating new pointers
void add_poligon(object_t* object, int count, int* poligon);
// Returns current_max_boundaries shifted towards new_potential_boundaries if
// necessary
point_t calculate_max_boundaries(point_t current_max_boundaries,
                                 point_t new_potential_boundaries);
// Returns current_min_boundaries shifted towards new_potential_boundaries if
// necessary
point_t calculate_min_boundaries(point_t current_min_boundaries,
                                 point_t new_potential_boundaries);
// Find maximal of all three projections on xyz axys
double find_max_projection(object_t* object);
// Scale object relative to 1 1 1 box
void scale_object(object_t* object, double scale);

// Basic math
// Returns maximum between two doubles
double maximal(double a, double b);
// Returns minimum between two doubles
double minimal(double a, double b);
// Returns median between two doubles
double median(double a, double b);

// Debug and testing
void print_object(object_t* object);

#endif  // VIEWER_H
