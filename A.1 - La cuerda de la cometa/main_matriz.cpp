/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

// ============================================================================
//  VERSION DIDACTICA con matriz 2D completa (N+1 x L+1).
//  NO es la que se envia al juez: el coste espacial O(N*L) (~18 MB con N=L=1000)
//  supera el limite de memoria del juez -> Run Error. Sirve para entender y
//  depurar viendo toda la tabla. La version que se envia (2 filas) esta en main.cpp.
//
//  Complejidad:
//   - Temporal: O(N * L). Se rellena una matriz de (N+1) x (L+1) en tiempo constante por celda.
//   - Espacial: O(N * L). Se guarda la matriz completa.
// ============================================================================

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"

/*@ <answer>

Mochila 0/1 (Knapsack Problem) con tabla 2D (no optimizado en espacio).

dp[i][j] = respuesta usando los primeros i cordeles para sumar exactamente la longitud j.
Cada celda combina dos casos disjuntos: NO usar el cordel i (dp[i-1][j]) o SÍ usarlo, en cuyo
caso lo que falta lo cubren los cordeles anteriores (dp[i-1][j-l]). Ambos miran la fila i-1, así
que el orden de j es indiferente (no se sobreescribe nada).

Caso base (igual para las tres magnitudes): dp[0][0] = {formas:1, minCuerdas:0, minCoste:0};
el resto de la fila 0 = {0, Infinito, Infinito}.

Recurrencia (si l <= j; si no, dp[i][j] = dp[i-1][j]):
  Matemático: dp[i][j].formas     = dp[i-1][j].formas + dp[i-1][j-l].formas
  Ingeniero:  dp[i][j].minCuerdas = min(dp[i-1][j].minCuerdas, dp[i-1][j-l].minCuerdas + 1)
  Economista: dp[i][j].minCoste   = min(dp[i-1][j].minCoste,   dp[i-1][j-l].minCoste + coste)

La respuesta está en dp[N][L]: si formas > 0 escribimos SI con las tres magnitudes, si no, NO.

Complejidad:
 - Coste Temporal: O(N * L).
 - Coste Espacial: O(N * L). Por la matriz.

 @ </answer> */


struct Cometa {
    long long formas;
    EntInf minCoste;
    EntInf minCuerdas;
};

bool resuelveCaso() {
    int N, L;
    cin >> N >> L;

    if (!std::cin) return false; // fin de la entrada

    // dp[i][j] = respuesta usando los primeros i cordeles para sumar exactamente j
    vector<vector<Cometa> > dp(N + 1, vector<Cometa>(L + 1, {0, Infinito, Infinito}));

    dp[0][0] = {1, 0, 0};

    for (int i = 1; i <= N; i++) {
        int longitud, coste;
        cin >> longitud >> coste;

        for (int j = 0; j <= L; j++) {
            dp[i][j] = dp[i - 1][j]; // caso: NO uso el cordel i
            if (j >= longitud) {
                // caso: SÍ lo uso (si cabe)
                const Cometa &prev = dp[i - 1][j - longitud];
                dp[i][j].formas += prev.formas;
                dp[i][j].minCuerdas = min(dp[i][j].minCuerdas, prev.minCuerdas + 1);
                dp[i][j].minCoste = min(dp[i][j].minCoste, prev.minCoste + coste);
            }
        }
    }

    if (dp[N][L].formas > 0) {
        cout << "SI " << dp[N][L].formas << " " << dp[N][L].minCuerdas << " " << dp[N][L].minCoste << "\n";
    } else {
        cout << "NO\n";
    }

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("1.in");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
