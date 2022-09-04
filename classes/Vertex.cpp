#include "Vertex.h"

float Vertex::mag() { return sqrt(x * x + y * y); }

void Vertex::rotation(float angleInRad) {
  float xtemp = x * cos(angleInRad) - y * sin(angleInRad);
  y = y * cos(angleInRad) + x * sin(angleInRad);
  x = xtemp;
}