#include <queue>
#include <optional>
#include <variant>

#include "sweeping_line.hpp"
#include "geom_aux.hpp"

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
    std::optional<double> slope; //pendiente, std::nulopt si es inf

    void normalize() {
        //p1 siempre el extremo izq
        if(p1.y < p2.y || (p1.y == p2.y && p1.x > p2.x)) {
            std::swap(p1, p2);
        }
    }

    void update_slope() {
        /*calcular el valor de la pendiente, null si los x son iguales*/
        if (p1.x == p2.x) {
            slope = std::nullopt;
        }

        else {
            /*static cast para evitar errores en el calculo*/
            slope = static_cast<double>(p2.y - p1.y) / (p2.x - p1.x);
        }
    }


    
    
    tPoint intersection(Segmento& other);
    
};


tPoint intersection_x_ctte(const Segmento& s1, const Segmento& s2) {
    /*s1 tiene una pendiente infinita, i.e., x ctte, se debe corroborar antes 
    de llamar a la funcion que y no sea ctte*/
    double s2_n = s2.p1.y - (s2.p1.x * s2.slope.value()); 

    double inter_x = s1.p1.x;
    double inter_y = (inter_x * s2.slope.value()) + s2_n;

    return {inter_x, inter_y};
}


//tipos de eventos para la cola de prioridad Q (eventos)
enum EventType {UPPER_POINT, INTERSECTION, LOWER_POINT};
enum IntersectionType {PROPER, IMPROPER};




struct Event {
    tPoint p;
    EventType type;
    int seg1_id; //para identificar el segmento
    int seg2_id; //para intersecciones

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


