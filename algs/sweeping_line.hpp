#ifndef SWEEPING_LINE_HPP
#define SWEEPING_LINE_HPP

#include "../structs/tPoint.hpp"

struct Segmento {
    int id;
    tPoint p1;  //siempre extremo superior
    tPoint p2;  //siempre extremo inferior

    void normalize();
};








#endif