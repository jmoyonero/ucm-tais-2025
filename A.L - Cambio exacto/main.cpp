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
#include "EnterosInf.h"


/*@ <answer>

 Problema del Cambio Exacto (Variante de Mochila 0/1)

 Recurrencia:
 dp[j] = Infinito; // Inicialización
 dp[j] = min(dp[j], 1 + dp[j - m]); // Si usamos la moneda 'm', sumamos 1 al conteo

 Inicio:
 dp[0] = 0;

 Complejidad:
 - Coste Temporal: O(N * S), donde N es el número de monedas y S es la suma total del dinero.
 - Coste Espacial: O(S). Se utiliza un vector de tamaño S+1.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int Precio, N;
    cin >> Precio >> N;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<int> monedas(N);
    int totalDinero = 0;

    for (int i = 0; i < N; ++i) {
        cin >> monedas[i];
        totalDinero += monedas[i];
    }

    vector<EntInf> dp(totalDinero + 1, Infinito);
    dp[0] = 0;

    for (int i = 0; i < N; ++i) {
        int m = monedas[i];
        for (int j = totalDinero; j >= m; --j) {
            dp[j] = min(dp[j], dp[j - m] + 1);
        }
    }

    for (int i = Precio; i <= totalDinero; ++i) {
        if (dp[i] != Infinito) {
            cout << i << " " << dp[i] << "\n";
            break;
        }
    }

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
