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

 El problema se resuelve mediante programación dinámica.

 El problema se modela como un grafo dirigido ponderado donde los poblados son los vértices y los costes de alquiler son
 las aristas. Dado que solo se puede viajar "a favor de la corriente" (i<j), el grafo es un DAG (Grafo Acíclico Dirigido).

 Como queremos encontrar el camino entre todo par de poblados utilizaremos el algoritmo de Floyd.

 Complejidad:

 - Coste Temporal: O(N^3), donde N es el número de poblados. Los tres bucles anidados recorren todos los posibles nodos intermedios k.
 - Coste Espacial: O(N^2), para almacenar la matriz de costes mínimos C y la matriz de reconstrucción de caminos A.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void Floyd(Matriz<EntInf> const &G, Matriz<EntInf> &C, Matriz<int> &A) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<int>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != Infinito)
                A[i][j] = i;
        }
    }
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) {
                    // es mejor pasar por k
                    C[i][j] = temp;
                    A[i][j] = A[k][j];
                }
            }
        }
    }
}

using Camino = std::deque<int>;

Camino ir_de(int i, int j, Matriz<int> const &A) {
    Camino cam;
    while (j != i) {
        cam.push_front(j);
        j = A[i][j];
    }
    cam.push_front(i);
    return cam;
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int numPoblados;
    cin >> numPoblados;

    if (!cin) return false; // fin de la entrada


    Matriz<EntInf> poblados(numPoblados, numPoblados, Infinito);
    Matriz<EntInf> C(numPoblados, numPoblados, Infinito);
    Matriz<int> A(numPoblados, numPoblados, 0);

    for (int i = 0; i < numPoblados - 1; ++i) {
        for (int j = i + 1; j < numPoblados; ++j) {
            int distancia;
            cin >> distancia;
            poblados[i][j] = distancia;
        }
    }

    Floyd(poblados, C, A);

    // escribir la solución

    for (int i = 0; i < numPoblados; ++i) {
        for (int j = i + 1; j < numPoblados; ++j) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
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
