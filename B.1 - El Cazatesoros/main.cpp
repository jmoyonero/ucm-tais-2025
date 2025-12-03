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

Mochila 0/1 (Knapsack Problem)
dp[i][w] = 0; si w=0
dp[i][w] = 0; si i=0
dp[i][w] = dp[i-1][w]; si p > w
dp[i][w] = max( dp[i-1][w], v + dp[i-1][w-p] ) ; si p <= w

Inicio:
 dp[0] = 0;

 Complejidad:
 - Coste Temporal: O(N * T), donde N es el número de cofres y T el tiempo máximo que puedo permanecer bajo el agua.
 - Coste Espacial: O(N * T). Se utiliza una matriz para reconstruir el camino.

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


struct Cofre {
    int oro;
    int profundidad;
    int peso;
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int T, N;
    cin >> T >> N;

    if (!std::cin) return false; // fin de la entrada

    vector<Cofre> cofres(N);

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    for (int i = 0; i < N; ++i) {
        cin >> cofres[i].profundidad >> cofres[i].oro;
        cofres[i].peso = 3 * cofres[i].profundidad;
    }

    Matriz<int> dp(N + 1, T + 1);

    for (int i = 1; i <= N; ++i) {
        const int peso = cofres[i - 1].peso;
        const int oro = cofres[i - 1].oro;

        for (int j = 1; j <= T; ++j) {
            if (peso > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], oro + dp[i - 1][j - peso]);
            }
        }
    }

    cout << dp[N][T] << "\n";

    // Reconstrucción para obtener los cofres
    vector<Cofre> cofresElegidos;
    int tiempo = T;

    for (int i = N; i > 0; --i) {
        if (dp[i][tiempo] != dp[i - 1][tiempo]) {
            cofresElegidos.push_back(cofres[i - 1]);
            tiempo -= cofres[i - 1].peso;
        }
    }

    cout << cofresElegidos.size() << "\n";

    for (int i = cofresElegidos.size() - 1; i >= 0; --i) {
        cout << cofresElegidos[i].profundidad << " " << cofresElegidos[i].oro << "\n";
    }

    cout << "---\n";

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
