/*@ <authors>
*
 * F28 Jonathan Paul Moyonero Espinoza
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

/*@ <answer>
Subsecuencia Común Más Larga (LCS)
dp[i][j] = 0; si i=0 || j=0
dp[i][j] = dp[i-1][j-1] + 1; si X[i-1] = Y[j-1]
dp[i][j] = 1 + max(dp[i-1][j], dp[i][j-1]); si X[i-1] != Y[j-1]


Distancia de Edición (Levenshtein),
dp[i][j] = i; si j=0
dp[i][j] = j; si i=0
dp[i][j] = dp[i-1][j-1]; si X[i-1] = Y[j-1]
dp[i][j] = 1 + min(ddp[i−1][j], dp[i][j−1], dp[i−1][j−1]); si X[i-1] != Y[j-1]

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

bool resuelveCaso() {
    string X, Y;
    cin >> X >> Y;

    if (!cin) return false;

    int N = X.size();
    int M = Y.size();

    vector<vector<int> > dp(N + 1, vector<int>(M + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << dp[N][M] << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("1.in");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
