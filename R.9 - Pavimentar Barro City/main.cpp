/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

 El problema consiste en encontrar el coste mínimo para conectar todos los nodos de un grafo valorado no dirigido, lo
 cual equivale a hallar el Árbol de Recubrimiento Mínimo (ARM).

 Estrategia:

 - Se utiliza el Algoritmo de Kruskal, que sigue una estrategia voraz (greedy):
 - Se consideran todas las aristas (calles) del grafo y se ordenan de menor a mayor coste.
 - Se utiliza una estructura de Conjuntos Disjuntos para controlar las componentes conexas y evitar la formación de ciclos.
 - Se añaden aristas al ARM siempre que unan dos vértices que no pertenezcan ya a la misma componente.
 - El proceso termina cuando se han seleccionado V−1 aristas o no quedan más aristas por procesar.

 A tener en cuenta:
    - Si al finalizar el algoritmo el número de aristas en el ARM es menor que N−1, significa que el grafo original NO
      era conexo y, por tanto, es "Imposible" pavimentar la ciudad completamente.

 Complejidad:
 - Temporal: O(V + A log A) por el algoritmo de Kruskal.
 - Espacial: O(V + A) para almacenar el grafo, los conjuntos disjuntos y la cola de prioridad.

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
    // leer los datos de la entrada

    int N, C;
    cin >> N >> C;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    GrafoValorado<int> gv(N);

    for (int i = 0; i < C; ++i) {
        int inicio, fin, coste;
        cin >> inicio >> fin >> coste;
        gv.ponArista({inicio - 1, fin - 1, coste});
    }

    ARM_Kruskal<int> arm(gv);

    // escribir la solución

    if (arm.ARM().size() != N - 1)
        cout << "Imposible\n";
    else
        cout << arm.costeARM() << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("1.in");
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
