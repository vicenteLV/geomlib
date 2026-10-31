#include <vector>

#include "polygon_triangulation.hpp"

void clipEar(int i, int& n, std::vector<tPoint>& P) {
    //eliminacion del vertice i
    for (int k = i; k < n-1; k++) {
        P[k] = P[k + 1];
    }
    n--;
}

void generateTriangulation(int n, std::vector<tPoint>& P) {
    
}