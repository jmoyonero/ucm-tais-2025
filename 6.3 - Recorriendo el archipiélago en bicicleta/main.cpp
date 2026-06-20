/*@ <authors>
*
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

/*@ <answer>

El problema se puede modelar con un grafo valorado en el que las islas son los vértices, los puentes las aristas y el
coste de su construcción el valor. El objetivo es encontrar el coste minimo de comunicar todas las islas: un Árbol de
Recubrimiento Mínimo (ARM). Para ello usamos el algoritmo de Kruskal, que recorre las aristas de menor a mayor coste
(con una cola de prioridad) y añade cada una al árbol si une dos componentes aún separadas (usando Conjuntos
Disjuntos para detectarlo).

Un árbol que conecta V vértices tiene exactamente V-1 aristas; si al terminar el ARM tiene menos de I-1 aristas, el
grafo no era conexo y no hay puentes suficientes.

Complejidad (V vértices, E aristas):
 - Temporal: O(E log E) por ordenar las aristas en la cola de prioridad.
 - Espacial: O(V + E) por el grafo, la cola de prioridad y los Conjuntos Disjuntos.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template<typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor> > _ARM;
    Valor coste;

public:
    Valor costeARM() const {
        return coste;
    }

    std::vector<Arista<Valor> > const &ARM() const {
        return _ARM;
    }

    ARM_Kruskal(GrafoValorado<Valor> const &g) : coste(0) {
        PriorityQueue<Arista<Valor> > pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};


bool resuelveCaso() {
    int I, P;
    if (!(cin >> I >> P)) return false; // fin de la entrada

    GrafoValorado<int> g(I);

    for (int i = 0; i < P; i++) {
        int x, y, coste;
        cin >> x >> y >> coste;
        g.ponArista({x - 1, y - 1, coste});
    }

    ARM_Kruskal<int> k(g);

    cout << ((k.ARM().size() != I - 1) ? "No hay puentes suficientes" : to_string(k.costeARM())) << "\n";
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
