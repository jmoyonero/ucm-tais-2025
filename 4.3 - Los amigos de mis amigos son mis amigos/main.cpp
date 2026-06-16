/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Grafo.h"

using namespace std;

/*@ <answer>

La amistad es transitiva ("los amigos de mis amigos son mis amigos"), así que cada grupo de amigos
es exactamente una componente conexa del grafo no dirigido cuyos vértices son las personas y cuyas
aristas son las amistades conocidas. La respuesta es el tamaño de la mayor componente conexa.

Recorremos el grafo con DFS: para cada vértice todavía sin visitar lanzamos un DFS que cuenta cuántos
vértices alcanza (el tamaño de su componente) y nos quedamos con el máximo de esos tamaños.

Complejidad por caso (N personas, M amistades):
 - Temporal: O(N + M), cada vértice y cada arista se visitan una vez.
 - Espacial: O(N + M) por la lista de adyacencia y el vector de visitados.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Componentes {
private:
    vector<bool> visit;

    int dfs(Grafo const &g, int v) {
        visit[v] = true;
        int tam = 1; // se cuenta el propio vértice
        for (int w: g.ady(v))
            if (!visit[w]) tam += dfs(g, w);
        return tam;
    }

public:
    Componentes(Grafo const &g) : visit(g.V(), false) {
    }

    int mayorComponente(Grafo const &g) {
        int mayor = 0;
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v]) mayor = max(mayor, dfs(g, v));
        return mayor;
    }
};

void resuelveCaso() {
    int N, M;
    cin >> N >> M;

    Grafo g(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a - 1, b - 1); // personas numeradas 1..N
    }

    cout << Componentes(g).mayorComponente(g) << "\n";
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

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
