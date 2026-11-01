#ifndef GEOM_AUX_HPP
#define GEOM_AUX_HPP

#include "../structs/tPoint.hpp"

//primitivas de area y orientacion
long long area2(tPoint a, tPoint b, tPoint c);
bool left(tPoint a , tPoint b, tPoint c);
bool leftOn(tPoint a , tPoint b, tPoint c);
bool collinear(tPoint a , tPoint b, tPoint c);

//interseccion de segmentos
bool inBetween(tPoint a, tPoint b, tPoint c);
bool areIntersectedProperly(tPoint a, tPoint b, tPoint c, tPoint d);
bool areIntersected(tPoint a, tPoint b, tPoint c, tPoint d);

//posicion de vertices
bool isConvex(int i, int n, const std::vector<tPoint>& P);
bool isInCone(int i, int j, int n, const std::vector<tPoint>& P);
bool isDiagonalInteriorExterior(int i, int j, int n, const std::vector<tPoint>& P);
bool isDiagonal(int i, int j, int n, const std::vector<tPoint>& P);


#endif