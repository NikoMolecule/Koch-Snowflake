#ifndef KOCHLINE_H
#define KOCHLINE_H

#include <vector>

#include "Vertex.h"

class KochLine {
 public:
  Vertex p1;
  Vertex p2;
  float mag();
  void generate(std::vector<KochLine> &v, float angle);
};

#endif