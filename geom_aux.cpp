#include <iostream>
#include <vector>

#include "geom_aux.hpp"


long long area2(tPoint a, tPoint b, tPoint c) {
    /*doble del area del triangulo segun la definicion con vectores */
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}


bool left(tPoint a , tPoint b, tPoint c) {
    /*true si c esta estrictamente a la izq del tramo ab 
    (esta luego de ab en el sentido CCW) */
    return area2(a, b, c) > 0;
}


bool leftOn(tPoint a , tPoint b, tPoint c) {
    /*si area es 0 son colineales */
    return area2(a, b, c) >= 0;
}


bool collinear(tPoint a , tPoint b, tPoint c) {
    /*true si los ptos son colineales*/
    return area2(a, b, c) == 0;
}


bool inBetween(tPoint a, tPoint b, tPoint c) {
    /*true si c esta apoyado en el segmento ab => INTERSECCION IMPROPIA*/
    if (!collinear(a, b, c)) return false;
    if (a.y != b.y) {
        return (c.x >= a.x && c.x <= b.x) || (c.x >= b.x && c.x <= a.x);
    }
    else {
        return (c.y >= a.y && c.y <= b.y) || (c.y >= b.y && c.x <= a.y);
    }
}


bool areIntersectedProperly(tPoint a, tPoint b, tPoint c, tPoint d) {
    /*revisa si segmentos ab y cd se cruzan, uso de != para xor con bool*/
    if (collinear(a, b, c) || collinear(a, b, d) || 
        collinear(c, d, a) || collinear(c, d, b)) return false;

    bool opposites_ab = (left(c, d, a) != left(c, d, b));  //revisa si a y b estan en lados opuestos de cd
    bool opposites_cd = (left(a, b, c) != left(a, b, d));  //revisa si c y d estan en lados opuestos de ab
    return opposites_ab && opposites_cd;
}


bool areIntersected(tPoint a, tPoint b, tPoint c, tPoint d) {
    /*cualquier tipo de interseccion*/
    if (areIntersectedProperly(a, b, c, d)) return true;

    return inBetween(a, b, c) || inBetween(a, b, d) || 
        inBetween(c, d, a) || inBetween(c, d, b); 
}


bool isConvex(int i, int n, const std::vector<tPoint>& P) {
    /*revisa si el vertice i es convexo, n tamaño de vector e i es el estudiado*/
    int prev = (i + n - 1) % n; //+n para no caer en < 0
    int next = (i + 1) % n;

    return leftOn(P[prev], P[i], P[next]); //a la izq o colineal
}


bool isInCone(int i, int j, int n, const std::vector<tPoint>& P) {
    int prev = (i + n -1) % n;
    int next = (i +1) % n;

    if (isConvex(i, n, P)) {
        return left(P[prev], P[i], P[j]) && left(P[i], P[next], P[j]);
    } else {
        //region prohibida: i-> j-> i+1 convexo y i -> i-1 -> j 
        return !(leftOn(P[i], P[j], P[next]) && leftOn(P[j], P[i], P[prev]));
    }
}


bool isDiagonalInteriorExterior(int i, int j, int n, const std::vector<tPoint>& P) {
    /*indica si el segmento entre vertices es una diagonal interior(true) o exterior (false)*/
    if (isInCone(i, j, n, P)) {
        for (int k = 0; k < n; k++) {
            int k1 = (k +1) % n; //segundo vertice
            
            //no valen los que incluyen los vertices analizados
            if (k == i || k == j || k1 == i || k1 == j) continue;

            if(areIntersected(P[i], P[j], P[k], P[k1])) return false;
        }

        return true;

    } else {
        std::cout << "Segmento (" << i <<  "," << j << ") no está en el cono de Pi" << std::endl;
        return false;
    }
}


bool isDiagonal(int i, int j, int n, const std::vector<tPoint>& P) {
    /*ambos deben estar en sus conos respectivos y no debe existir interseccion con otras
    aristas en el segmento que los une*/
    return isInCone(i, j, n, P) && isInCone(j, i, n, P) && isDiagonalInteriorExterior(i, j, n, P);
}





