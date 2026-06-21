/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*@ <answer>

Subsecuencia Comun mas Larga (LCS), DP sobre DOS secuencias con tabla 2D.

Estado:
    dp[i][j] = longitud de la subsecuencia comun mas larga entre los i primeros caracteres de A
               y los j primeros de B.  (Ojo: el caracter i de A es A[i-1], desfase de 1.)

Caso base:
    - dp[0][j] = 0 y dp[i][0] = 0  -> si una de las cadenas esta vacia, no hay nada en comun.

Recurrencia (los tres vecinos: arriba, izquierda y diagonal):
    - Si A[i-1] == B[j-1] (coinciden):  dp[i][j] = dp[i-1][j-1] + 1
        (empareja ese caracter, consumiendo uno de CADA cadena -> diagonal, y suma 1)
    - Si no coinciden:                  dp[i][j] = max(dp[i-1][j], dp[i][j-1])
        (descarto el ultimo de A -> arriba, o el ultimo de B -> izquierda, y me quedo el mejor)

La respuesta es dp[n][m].

Complejidad (n = |A|, m = |B|):
 - Coste Temporal: O(n * m).
 - Coste Espacial: O(n * m) por la matriz.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada: dos cadenas, una por linea
    string A, B;
    if (!(cin >> A >> B)) return false; // fin de la entrada

    int n = A.size(), m = B.size();

    // dp de tamaño (n+1) x (m+1); la fila/columna 0 representa el prefijo vacío (todo a 0)
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // coinciden: diagonal + 1
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // no coinciden: mejor de arriba/izquierda
            }
        }
    }

    // escribir la solución
    cout << dp[n][m] << "\n";

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
