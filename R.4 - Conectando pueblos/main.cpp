/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

 El problema lo representaremos como un grafo valorado en donde los pueblos son los vertices, las carreteras las aristas
 y su valor es el tiempo que se tarda en despejar la nieve de ellas.

 Una vez construido el grafo hallaremos el ARM para identificar las aristas con menor tamaño que unen todos los vertices.

 Como nos piden el tiempo máximo que debemos esperar para ir desde un vertice a cualquier otro, esto significa que la
 arista de mayor peso en el ARM es el tiempo máximo que esperaremos por la condición de que todas las carreteras se
 empiezan a limpiar al mismo tiempo.

 Por lo tanto, modificaremos el algoritmo de Kruskal para que además de identificar la arista que forma parte del ARM
 nos quedemos con la arista de mayor peso.

 Complejidad:

 - Coste Temporal: O(V + A Log A), donde V es el número de pueblos y A es el número de carreteras.
 - Coste Espacial: O(V + A).

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
    Valor tiempoMax;

public:
    Valor costeARM() const {
        return coste;
    }

    Valor tiempoMaximo() const {
        return tiempoMax;
    }

    std::vector<Arista<Valor> > const &ARM() const {
        return _ARM;
    }

    ARM_Kruskal(GrafoValorado<Valor> const &g) : coste(0), tiempoMax(0) {
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
                tiempoMax = max(tiempoMax, a.valor());
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};

void resuelveCaso() {
    // leer los datos de la entrada

    int N, M;
    cin >> N >> M;

    // resolver el caso posiblemente llamando a otras funciones

    GrafoValorado<int> g(N);

    for (int i = 0; i < M; ++i) {
        int a, b, tiempo;
        cin >> a >> b >> tiempo;
        g.ponArista({a - 1, b - 1, tiempo});
    }

    ARM_Kruskal<int> arm(g);

    // escribir la solución

    if (arm.ARM().size() != N - 1) {
        cout << "Imposible\n";
        return;
    }

    cout << arm.tiempoMaximo() << "\n";
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

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif

    return 0;
}
