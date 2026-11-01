#include <queue>

#include "sweeping_line.hpp"

/*cmp se convierte en una closure, una clase unica para el compilador de c++
asi se le puede entregar el tipo al tercer parametro de priority_queue
auto cmp = [](tPoint a, tPoint b) {
    ...    
}
lo que va en la funcion debe reflejar como se hace la comparacion, es una opcion
*/

struct Segmento {
    int id;
    tPoint p1;  //siempre extremo superior
    tPoint p2;  //siempre extremo inferior

    void normalize() {
        //p1 siempre el extremo izq
        if(p1.y < p2.y || (p1.y == p2.y && p1.x > p2.x)) {
            std::swap(p1, p2);
        }
    }

    tPoint intersection(Segmento& other);

    
};

//tipos de eventos para la cola de prioridad Q (eventos)
enum EventType {UPPER_POINT, INTERSECTION, LOWER_POINT};
enum IntersectionType {PROPER, IMPROPER};


struct Event {
    tPoint p;
    EventType type;
    int seg1_id; //para identificar el segmento
    int seg2_id; //para intersecciones
    IntersectionType inter_type;  //tipo de interseccion

    bool operator<(const Event& other) {
        if(p.y != other.p.y) {
            return p.y < other.p.y;
        }
        
        return p.x < other.p.x;
    }
};




std::vector<Event> sweepingLineIntersections(const std::vector<Segmento>& S) {
    std::priority_queue<Event> Q; //recordar que recibe eventos

    //inicializamos cola de eventos
    for (const auto& segment : S) {
        Segmento s = segment;
        s.normalize();

        /*como Q espera eventos se le pasa los que corresponden
        se etiquetan los puntos y luego se ingresan a Q, seg_2.id = -1 cuando no hay*/
        Q.push({s.p1, UPPER_POINT, s.id, -1});  //extremo superior
        Q.push({s.p2, LOWER_POINT, s.id, -1});        
    }

    //linea de barrido
    std::vector<Segmento> active_segments;

}


