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

 El problema se resuelve mediante Programación Dinámica con una complejidad lineal. Se define dp[i] como el beneficio
 máximo obtenible considerando los primeros i locales.

 Para cada local i, se decide entre:
    1. No incluirlo: dp[i-1].
    2. Incluirlo: beneficio[i-1] + dp[j], donde j es el índice del último local cuya distancia es p[i-1] - p[j-1] >= S

 Para optimizar la búsqueda de j se utiliza la técnica de "dos punteros" aprovechando que las posiciones de los locales
 están ordenadas de forma creciente.

 Complejidad:

 - Coste Temporal: O(N). Donde N es el número de locales.
 - Coste Espacial: O(N). Necesario para almacenar los vectores de posiciones, beneficios, la tabla DP y el vector de
   reconstrucción.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, S;
    cin >> N >> S;

    if (!cin) return false; // fin de la entrada

    vector<int> locales(N);
    vector<long long> beneficios(N);

    for (int i = 0; i < N; ++i) cin >> locales[i];
    for (int i = 0; i < N; ++i) cin >> beneficios[i];

    vector<long long> dp(N + 1, 0);
    vector<int> ultimoValido(N + 1, 0);
    vector<bool> elegidos(N + 1, false);

    int j = 0;

    for (int i = 1; i <= N; ++i) {
        while (j < i && locales[i - 1] - locales[j] >= S) {
            ++j;
        }

        ultimoValido[i] = j;

        long long sinActual = dp[i - 1];
        long long conActual = beneficios[i - 1] + dp[j];

        if (conActual >= sinActual) {
            dp[i] = conActual;
            elegidos[i] = true;
        } else {
            dp[i] = sinActual;
            elegidos[i] = false;
        }
    }

    // Reconstrucción a partir del vector de elegidos.

    vector<long long> solucion;

    for (int i = N; i > 0;) {
        if (elegidos[i]) {
            solucion.push_back(locales[i - 1]);
            i = ultimoValido[i];
        } else {
            i--;
        }
    }

    // escribir la solución

    cout << dp[N] << ":";

    for (int i = solucion.size() - 1; i >= 0; --i) cout << " " << solucion[i];

    cout << "\n";

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
