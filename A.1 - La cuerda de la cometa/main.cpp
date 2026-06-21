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

Mochila 0/1 (Knapsack Problem) con tabla 2D, optimizada a dos filas.

Conceptualmente dp[i][j] = respuesta usando los primeros i cordeles para sumar exactamente la
longitud j. Cada celda combina dos casos disjuntos: NO usar el cordel i (dp[i-1][j]) o SÍ usarlo,
en cuyo caso lo que falta lo cubren los cordeles anteriores (dp[i-1][j-l]). Como cada celda solo
mira la fila i-1, basta guardar DOS filas (anterior y actual) e ir alternándolas: así la memoria
baja de O(N*L) a O(L).

Caso base (igual para las tres magnitudes): fila anterior[0] = {formas:1, minCuerdas:0, minCoste:0};
el resto = {0, Infinito, Infinito}.

Recurrencia (si l <= j; si no, act[j] = ant[j]):
  Matemático: act[j].formas     = ant[j].formas + ant[j-l].formas
  Ingeniero:  act[j].minCuerdas = min(ant[j].minCuerdas, ant[j-l].minCuerdas + 1)
  Economista: act[j].minCoste   = min(ant[j].minCoste,   ant[j-l].minCoste + coste)

La respuesta está en la fila final, posición L: si formas > 0 escribimos SI con las tres
magnitudes, si no, NO.

Complejidad:
 - Coste Temporal: O(N * L).
 - Coste Espacial: O(L). Solo se guardan dos filas (anterior y actual).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Cometa {
    long long formas;
    EntInf minCoste;
    EntInf minCuerdas;
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, L;
    cin >> N >> L;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: solo guardamos la fila anterior (ant) y la actual (act)

    vector<Cometa> ant(L + 1, {0, Infinito, Infinito});
    vector<Cometa> act(L + 1);

    ant[0] = {1, 0, 0};

    for (int i = 1; i <= N; i++) {
        int longitud, coste;
        cin >> longitud >> coste;

        for (int j = 0; j <= L; j++) {
            act[j] = ant[j]; // caso: NO uso el cordel i
            if (j >= longitud) {
                // caso: SÍ lo uso (si cabe)
                const Cometa &prev = ant[j - longitud];
                act[j].formas += prev.formas;
                act[j].minCuerdas = min(act[j].minCuerdas, prev.minCuerdas + 1);
                act[j].minCoste = min(act[j].minCoste, prev.minCoste + coste);
            }
        }

        swap(ant, act); // la fila actual pasa a ser la anterior para el siguiente cordel
    }

    // escribir la solución

    if (ant[L].formas > 0) {
        cout << "SI " << ant[L].formas << " " << ant[L].minCuerdas << " " << ant[L].minCoste << "\n";
    } else {
        cout << "NO\n";
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
