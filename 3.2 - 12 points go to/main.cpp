/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "IndexPQ.h"

using namespace std;

/*@ <answer>

Solución: Mantener el ranking de países y responder al líder en cada consulta.

Cada país acumula puntos (que pueden ser negativos). El líder es el de mayor puntuación y a igualdad,
el de nombre lexicográficamente menor.

Usamos una IndexPQ que permite modificar la prioridad de un elemento ya insertado, justo lo que hace falta
al subir/bajar puntos. Como sus elementos son enteros 0..N-1, asignamos a cada país un id entero (map nombre->id).

Por cada evento:
 - "nombre delta": actualizamos su puntuación y llamamos a update(id, {puntos, nombre}).
 - "?": leemos top(), que es el líder vigente (sin borrados perezosos).

Complejidad (N = eventos, K = países distintos):
 - Temporal: O(N log K).
 - Espacial: O(N) (la IndexPQ se dimensiona por el número de eventos).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Prioridad {
    int puntos;
    string nombre;

    bool operator<(const Prioridad &otra) const {
        if (puntos != otra.puntos) return puntos > otra.puntos;
        return nombre < otra.nombre;
    }
};

bool resuelveCaso() {
    int n;
    if (!(cin >> n)) return false;

    IndexPQ<Prioridad> cola(n); // elementos 0..n-1: el id de cada país
    map<string, int> indice; // nombre -> id
    vector<int> puntos(n, 0); // puntuación actual por id

    for (int i = 0; i < n; ++i) {
        string ev;
        cin >> ev;
        if (ev == "?") {
            const auto &lider = cola.top();
            cout << lider.prioridad.nombre << " " << lider.prioridad.puntos << "\n";
        } else {
            int delta;
            cin >> delta;
            auto it = indice.find(ev);
            int e;
            if (it != indice.end()) e = it->second;
            else {
                e = int(indice.size());
                indice[ev] = e;
            } // país nuevo: id siguiente
            puntos[e] += delta;
            cola.update(e, {puntos[e], ev});
        }
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
