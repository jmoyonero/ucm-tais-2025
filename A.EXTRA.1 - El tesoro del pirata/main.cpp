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

Mochila 0/1 (Knapsack Problem) optimizado a un vector.

Caso base:
    - dp[0] = 0 -> Si no hay objetos la mochila lleva 0 de beneficio.

Recurrencia:
    - dp[j] = dp[j]                                 -> Si j < peso  (No usamos el objeto)
    - dp[j] = max(dp[j], dp[j-peso] + valor)        -> Si j >= peso (Usamos el objeto)

Complejidad:
 - Coste Temporal: O(N * W).
 - Coste Espacial: O(W). Solo se usa un vector.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N, W;
    cin >> N >> W;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<long long> dp(W + 1, 0);

    dp[0] = 0; // Si no hay objetos la mochila lleva 0 de beneficio.

    for (int i = 1; i <= N; ++i) {
        int peso, valor;
        cin >> peso >> valor;
        for (int j = W; j >= peso; --j) {
            dp[j] = max(dp[j], dp[j - peso] + valor);
        }
    }

    // escribir la solución

    cout << dp[W] << "\n";

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
