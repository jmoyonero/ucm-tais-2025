/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

// propios o los de las estructuras de datos de clase


/*@ <answer>

Mochila 0/1 (Knapsack Problem) Optimizada (2 restricciones)
dp[j][w] = 0;
dp[j][w] = max( dp[j][w], vi + dp[j-o][w-p] ) ; si p <= w && o <=j (iterando j y w de mayor a menor)

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

    cout << dp[PRESUPUESTO][PLATOSmax] << "\n";

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
