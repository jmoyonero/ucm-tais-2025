/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

/*@ <answer>

Un grafo es bipartito si sus vértices se pueden colorear con dos colores sin que ninguna arista una
dos vértices del mismo color. Lo comprobamos con un recorrido en profundidad (DFS) que colorea:

 - al visitar un vértice sin color, le damos un color y a cada adyacente le asignamos el color contrario;
 - si un adyacente ya estaba coloreado y tiene el MISMO color que el actual, hay una arista monocroma
   (equivale a un ciclo de longitud impar) y el grafo NO es bipartito.

Como el grafo puede ser disconexo, lanzamos el DFS desde cada vértice todavía sin color, de modo que
recorremos todas las componentes. El vector color guarda -1 (sin visitar), 0 ó 1.

Complejidad (V vértices, A aristas):
 - Temporal: O(V + A), cada vértice y cada arista se procesan una vez.
 - Espacial: O(V + A) por la lista de adyacencia y el vector de colores.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Bipartito {
private:
    vector<int> color; // -1 sin colorear, 0 ó 1
    bool esBip;

    void dfs(Grafo const &g, int v) {
        for (int w: g.ady(v)) {
            if (color[w] == -1) {
                color[w] = 1 - color[v]; // color contrario
                dfs(g, w);
            } else if (color[w] == color[v]) {
                esBip = false; // arista entre dos vértices del mismo color
            }
        }
    }

public:
    Bipartito(Grafo const &g) : color(g.V(), -1), esBip(true) {
        for (int v = 0; v < g.V(); ++v) // recorre todas las componentes
            if (color[v] == -1) {
                color[v] = 0;
                dfs(g, v);
            }
    }

    bool resultado() const { return esBip; }
};

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;
    if (!cin) return false; // fin de la entrada

    Grafo g(V);
    for (int i = 0; i < A; ++i) {
        int v, w;
        cin >> v >> w;
        g.ponArista(v, w); // vértices ya en 0..V-1
    }

    cout << (Bipartito(g).resultado() ? "SI" : "NO") << "\n";
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
