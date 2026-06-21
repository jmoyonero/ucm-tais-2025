/*@ <authors>
*
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer>

Caminos en una cuadricula optimizado a UN solo vector dp de tamano C.

Procesamos la rejilla fila por fila, y dentro de cada fila las columnas de IZQUIERDA a DERECHA.
Reutilizamos el mismo dp[j]: en el momento de actualizarlo,
    - dp[j]   todavia contiene el valor de la fila anterior -> "vengo de arriba"
    - dp[j-1] ya esta actualizado en esta fila              -> "vengo de la izquierda"
Por eso aqui el recorrido es ascendente (al reves que la mochila 0/1).

Caso base:
    - dp[0] = 1 (la casilla de salida); el resto del vector a 0.

Recurrencia en cada casilla (i, j):
    - Si es muro:      dp[j] = 0                  (corta el paso)
    - Si es libre y j>0: dp[j] = dp[j] + dp[j-1]  (arriba ya en dp[j], izquierda en dp[j-1])
    - Si es libre y j==0: dp[0] no se toca        (no hay vecino izquierdo; ya trae el de arriba)

Nota: el número de caminos puede ser muy grande, por eso se usa long long (cabe en 64 bits).

Complejidad:
 - Coste Temporal: O(F * C)
 - Coste Espacial: O(C). Un unico vector reutilizado fila a fila.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int F, C;
    cin >> F >> C;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<long long> dp(C, 0);

    dp[0] = 1;

    for (int i = 0; i < F; ++i) {
        string fila;
        cin >> fila;
        for (int j = 0; j < C; ++j) {
            if (fila[j] == '#') dp[j] = 0; // muro: corta el paso
            else if (j > 0) dp[j] = dp[j] + dp[j - 1]; // libre: arriba (ya en dp[j]) + izquierda
        }
    }

    // escribir la solución

    cout << dp[C - 1] << "\n";

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
