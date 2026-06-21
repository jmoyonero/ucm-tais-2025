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

Cambio de moneda con monedas ILIMITADAS (DP 2D). dp[i][j] = minimo numero de monedas para
formar la cantidad j usando los i primeros tipos de moneda.

Caso base:
    - dp[0][0] = 0  -> mínimo de monedas para el monto 0 (ninguna); el resto, Infinito.

Recurrencia:
    - dp[i][j] = dp[i-1][j]                             -> Si m > j  (no cabe, no usamos la moneda)
    - dp[i][j] = min(dp[i-1][j], dp[i][j-m] + 1)        -> Si m <= j (al usar la moneda repetible
                                                          nos quedamos en la MISMA fila i)

Complejidad:
 - Coste Temporal: O(M * Q)
 - Coste Espacial: O(M * Q) por la matriz.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int M, Q;
    cin >> M >> Q;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<vector<EntInf> > dp(M + 1, vector<EntInf>(Q + 1, Infinito));

    dp[0][0] = 0;

    for (int i = 1; i <= M; ++i) {
        int m;
        cin >> m;

        for (int j = 0; j <= Q; ++j) {
            if (m <= j) {
                dp[i][j] = min(dp[i][j - m] + 1, dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }


    // escribir la solución

    if (dp[M][Q] == Infinito) cout << "Imposible\n";
    else cout << dp[M][Q] << "\n";

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
