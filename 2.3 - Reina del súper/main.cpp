/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

/*@ <answer>

Solución: Determinar en qué caja será atendido Ismael.

Simulamos la fila única con una priority_queue de mínimos de cajas ordenadas por el instante en que quedan
libres (campo ocupado); a igualdad de instante, gana la caja de menor número. Todas empiezan libres (ocupado = 0).

Para cada uno de los C clientes, en orden, lo asignamos a la caja más prioritaria (la que antes queda libre),
sumamos su tiempo a esa caja y la reinsertamos. Tras procesar los C clientes, Ismael ocupará la caja que quede
libre antes, es decir, la caja mas prioritaria en ese momento e imprimimos su id.

Complejidad:
 - Temporal: O((N + C) log N) por las N inserciones iniciales y las C extracciones/reinserciones
 - Espacial: O(N) por las cajas en la priority_queue

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Caja {
    int id;
    int ocupado;    // segundos que la caja seguirá ocupada antes de quedar libre

    bool operator<(Caja const &otro) const {
        if (ocupado == otro.ocupado) return id < otro.id;
        return ocupado < otro.ocupado;
    }
};


bool resuelveCaso() {
    int N, C;
    cin >> N >> C;
    if (N == 0 && C == 0) return false;

    // Min-heap de cajas: en la cima la que antes queda libre.
    PriorityQueue<Caja> cajas;
    for (int i = 0; i < N; ++i)
        cajas.push({i + 1, 0});

    for (int i = 0; i < C; ++i) {
        int tiempo;
        cin >> tiempo;
        Caja c = cajas.top(); cajas.pop();
        c.ocupado += tiempo;
        cajas.push(c);
    }

    // Ismael ocupa la caja que queda libre antes tras los C clientes.
    cout << cajas.top().id << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
