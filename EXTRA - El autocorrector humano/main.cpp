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

Distancia de Edición (Levenshtein),
dp[i][j] = i; si j=0
dp[i][j] = j; si i=0
dp[i][j] = dp[i-1][j-1]; si X[i-1] = Y[j-1]
dp[i][j] = 1 + min(ddp[i−1][j], dp[i][j−1], dp[i−1][j−1]); si X[i-1] != Y[j-1]

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    string X, Y;
    cin >> X >> Y;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    int N = X.size();
    int M = Y.size();

    vector<vector<int> > dp(N + 1, vector<int>(M + 1, 0));

    for (int i = 0; i <= N; i++) dp[i][0] = i;
    for (int j = 0; j <= M; j++) dp[0][j] = j;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({
                               dp[i - 1][j],
                               dp[i][j - 1],
                               dp[i - 1][j - 1]
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
