/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

/*@ <answer>

Solución: Hallar en qué turno de la cola se compra el mejor ejemplar de la tienda
(el de menor identificador global).

Cada cliente compra el mejor ejemplar disponible entre las cimas de las pilas. Simulamos esos turnos
con una priority_queue de mínimos que contiene, en todo momento, la cima de cada pila no vacía. En
cada turno sacamos la cima de menor identificador (ese cliente la compra) y si su pila aún tiene
ejemplares, metemos la nueva cima de esa pila. Contamos turnos hasta comprar el ejemplar de
identificador mínimo global: ese contador es la posición buscada.

Complejidad (C = total de ejemplares, N = nº de pilas, T = ejemplares comprados hasta el mejor):
 - Temporal: O(C + T log N) por la lectura y la simulación.
 - Espacial: O(C) por los ejemplares almacenados.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Comic {
    int idPila;
    int ejemplar;   // identificador único del ejemplar (menor = más codiciado)

    // Invertimos el orden para que la priority_queue (max-heap) deje en la
    // cima el ejemplar de MENOR identificador.
    bool operator<(const Comic &otro) const {
        return ejemplar > otro.ejemplar;
    }
};

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;

    vector<vector<Comic> > pilas(N);
    int mejorEjemplar = INT_MAX;

    for (int i = 0; i < N; ++i) {
        int K;
        cin >> K;
        pilas[i].reserve(K);
        for (int j = 0; j < K; ++j) {
            int x;
            cin >> x;
            mejorEjemplar = min(mejorEjemplar, x);
            pilas[i].push_back({i, x});
        }
    }

    // La cola contiene en cada momento la cima de cada pila no vacía.
    priority_queue<Comic> aux;
    for (int i = 0; i < N; ++i) {
        aux.push(pilas[i].back());
        pilas[i].pop_back();
    }

    int posicion = 0;
    while (true) {
        Comic cima = aux.top();
        aux.pop();
        ++posicion;
        if (cima.ejemplar == mejorEjemplar) break;   // comprado el mejor de la tienda

        int p = cima.idPila;
        if (!pilas[p].empty()) {                      // sale a la cima el siguiente de esa pila
            aux.push(pilas[p].back());
            pilas[p].pop_back();
        }
    }

    cout << posicion << "\n";

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
