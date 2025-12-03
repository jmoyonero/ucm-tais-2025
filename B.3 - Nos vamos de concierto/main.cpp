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


/*@ <answer>

Mochila 0/1 (Knapsack Problem)
dp[i][w] = 0; si w=0
dp[i][w] = 0; si i=0
dp[i][w] = dp[i-1][w]; si p > w
dp[i][w] = max( dp[i-1][w], v + dp[i-1][w-p] ) ; si p <= w

Inicio:
 dp[0] = 0;

 Complejidad:
 - Coste Temporal: O(N * P), donde N es el número de conciertos y P el presupuesto que tengo para gastar.
 - Coste Espacial: O(P). Se utiliza un vector porque no necesitamos reconstruir el camino.

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Festival {
    int grupos;
    int precio;
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int P, N;
    cin >> P >> N;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<int> dp(P + 1, 0);

    for (int i = 1; i <= N; ++i) {
        int precio, grupos;
        cin >> grupos >> precio;

        for (int j = P; j >= precio; --j) {
            dp[j] = max(dp[j], grupos + dp[j - precio]);
        }
    }

    cout << dp[P] << "\n";

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
