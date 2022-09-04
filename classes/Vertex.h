#ifndef VERTEX_H
#define VERTEX_H

#include <math.h>

class Vertex {
 public:
  float x, y;

  float mag();
  void rotation(float angleInRad);
};

#endif