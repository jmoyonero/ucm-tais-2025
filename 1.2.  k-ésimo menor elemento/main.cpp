/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"

using namespace std;

/*@ <answer>

Solución: Encontrar el k-ésimo menor elemento en un árbol AVL.

Cada nodo mantiene tam_i = número de nodos en su subárbol izquierdo + 1.

Búsqueda del k-ésimo elemento:
- Si k < tam_i: buscar en hijo izquierdo
- Si k == tam_i: la raíz es el k-ésimo elemento
- Si k > tam_i: buscar en hijo derecho con k - tam_i

El campo tam_i se mantiene en O(1), sin contar nodos:
- al insertar/borrar en el hijo izquierdo, se incrementa/decrementa en 1
- al insertar/borrar en el hijo derecho, no cambia
- en las rotaciones se recalcula con aritmética entre los tam_i implicados

Complejidad:
 - Temporal: O(log n) para la búsqueda kesimo
 - Espacial: O(n) para el árbol

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;

    Set<int> tree;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        tree.insert(x);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        try {
            cout << tree.kesimo(k) << "\n";
        } catch (const exception &e) {
            cout << "??\n";
        }
    }

    cout << "---\n";

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
