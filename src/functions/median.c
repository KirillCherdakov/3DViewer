#include "../3d_viewer.h"

double median(double a, double b) {
  double max = maximal(a, b);
  double min = minimal(a, b);

  double offset = (max - min) / 2;

  return min + offset;
}
