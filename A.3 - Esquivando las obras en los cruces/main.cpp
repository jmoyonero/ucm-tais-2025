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
#include "Matriz.h"

/*@ <answer>

Cambio de Monedas (Change Making Problem)

dp[0][0] = 1;
dp[i][j] = 0; si (i, j) = X;
dp[i][j] = dp[i-1][j] + dp[i][j-1]; si (i, j) != X;

Complejidad:
 - Coste Temporal: O(V * S).
 - Coste Espacial: O(N * M). Se almacena únicamente un vector de tamaño V+1 para cada cálculo, reutilizando el espacio.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N, M;
    cin >> N >> M;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<string> mapa(N);

    for (int i = 0; i < N; ++i) {
        cin >> mapa[i];
    }

    Matriz<int> dp(N, M, 0);
    dp[0][0] = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (mapa[i][j] == 'X') {
                dp[i][j] = 0;
            } else if (i > 0 || j > 0) {
                if (i > 0)
                    dp[i][j] = dp[i - 1][j];

                if (j > 0)
                    dp[i][j] += dp[i][j - 1];
            }
        }
    }

    cout << dp[N - 1][M - 1] << " \n";

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
