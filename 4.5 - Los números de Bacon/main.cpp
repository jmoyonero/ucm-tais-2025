/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "Grafo.h"

using namespace std;

/*@ <answer>

El número de Bacon es la mínima cantidad de "saltos de película" hasta Kevin Bacon, es decir, la
distancia más corta en un grafo no dirigido y sin pesos. La herramienta para distancias mínimas en
ese tipo de grafo es un recorrido en ANCHURA (BFS) desde Kevin Bacon.

Lo natural sería poner una arista entre cada par de actores que comparten película, pero una película
con k actores generaría k*(k-1)/2 aristas y eso se dispara. En su lugar añadimos un VÉRTICE EXTRA por
cada película y la conectamos con cada uno de sus actores (grafo bipartito actores–películas). Así un
camino actor -> película -> actor tiene longitud 2, y en general dos actores que se enlazan con c
conexiones de películas quedan a distancia 2*c. Por tanto el número de Bacon de un actor es su
distancia BFS a Kevin Bacon dividida entre 2; si es inalcanzable (o Kevin Bacon no está en la base de
datos) la respuesta es INF.

Numeramos los actores 0..nAct-1 (asignándoles índice según aparecen) y las P películas
nAct..nAct+P-1, de modo que el grafo tiene nAct+P vértices y una arista por cada aparición de un actor
en una película.

Complejidad por caso (A actores, P películas, E apariciones totales):
 - Temporal: O(A + P + E), construir el grafo y el BFS recorren cada vértice y arista una vez.
 - Espacial: O(A + P + E) por la lista de adyacencia, el mapa de nombres y el vector de distancias.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int P;
    if (!(cin >> P)) return false; // fin de la entrada

    unordered_map<string, int> id; // nombre de actor -> índice de vértice
    vector<vector<int> > actoresPeli(P); // actores (ya numerados) de cada película
    string nombre;
    int k;

    for (int p = 0; p < P; ++p) {
        cin >> nombre >> k;
        actoresPeli[p].reserve(k);
        for (int i = 0; i < k; ++i) {
            cin >> nombre;
            // emplace asigna un índice nuevo solo si el actor no existía aún
            int v = id.emplace(nombre, (int) id.size()).first->second;
            actoresPeli[p].push_back(v);
        }
    }

    int nAct = (int) id.size();
    // vértices: 0..nAct-1 actores, nAct..nAct+P-1 películas
    Grafo g(nAct + P);
    for (int p = 0; p < P; ++p) {
        int peli = nAct + p;
        for (int v: actoresPeli[p])
            g.ponArista(v, peli);
    }

    // BFS desde Kevin Bacon (si aparece en la base de datos)
    vector<int> dist(g.V(), -1);
    auto it = id.find("KevinBacon");
    if (it != id.end()) {
        queue<int> cola;
        dist[it->second] = 0;
        cola.push(it->second);
        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            for (int w: g.ady(v))
                if (dist[w] == -1) {
                    dist[w] = dist[v] + 1;
                    cola.push(w);
                }
        }
    }

    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> nombre;
        int d = dist[id[nombre]];
        if (d == -1) cout << nombre << " INF\n";
        else cout << nombre << " " << d / 2 << "\n";
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
