/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "Matriz.h"
#include "EnterosInf.h"

/*@ <answer>

 El problema se resuelve mediante programación dinámica sobre un grafo acíclico (DAG).
 El estado dp[i][j] representa el tiempo mínimo para llegar a la ciudad 'i' habiendo gastado 'j' de presupuesto.

 Estrategia:
    1. Para cada ciudad i, consideramos el tiempo de estancia predicho por el oráculo.
    2. Transicionamos a la ciudad i+1 (gasto 0) o mediante atajos (gasto c).
    3. El resultado es el mínimo tiempo en la ciudad N+1 para cualquier gasto <= P.

 Complejidad:
 - Coste Temporal: O(P * (N + A)), donde N es el número de ciudades, P el presupuesto y A el número de atajos.
 - Coste Espacial: O(N * P) para almacenar la tabla de estados.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Atajo {
    int destino;
    int coste;
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, P, A;
    cin >> N >> P >> A;

    if (!cin) return false; // fin de la entrada

    vector<int> tiempos(N + 1);
    for (int i = 1; i <= N; ++i) cin >> tiempos[i];

    vector<vector<Atajo> > adyacentes(N + 1);
    for (int i = 0; i < A; ++i) {
        int origen, destino, coste;
        cin >> origen >> destino >> coste;
        if (origen < N)
            adyacentes[origen].push_back({destino, coste});
    }

    // resolver el caso posiblemente llamando a otras funciones
    // Programación dinámica: dp

    Matriz<EntInf> dp(N + 2, P + 1, Infinito);
    dp[1][0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= P; ++j) {
            if (dp[i][j] == Infinito) continue;

            EntInf tiempoTotal = dp[i][j] + tiempos[i];

            if (dp[i + 1][j] > tiempoTotal) {
                dp[i + 1][j] = tiempoTotal;
            }

            for (auto &ady: adyacentes[i]) {
                if (j + ady.coste <= P) {
                    if (dp[ady.destino][j + ady.coste] > tiempoTotal)
                        dp[ady.destino][j + ady.coste] = tiempoTotal;
                }
            }
        }
    }

    EntInf tiempoMinimo = Infinito;
    for (int j = 0; j <= P; ++j)
        tiempoMinimo = min(tiempoMinimo, dp[N + 1][j]);

    // escribir la solución

    cout << tiempoMinimo << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("1.in");
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
