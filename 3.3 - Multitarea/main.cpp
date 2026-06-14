/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

/*@ <answer>

Solución: Detectar si hay solapamiento entre tareas en el periodo [0, T).

Cada tarea genera una secuencia de ocurrencias [c, f) ordenadas por inicio: las únicas (una sola), las
periódicas ([c+kp, f+kp) mientras c+kp < T). Solo importan las que empiezan antes de T: si dos
ocurrencias con inicio < T se solapan, el solape ocurre en max(inicio) < T, es decir dentro de [0,T);
por eso no hace falta recortar los intervalos.

Fusionamos todas las secuencias por orden de inicio con una priority_queue de mínimos (merge de k
secuencias ordenadas). Extraemos la ocurrencia que empieza antes, si su inicio es menor que el mayor fin
visto hasta ahora (hay solape -> SI). Si no, actualizamos el fin y si la tarea es periódica encolamos su
siguiente repetición (si aún entra en [0,T)). Si se agota la cola sin solapes -> NO.

Complejidad (K = nº de ocurrencias con inicio < T):
 - Temporal: O(K log(N+M)).
 - Espacial: O(N+M) (a lo sumo una ocurrencia pendiente por tarea).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Ocurrencia {
    long long inicio, fin;
    long long periodo; // 0 si es una tarea única (no se repite)

    // Más prioritaria = la que empieza antes (PriorityQueue es de mínimos).
    bool operator<(const Ocurrencia &otra) const {
        return inicio < otra.inicio;
    }
};

bool resuelveCaso() {
    long long N, M, T;
    if (!(cin >> N >> M >> T)) return false;

    PriorityQueue<Ocurrencia> cola;

    for (long long i = 0; i < N; ++i) {
        long long c, f;
        cin >> c >> f;
        if (c < T) cola.push({c, f, 0}); // tarea única
    }

    for (long long i = 0; i < M; ++i) {
        long long c, f, p;
        cin >> c >> f >> p;
        if (c < T) cola.push({c, f, p}); // primera aparición de la periódica
    }

    bool conflicto = false;
    long long maxFin = -1;
    while (!cola.empty() && !conflicto) {
        Ocurrencia o = cola.top();
        cola.pop();

        if (o.inicio < maxFin) {
            // se solapa con una tarea ya empezada
            conflicto = true;
        } else {
            maxFin = o.fin;
            if (o.periodo > 0) {
                // encola la siguiente repetición si entra en [0,T)
                long long sigInicio = o.inicio + o.periodo;
                if (sigInicio < T)
                    cola.push({sigInicio, o.fin + o.periodo, o.periodo});
            }
        }
    }

    cout << (conflicto ? "SI" : "NO") << "\n";
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
