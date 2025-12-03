/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "Matriz.h"
#include "EnterosInf.h"


/*@ <answer>

 Seis Grados de Separación (Caminos Mínimos en Grafos)

 Usamos el algoritmo de Floyd-Warshall para calcular la distancia mínima entre todos los pares de personas.
 El "grado de separación" de la red es la máxima distancia encontrada en la matriz final.

 Recurrencia (Floyd-Warshall):
 C[i][j] = min(C[i][j], C[i][k] + C[k][j])
 (Iterando k desde 0 hasta P-1 como nodo intermedio)

 Complejidad:
 - Coste Temporal: O(P^3), donde P es el número de personas (P <= 500).
 - Coste Espacial: O(P^2). Matriz de adyacencia PxP.

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


bool resuelveCaso() {
    // leer los datos de la entrada

    int P, R;
    cin >> P >> R;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp


    Matriz<EntInf> G(P, P, Infinito);
    for (int i = 0; i < P; ++i) G[i][i] = 0;

    map<string, int> personas;

    for (int i = 0; i < R; ++i) {
        string persona1, persona2;
        cin >> persona1 >> persona2;

        if (!personas.count(persona1))personas[persona1] = personas.size();
        if (!personas.count(persona2))personas[persona2] = personas.size();

        int u = personas[persona1];
        int v = personas[persona2];

        G[u][v] = 1;
        G[v][u] = 1;
    }

    Matriz<EntInf> C(P, P, Infinito);
    Matriz<int> A(P, P, 0);

    Floyd(G, C, A);

    EntInf maxGrado = 0;

    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < P; ++j) {
            if (C[i][j] == Infinito) {
                cout << "DESCONECTADA" << "\n";
                return true;
            }
            maxGrado = max(maxGrado, C[i][j]);
        }
    }
    cout << maxGrado << "\n";

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
