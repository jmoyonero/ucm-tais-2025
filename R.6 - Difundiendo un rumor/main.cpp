/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "Grafo.h"

/*@ <answer>

 El problema se modela mediante un grafo no dirigido, donde los vértices V representan a los personajes y las aristas E
 las relaciones de amistad.

 Puesto que el rumor se propaga gratuitamente entre amigos, el grafo se divide en componentes conexas. Para que todos
 los personajes conozcan el rumor al menor coste posible, basta con sobornar a un solo personaje por cada componente
 conexa, específicamente aquel cuyo coste de soborno sea mínimo dentro de dicha componente.

 Para lograrlo realizaremos un recorrido en profundidad (DFS) modificado para identificar cada componente conexa y
 quedarnos con el vertice con el menor valor.

 Complejidad:

 - Temporal: O(V+E), ya que visitamos cada vértice y cada arista una sola vez durante el recorrido.
 - Espacial: O(V+E) para almacenar la lista de adyacencia del grafo y el vector de visitados.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class DFS {
private:
    std::vector<bool> visit;
    std::vector<int> ant;
    std::vector<int> precios;
    long long costeMinimo;
    int s;

    int dfs(Grafo const &G, int v) {
        int minimo = precios[v];
        visit[v] = true;
        for (int w: G.ady(v)) {
            if (!visit[w]) {
                ant[w] = v;
                minimo = min(dfs(G, w), minimo);
            }
        }
        return minimo;
    }

public:
    DFS(Grafo const &g, int s, vector<int> precios) : visit(g.V(), false), ant(g.V()), s(s), precios(precios),
                                                             costeMinimo(0) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) {
                costeMinimo += dfs(g, v);
            }
        }
    }

    int costeTotal() const {
        return costeMinimo;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, M;
    cin >> N >> M;

    if (!std::cin) return false; // fin de la entrada

    vector<int> precios(N);

    for (int i = 0; i < N; ++i) {
        cin >> precios[i];
    }

    // resolver el caso posiblemente llamando a otras funciones

    Grafo g(N);

    for (int i = 0; i < M; ++i) {
        int amigoA, amigoB;
        cin >> amigoA >> amigoB;
        g.ponArista(amigoA - 1, amigoB - 1);
    }

    DFS dfs(g, 0, precios);

    // escribir la solución

    cout << dfs.costeTotal() << "\n";

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
