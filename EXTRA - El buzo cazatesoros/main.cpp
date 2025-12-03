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

 Problema: El Buzo Cazatesoros (Mochila 0/1 Multidimensional)

 Recurrencia:
    dp[j][k] = max(dp[j][k], v + dp[j - costeO][k - costeP])
    (Iterando j y k hacia atrás para asegurar la propiedad 0/1)

 Complejidad:
 - Coste Temporal: O(N * Omax * Pmax). Tenemos N objetos y para cada uno recorremos la matriz de capacidades.
 - Coste Espacial: O(Omax * Pmax). Usamos una matriz de tamaño (Oxígeno x Peso).

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, Omax, Pmax;
    cin >> N >> Omax >> Pmax;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<vector<int> > dp(Omax + 1, vector<int>(Pmax + 1, 0));

    for (int i = 0; i < N; ++i) {
        int costeOxigeno, peso, valor;
        cin >> costeOxigeno >> peso >> valor;

        for (int j = Omax; j >= costeOxigeno; --j) {
            for (int k = Pmax; k >= peso; --k) {
                dp[j][k] = max(dp[j][k], valor + dp[j - costeOxigeno][k - peso]);
            }
        }
    }

    cout << dp[Omax][Pmax] << "\n";

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
