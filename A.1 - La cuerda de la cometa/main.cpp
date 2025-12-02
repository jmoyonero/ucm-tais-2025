/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F26)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

Mochila 0/1 (Knapsack Problem) (Optimizado)

Matemático
dp[j] = 0;
dp[0] = 1;
dp[j] = dp[j] + dp[j-l] ; si l <= j (iterando j de mayor a menor)

Ingeniero
dp[j] = Infinito;
dp[0] = 0;
dp[j] = min( dp[j], 1 + dp[j-l] ) ; si l <= j (iterando j de mayor a menor)

Economista
dp[j] = Infinito;
dp[0] = 0;
dp[j] = min( dp[j], coste + dp[j-l] ) ; si l <= j (iterando j de mayor a menor)

Complejidad:
 - Coste Temporal: O(N * L).
 - Coste Espacial: O(L). Se almacena únicamente un vector de tamaño L+1 para cada cálculo, reutilizando el espacio.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Cometa {
    long long formas;
    EntInf minCoste;
    EntInf minCuerdas;
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, L;
    cin >> N >> L;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<Cometa> dp(L + 1, {0, Infinito, Infinito});

    dp[0] = {1, 0, 0};

    for (int i = 1; i <= N; ++i) {
        long long longitud, coste;
        cin >> longitud >> coste;

        for (int j = L; j >= longitud; --j) {
            if (dp[j - longitud].formas > 0)
                dp[j].formas += dp[j - longitud].formas;

            if (dp[j - longitud].minCoste != Infinito)
                dp[j].minCoste = min(dp[j].minCoste, dp[j - longitud].minCoste + coste);

            if (dp[j - longitud].minCuerdas != Infinito)
                dp[j].minCuerdas = min(dp[j].minCuerdas, dp[j - longitud].minCuerdas + 1);
        }
    }

    // escribir la solución

    if (dp[L].formas > 0) {
        cout << "SI " << dp[L].formas << " " << dp[L].minCoste << " " << dp[L].minCuerdas << "\n";
    } else {
        cout << "NO\n";
    }

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
