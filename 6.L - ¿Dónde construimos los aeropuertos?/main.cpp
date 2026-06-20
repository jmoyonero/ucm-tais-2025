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

El problema se puede modelar con un grafo valorado en el que las ciudades son los vértices, las carreteras las aristas
y su coste por construirlo el valor. El objetivo es encontrar el coste mínimo por construir carreteras y aeropuertos,
un Árbol de Recubrimiento Mínimo (ARM). Para ello usamos el algoritmo de Kruskal, que recorre las aristas de menor a
mayor coste (con una cola de prioridad) y añade cada una al árbol si une dos componentes aún separadas (usando Conjuntos
Disjuntos para detectarlo).

Como tener acceso por carretera o por aeropuerto es equivalente, una carretera solo merece la pena si cuesta MENOS que
un aeropuerto: descartamos las de coste >= A (con el filtro c < A). El estricto "<" implementa el desempate del
enunciado: a igual coste preferimos el aeropuerto, porque hay que maximizar el número de aeropuertos.

Tras Kruskal sobre las carreteras con c < A queda un bosque de recubrimiento mínimo; cada componente conexa necesita
exactamente un aeropuerto, así que el número de aeropuertos es N - (aristas del bosque) = N - ARM.size(), y el coste
total es (suma de carreteras) + A * aeropuertos.

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
    int N, M, A;
    if (!(cin >> N >> M >> A)) return false; // fin de la entrada

    GrafoValorado<int> g(N);

    for (int i = 0; i < M; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        if (c < A) {
            g.ponArista({x - 1, y - 1, c});
        }
    }

    ARM_Kruskal<int> arm(g);

    int aviones = N - arm.ARM().size();
    int coste = 0;
    for (const auto& a: arm.ARM()) {
        coste += a.valor();
    }
    cout << coste + A * aviones << " " << aviones << "\n";


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
