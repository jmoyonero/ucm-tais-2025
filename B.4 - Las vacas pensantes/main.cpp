/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "Matriz.h"


/*@ <answer>
 Las Vacas Pensantes (DP sobre Intervalos / Teoría de Juegos)

 Enfoque Iterativo (Bottom-Up):
 Llenamos la tabla dp[i][j] ordenados por la longitud del intervalo (d = j - i).

 dp[i][j] = Máxima comida obtenible en el rango [i, j].

 Transición:
 dp[i][j] = max(
    cubos[i] + respuesta_rival(i+1, j),  // Si como el izquierdo
    cubos[j] + respuesta_rival(i, j-1)   // Si como el derecho
 )

 Donde 'respuesta_rival' simula el movimiento voraz de Devoradora.

 Complejidad:
    O(N^2) tiempo, O(N^2) espacio.
 Complejidad:
 - Coste Temporal: O(N^2), donde N es el número de cubos.
 - Coste Espacial: O(N^2). Se utiliza una matriz.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (N == 0) return false; // fin de la entrada

    vector<int> cubos(N);

    for (int i = 0; i < N; ++i) {
        cin >> cubos[i];
    }

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    Matriz<int> dp(N, N, 0);

    for (int d = 0; d < N; ++d) {
        for (int i = 0; i < N - d; ++i) {
            int j = i + d;

            // Elijo la izquierda
            int elijoIzq = cubos[i];

            if (i + 1 <= j) {
                if (cubos[i + 1] > cubos[j]) {
                    // Devoradora elige la izquierda con lo cual lo quito ese cubo.
                    elijoIzq += dp[i + 2][j];
                } else {
                    // Devoradora elige la derecha con lo cual lo quito ese cubo.
                    elijoIzq += dp[i + 1][j - 1];
                }
            }

            // Elijo la derecha
            int elijoDer = cubos[j];

            if (i <= j - 1) {
                if (cubos[i] > cubos[j - 1]) {
                    // Devoradora elige la izquierda con lo cual lo quito ese cubo.
                    elijoDer += dp[i + 1][j - 1];
                } else {
                    // Devoradora elige la derecha con lo cual lo quito ese cubo.
                    elijoDer += dp[i][j - 2];
                }
            }

            dp[i][j] = max(elijoIzq, elijoDer);
        }
    }

    cout << dp[0][N - 1] << "\n";

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
