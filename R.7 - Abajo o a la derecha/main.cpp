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


/*@ <answer>

 El problema se resuelve mediante programación dinámica.
 Dado que desde cada celda solo se puede saltar hacia abajo o hacia la derecha, podemos calcular el número de formas de
 llegar a (n, m) acumulando los caminos de forma progresiva.

 Estrategia:
    1.  Usamos una matriz dp inicializada a cero, donde dp[0][0] = 1.
    2.  Recorremos la matriz original donde para cada celda sumamos sus caminos actuales a las celdas destino de sus
        saltos permitidos (derecha y abajo).
    3.  Controlamos que los saltos no excedan los límites de la matriz (n, m).

 Complejidad:

 - Coste Temporal: O(n * m). Se realiza un recorrido simple por todas las celdas de la matriz de tamaño n x m.
 - Coste Espacial: O(n * m). Se requiere una matriz adicional de las mismas dimensiones para almacenar los caminos acumulados.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N, M;
    cin >> N >> M;

    if (!cin) return false; // fin de la entrada

    Matriz<int> tablero(N, M, 0);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> tablero[i][j];


    Matriz<long long> dp(N, M, 0);
    dp[0][0] = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // Si ya llegamos al destino o no hay caminos aquí, saltamos
            if ((i == N - 1 && j == M - 1) || dp[i][j] == 0) continue;

            int salto = tablero[i][j];

            // Salto hacia abajo (i + salto)
            if (i + salto < N) {
                dp[i + salto][j] += dp[i][j];
            }

            // Salto a la derecha (j + salto)
            if (j + salto < M) {
                dp[i][j + salto] += dp[i][j];
            }
        }
    }


    // escribir la solución

    cout << dp[N - 1][M - 1] << "\n";

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
