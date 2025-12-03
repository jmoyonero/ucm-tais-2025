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


/*@ <answer>

 Problema: El Restaurador de Mosaicos (Distancia de Edición con Costes Variables)

 Recurrencia:
    Caso base:
       dp[i][0] = i * Cdel; (Borrar todo el prefijo de X)
       dp[0][j] = j * Cins; (Insertar todo el prefijo de Y)

    Transición:
       Si X[i-1] == Y[j-1]: dp[i][j] = dp[i-1][j-1]; (Coste 0)
       Si no:
       dp[i][j] = min({
           dp[i-1][j] + Cdel,    // Borrado
           dp[i][j-1] + Cins,    // Inserción
           dp[i-1][j-1] + Csub   // Sustitución
       });

 Complejidad:
 - Coste Temporal: O(N * M), donde N y M son las longitudes de las cadenas.
 - Coste Espacial: O(N * M). Matriz completa.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    int Cins, Cdel, Csub;
    string X, Y;

    cin >> Cins >> Cdel >> Csub >> X >> Y;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    int N = X.size();
    int M = Y.size();

    vector<vector<int> > dp(N + 1, vector<int>(M + 1));

    for (int i = 0; i <= N; ++i) dp[i][0] = i * Cdel;
    for (int j = 0; j <= M; ++j) dp[0][j] = j * Cins;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({
                    dp[i - 1][j] + Cdel,
                    dp[i][j - 1] + Cins,
                    dp[i - 1][j - 1] + Csub
                });
            }
        }
    }

    cout << dp[N][M] << "\n";

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
