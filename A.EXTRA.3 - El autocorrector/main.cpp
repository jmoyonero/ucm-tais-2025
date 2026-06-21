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

Distancia de edicion (Levenshtein), DP sobre DOS secuencias con tabla 2D.

Estado:
    dp[i][j] = numero minimo de operaciones (insertar, borrar, sustituir) para transformar los
               i primeros caracteres de A en los j primeros de B. (El caracter i de A es A[i-1].)

Caso base (transformar contra una cadena vacia):
    - dp[i][0] = i  -> borrar las i letras de A.
    - dp[0][j] = j  -> insertar las j letras de B.

Recurrencia (los tres vecinos: arriba=borrar, izquierda=insertar, diagonal=sustituir):
    - Si A[i-1] == B[j-1]:  dp[i][j] = dp[i-1][j-1]            (coinciden, coste 0)
    - Si no:                dp[i][j] = 1 + min(dp[i-1][j],     (borrar A[i-1])
                                               dp[i][j-1],     (insertar B[j-1])
                                               dp[i-1][j-1])   (sustituir)

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
    // leer los datos de la entrada

    string A, B;
    if (!(cin >> A >> B)) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<vector<int> > dp(A.size() + 1, vector<int>(B.size() + 1, 0));

    for (int i = 0; i <= A.size(); i++) dp[i][0] = i;
    for (int j = 0; j <= B.size(); j++) dp[0][j] = j;

    for (int i = 1; i <= A.size(); i++) {
        for (int j = 1; j <= B.size(); j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(
                               min(dp[i - 1][j], dp[i][j - 1]),
                               dp[i - 1][j - 1]);
            }
        }
    }

    // escribir la solución

    cout << dp[A.size()][B.size()] << endl;

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
