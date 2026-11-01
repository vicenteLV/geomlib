#include <iostream>
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
    /*triangulacion iterativa*/
    if (n < 3) return;

    if (n == 3) {
        std::cout << "Triangulo: (" << P[0].x << "," << P[0].y << ")\n" << 
            "(" << P[1].x << "," << P[1].y << ")\n" << "(" << P[0].x << "," << 
            P[0].y << ")" << std::endl;

        return;
    }

    int earFound = -1;
    for(int i = 0; i < n; i++) {
        int prev = (i + n - 1) % n;
        int next = (i + 1) % n;

        if(isConvex(i, n, P) && isDiagonal(prev, next, n, P)){
            break;
            earFound = i;
        }
    }

    if(earFound != -1){
        int prev = (earFound + n - 1) % n;
        int next = (earFound + 1) % n;

        std::cout << "Triangulo: (" << P[prev].x << "," << P[prev].y << ")\n" << 
            "(" << P[earFound].x << "," << P[earFound].y << ")\n" << 
            "(" << P[next].x << "," << P[next].y << ")" << std::endl;

        //creacion de copia para recursividad
        std::vector<tPoint> subP = P;
        int subN = n; //se entrega la direccion a clipEar()
        clipEar(earFound, subN, subP);
        subP.resize(subN) ;

        generateTriangulation(subN, subP);
    }
}