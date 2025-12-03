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

 Camino de suma máxima en una cuadrícula (Maximum Path Sum in a Grid)

 Recurrencia:
 dp[j] = valor[0][j]; // Caso base (primera fila)
 dp[j] = valor[i][j] + max(prev[j-1], prev[j], prev[j+1]); // Paso recursivo (mirando fila anterior)

 Complejidad:
 - Coste Temporal: O(N^2). Recorremos las N*N casillas una vez.
 - Coste Espacial: O(N^2). Se utiliza una matriz N*N.

 Optimización en espacio:

 Complejidad:
 - Coste Temporal: O(N^2). Recorremos las N*N casillas una vez.
 - Coste Espacial: O(N). Se almacena únicamente un vector (o dos) de tamaño N, reutilizando el espacio fila a fila.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!std::cin) return false; // fin de la entrada

    Matriz<int> tablero(N, N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> tablero[i][j];
        }
    }

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    Matriz<int> dp(N + 1, N + 1, 0);

    for (int j = 1; j <= N; ++j) {
        dp[0][j] = tablero[0][j];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int maxPrevio = -1;

            // Diagonal izquierda
            if (j > 0) maxPrevio = max(maxPrevio, dp[i - 1][j - 1]);

            // Vertical
            maxPrevio = max(maxPrevio, dp[i - 1][j]);

            // Diagonal derecha
            if (j < N - 1) maxPrevio = max(maxPrevio, dp[i - 1][j + 1]);

            dp[i][j] = tablero[i][j] + maxPrevio;
        }
    }

    // Buscamos el máximo valor en la última fila y su posición
    // Inicializamos con -1 para asegurar la actualización
    int maxValor = -1;
    int mejorColumna = -1;

    for (int j = 0; j < N; ++j) {
        // Usamos > estricto para mantener el índice más a la izquierda en caso de empate ("En caso de que haya varias preferimos la que esté más a la izquierda")
        if (dp[N - 1][j] > maxValor) {
            maxValor = dp[N - 1][j];
            mejorColumna = j + 1;
        }
    }

    cout << maxValor << " " << mejorColumna << " \n";

    return true;
}

bool resuelveCasoOptimizacion() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<int> dp(N);

    for (int j = 0; j < N; ++j) {
        cin >> dp[j];
    }

    for (int i = 1; i < N; ++i) {
        vector<int> filaActual(N);
        vector<int> nuevaDp(N);

        for (int j = 0; j < N; ++j) {
            cin >> filaActual[j];
        }

        for (int j = 0; j < N; ++j) {
            int maxPrevio = dp[j];

            // Diagonal izquierda
            if (j > 0) maxPrevio = max(maxPrevio, dp[j - 1]);

            // Diagonal derecha
            if (j < N - 1) maxPrevio = max(maxPrevio, dp[j + 1]);

            // Sumamos el valor de la casilla actual al mejor camino previo
            nuevaDp[j] = filaActual[j] + maxPrevio;
        }
        dp = nuevaDp;
    }

    // Buscamos el máximo valor en la última fila y su posición
    // Inicializamos con -1 para asegurar la actualización
    int maxValor = -1;
    int mejorColumna = -1;

    for (int j = 0; j < N; ++j) {
        // Usamos > estricto para mantener el índice más a la izquierda en caso de empate ("En caso de que haya varias preferimos la que esté más a la izquierda")
        if (dp[j] > maxValor) {
            maxValor = dp[j];
            mejorColumna = j;
        }
    }

    cout << maxValor << " " << mejorColumna + 1 << " \n";

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

    while (resuelveCasoOptimizacion());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
