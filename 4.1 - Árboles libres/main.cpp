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

Un grafo no dirigido es un árbol libre si es conexo y acíclico. Usemos esta característica:

    es árbol libre  <=>  es conexo  y  A == V - 1

Justificación: un grafo conexo con V vértices necesita al menos V-1 aristas, y si tiene exactamente
V-1 entonces no puede tener ciclos (cualquier arista de más sobre un grafo conexo crea un ciclo).
Como el enunciado garantiza que no hay bucles ni aristas repetidas, basta comprobar esas dos cosas:
 - A == V - 1 (condición barata, se mira primero);
 - conexión: un recorrido en profundidad (DFS) desde el vértice 0 debe visitar los V vértices.

Si A != V - 1 ya respondemos NO sin recorrer. En otro caso contamos los vértices alcanzables desde
el 0 con un DFS: si son los V, el grafo es conexo (y por tanto árbol libre) -> SI; si no -> NO.

Complejidad (V vértices, A aristas):
 - Temporal: O(V + A), cada vértice y cada arista se visitan una vez.
 - Espacial: O(V + A) por la lista de adyacencia y el vector de visitados.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Conexion {
private:
    vector<bool> visit;
    int alcanzados;

    void dfs(Grafo const &g, int v) {
        visit[v] = true;
        ++alcanzados;
        for (int w: g.ady(v))
            if (!visit[w]) dfs(g, w);
    }

public:
    Conexion(Grafo const &g) : visit(g.V(), false), alcanzados(0) {
        dfs(g, 0); // basta arrancar en un vértice; si es conexo se alcanzan todos
    }

    bool esConexo(Grafo const &g) const {
        return alcanzados == g.V();
    }
};

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;
    if (!cin) return false; // fin de la entrada

    Grafo g(V);
    for (int i = 0; i < A; ++i) {
        int v, w;
        cin >> v >> w;
        g.ponArista(v, w);
    }

    // árbol libre <=> conexo y con exactamente V-1 aristas
    bool arbolLibre = (A == V - 1) && Conexion(g).esConexo(g);

    cout << (arbolLibre ? "SI" : "NO") << "\n";

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
