#ifndef POLYGON_TRIANGULATION_HPP
#define POLYGON_TRIANGULATION_HPP

#include <vector>

#include "../structs/tPoint.hpp"
#include "geom_aux.hpp"

void clipEar(int i, int& n, std::vector<tPoint>& P);
void generateTriangulation(int n, std::vector<tPoint>& P);

#endif