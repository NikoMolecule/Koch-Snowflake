#include "KochLine.h"

float KochLine::mag() {
  float x = (p1.x - p2.x) * (p1.x - p2.x);
  float y = (p1.y - p2.y) * (p1.y - p2.y);
  return sqrt(x + y);
}

void KochLine::generate(std::vector<KochLine> &v, float angle) {
  Vertex start, end;

  Vertex vector{p2.x - p1.x, p2.y - p1.y};
  float vecMag = vector.mag();
  vector.x /= vecMag;
  vector.y /= vecMag;

  start = p1;
  end = p2;
  Vertex tr1{start.x + vector.x * vecMag / 3.0f, start.y + vector.y * vecMag / 3.0f};
  Vertex tr3{start.x + 2.0f * vector.x * vecMag / 3.0f,  start.y + 2.0f * vector.y * vecMag / 3.0f};

  Vertex secondVector{tr3.x - tr1.x, tr3.y - tr1.y};
  secondVector.rotation(angle);

  Vertex tr2{tr1.x + secondVector.x, tr1.y + secondVector.y};

  KochLine e1{start, tr1};
  KochLine e2{tr1, tr2};
  KochLine e3{tr2, tr3};
  KochLine e4{tr3, end};

  v.push_back(e1);
  v.push_back(e2);
  v.push_back(e3);
  v.push_back(e4);
}