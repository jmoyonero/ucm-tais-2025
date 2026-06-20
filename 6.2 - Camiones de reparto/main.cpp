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

using namespace std;

/*@ <answer>
El problema lo podemos representar con un grafo valorado en el que los vertices son las intersecciones, las calles las
aristas y su anchura maxima el valor.
La idea es aplicar un recorrido en profundidad (DFS) iniciado en el vertice origen de cada una de las K consultas.
En el recorrido tendremos en cuenta el "umbral", que en este caso es el ancho del camion (a).
Solo continuamos el recorrido por una arista si:
    anchuraCalle >= anchoCamion (lo que significa que el camion puede circular por esa calle)

Para saber si el camion es capaz de llegar al destino consultamos un vector de booleanos en el que marcamos los
vertices visitados por el recorrido. Si el destino esta marcado escribimos "SI", en caso contrario "NO".

Complejidad (V vértices, E aristas, K consultas con K <= 10):
 - Temporal: O(V + E) para construir el grafo y O(V + E) por cada DFS de consulta.
 - Espacial: O(V + E) por la lista de adyacencia, más O(V) del vector de visitados.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


void dfs(GrafoValorado<int> const &G, int v, int umbral, vector<bool> &visit) {
    visit[v] = true;
    for (auto a: G.ady(v)) {
        if (a.valor() >= umbral) {
            int w = a.otro(v);
            if (!visit[w])
                dfs(G, w, umbral, visit);
        }
    }
}

bool resuelveCaso() {
    int V, E;
    if (!(cin >> V >> E)) return false; // fin de la entrada

    GrafoValorado<int> g(V);

    for (int i = 0; i < E; ++i) {
        int o, d, a;
        cin >> o >> d >> a;
        --o;
        --d;
        g.ponArista({o, d, a});
    }

    int K;
    cin >> K;
    for (int i = 0; i < K; ++i) {
        vector<bool> visit(V, false);
        int o, d, a;
        cin >> o >> d >> a;
        dfs(g, o - 1, a, visit);

        cout << ((visit[d - 1]) ? "SI\n" : "NO\n");
    }

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
