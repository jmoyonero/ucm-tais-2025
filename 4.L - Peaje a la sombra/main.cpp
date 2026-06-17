/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include "Grafo.h"

using namespace std;

/*@ <answer>

Alex y Lucas se reúnen en alguna intersección intermedia m y desde ahí van juntos al trabajo T. El
tramo común lo pagan una sola vez (de ahí el ahorro de la mitad respecto a ir cada uno por su lado),
así que el gasto total para un punto de reunión m es:

    dist(Alex, m) + dist(Lucas, m) + dist(m, T)

donde dist es el número mínimo de tramos entre dos intersecciones. Hay que minimizar esa suma sobre
todas las posibles intersecciones m (incluidas las propias casas o el trabajo: reunirse en el trabajo
equivale a no compartir camino, y reunirse en una casa a que uno no ande solo).

Como todos los tramos cuestan lo mismo (un euro), la distancia mínima se obtiene con BFS. Basta UN BFS
desde cada uno de los tres puntos fijos (Alex, Lucas, T); con esas tres tablas de distancias evaluamos
la suma para cada m y nos quedamos con el mínimo. La ciudad está conexa, así que toda m es alcanzable.

Complejidad por caso (N intersecciones, C tramos):
 - Temporal: O(N + C), tres BFS más un recorrido final sobre los N nodos.
 - Espacial: O(N + C) por la lista de adyacencia y las tablas de distancias.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// distancias mínimas (en nº de tramos) desde origen a todos los nodos
vector<int> bfs(Grafo const &g, int origen) {
    vector<int> dist(g.V(), -1);
    queue<int> cola;
    dist[origen] = 0;
    cola.push(origen);
    while (!cola.empty()) {
        int v = cola.front();
        cola.pop();
        for (int w: g.ady(v))
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                cola.push(w);
            }
    }
    return dist;
}

bool resuelveCaso() {
    int N, C, alex, lucas, trabajo;
    if (!(cin >> N >> C >> alex >> lucas >> trabajo)) return false; // fin de la entrada

    Grafo g(N);
    for (int i = 0; i < C; ++i) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a - 1, b - 1); // intersecciones numeradas 1..N
    }

    vector<int> dA = bfs(g, alex - 1);
    vector<int> dL = bfs(g, lucas - 1);
    vector<int> dT = bfs(g, trabajo - 1);

    int mejor = INT_MAX;
    for (int m = 0; m < N; ++m)
        mejor = min(mejor, dA[m] + dL[m] + dT[m]);

    cout << mejor << "\n";
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
