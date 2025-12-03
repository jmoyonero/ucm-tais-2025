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
#include "EnterosInf.h"

/*@ <answer>

Cambio de Monedas (Change Making Problem)

dp[j] = Infinito; si j > 0;
dp[0] = 0;
dp[j] = min( dp[j], 1 + dp[j-p] ) ; si p <= j && dp[j - p] sea alcanzable

Complejidad:
 - Coste Temporal: O(V * S).
 - Coste Espacial: O(V). Se almacena únicamente un vector de tamaño V+1 para cada cálculo, reutilizando el espacio.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int V, S;
    cin >> V >> S;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<int> puntuaciones(S);

    for (int i = 0; i < S; ++i) {
        cin >> puntuaciones[i];
    }

    vector<EntInf> dp(V + 1, Infinito);
    dp[0] = 0;

    for (int i = 1; i <= V; ++i) {
        for (int j = 0; j < S; ++j) {
            int puntuacion = puntuaciones[j];
            if (i >= puntuacion && dp[i - puntuacion] != Infinito) {
                dp[i] = min(dp[i], dp[i - puntuacion] + 1);
            }
        }
    }

    // escribir la solución

    if (dp[V] == Infinito) {
        cout << "Imposible\n";
        return true;
    }

    cout << dp[V] << ":";

    int actual = V;

    while (actual > 0) {
        for (int j = S - 1; j >= 0; --j) {
            int p = puntuaciones[j];
            if (actual >= p && dp[actual] == dp[actual - p] + 1) {
                cout << " " << p;
                actual -= p;
                break;
            }
        }
    }

    cout << "\n";

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
