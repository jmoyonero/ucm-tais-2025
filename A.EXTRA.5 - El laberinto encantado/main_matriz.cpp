/*@ <authors>
*
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer>

Caminos en una cuadricula (DP 2D). dp[i][j] = numero de caminos para llegar a la casilla (i,j)
moviendose solo a la derecha o hacia abajo, sin pisar muros.

Caso base:
    - dp[0][0] = 1 (la casilla de salida)

Recurrencia (si (i,j) no es muro):
    - dp[i][j] += dp[i-1][j]    -> vengo de arriba    (si i > 0)
    - dp[i][j] += dp[i][j-1]    -> vengo de la izquierda (si j > 0)
    Si (i,j) es muro, dp[i][j] = 0.

Nota: el numero de caminos puede ser muy grande, por eso se usa long long (cabe en 64 bits).

Complejidad:
 - Coste Temporal: O(F * C)
 - Coste Espacial: O(F * C) por la matriz

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int F, C;
    cin >> F >> C;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<vector<long long> > dp(F, vector<long long>(C, 0));

    dp[0][0] = 1;

    for (int i = 0; i < F; ++i) {
        string fila;
        cin >> fila;
        for (int j = 0; j < C; ++j) {
            if (fila[j] == '#') continue;
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }

    // escribir la solución

    cout << dp[F - 1][C - 1] << "\n";

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
