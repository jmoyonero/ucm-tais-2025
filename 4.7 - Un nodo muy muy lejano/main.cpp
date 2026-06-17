/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"

using namespace std;

/*@ <answer>

El mensaje parte del nodo origen y se reenvía a los adyacentes mientras le quede TTL. Cada reenvío
gasta una unidad de TTL, así que un nodo a distancia d (mínimo nº de saltos desde el origen) recibe el
mensaje exactamente si d <= TTL (el origen, d = 0, siempre lo conoce). Por tanto los nodos accesibles
son los que están a distancia BFS menor o igual que TTL, y la respuesta es N menos esa cantidad.

Como las aristas no tienen peso, la distancia mínima a cada nodo se obtiene con un recorrido en
ANCHURA (BFS) desde el origen. Lanzamos un BFS por consulta (hay como mucho 10) contando cuántos nodos
quedan dentro del radio TTL.

Complejidad por consulta (N nodos, C conexiones):
 - Temporal: O(N + C), un BFS recorre cada nodo y arista una vez.
 - Espacial: O(N) por el vector de distancias y la cola.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// Devuelve cuántos nodos están a distancia BFS <= ttl del origen (incluido el origen).
int alcanzables(Grafo const &g, int origen, int ttl) {
    vector<int> dist(g.V(), -1);
    queue<int> cola;
    dist[origen] = 0;
    cola.push(origen);
    int cuenta = 1; // el propio origen
    while (!cola.empty()) {
        int v = cola.front();
        cola.pop();
        if (dist[v] == ttl) continue; // desde aquí ya no se reenvía más
        for (int w: g.ady(v))
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                ++cuenta;
                cola.push(w);
            }
    }
    return cuenta;
}

bool resuelveCaso() {
    int N, C;
    if (!(cin >> N >> C)) return false; // fin de la entrada

    Grafo g(N);
    for (int i = 0; i < C; ++i) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a - 1, b - 1); // nodos numerados 1..N
    }

    int K;
    cin >> K;
    for (int q = 0; q < K; ++q) {
        int origen, ttl;
        cin >> origen >> ttl;
        cout << N - alcanzables(g, origen - 1, ttl) << "\n";
    }
    cout << "---\n";
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
