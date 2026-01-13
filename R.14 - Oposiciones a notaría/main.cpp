/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "Matriz.h"
#include "EnterosInf.h"

/*@ <answer>

 El problema se resuelve mediante Programación Dinámica, utilizando una variante del algoritmo de Multiplicación de
 Cadenas de Matrices.

 Se define matrices[i][j] como el coste mínimo (en segundos) para fusionar los documentos desde el índice i hasta el
 j. El coste de una unión es la suma de las páginas del bloque resultante.

 Complejidad:

 - Coste Temporal: O(N^3), donde N es el número de documentos. Hay tres bucles anidados: uno para la longitud del
   intervalo, otro para el inicio i y un tercero para probar los puntos de corte k.

 - Coste Espacial: O(N^2), para almacenar la matriz de costes mínimos.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    int numDocs;
    cin >> numDocs;

    if (numDocs == 0) return false; // fin de la entrada

    vector<int> D(numDocs);
    vector<long long> Sumas(numDocs + 1, 0);

    for (int i = 0; i < numDocs; ++i) {
        cin >> D[i];
        Sumas[i + 1] = Sumas[i] + D[i];
    }

    Matriz<EntInf> matrices(numDocs, numDocs, 0);

    for (int d = 1; d < numDocs; ++d)

        for (int i = 0; i < numDocs - d; ++i) {
            int j = i + d;
            matrices[i][j] = Infinito;

            EntInf coste_fusion = Sumas[j + 1] - Sumas[i];

            for (int k = i; k < j; ++k) {
                EntInf temp = matrices[i][k] + matrices[k + 1][j] + coste_fusion;
                if (temp < matrices[i][j]) {
                    matrices[i][j] = temp;
                }
            }
        }

    // escribir la solución

    cout << matrices[0][numDocs - 1] << "\n";

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
