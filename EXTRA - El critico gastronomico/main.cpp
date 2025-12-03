/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// propios o los de las estructuras de datos de clase


/*@ <answer>

 El Crítico Gastronómico (Mochila 0/1 con restricción de cardinalidad)

 Recurrencia:
    dp[j][k] = max(dp[j][k], satisfaccion + dp[j - precio][k - 1])
    (Iterando j y k hacia atrás)

 Complejidad:
 - Coste Temporal: O(N * D * K), donde N es el número de platos, D el presupuesto y K el límite de platos.
 - Coste Espacial: O(D * K). Usamos una matriz de (Presupuesto x Cantidad).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Plato {
    int precio;
    int satisfaccion;
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, PLATOSmax, PRESUPUESTO;
    cin >> N >> PLATOSmax >> PRESUPUESTO;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<vector<int> > dp(PRESUPUESTO + 1, vector<int>(PLATOSmax + 1));

    for (int i = 0; i < N; ++i) {
        int precio, satisfaccion;
        cin >> precio >> satisfaccion;

        for (int j = PRESUPUESTO; j >= precio; --j) {
            for (int k = PLATOSmax; k >= 1; --k) {
                dp[j][k] = max(dp[j][k], satisfaccion + dp[j - precio][k - 1]);
            }
        }
    }

    int maxSatisfaccion = 0;
    for (int k = 0; k <= PLATOSmax; ++k) {
        maxSatisfaccion = max(maxSatisfaccion, dp[PRESUPUESTO][k]);
    }

    cout << maxSatisfaccion << "\n";

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
