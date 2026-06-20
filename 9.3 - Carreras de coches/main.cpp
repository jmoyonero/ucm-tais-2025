/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*@ <answer>

Este problema se resuelve con un algoritmo VORAZ basado en dos punteros.
Cada coche necesita 2 pilas cuyos voltajes sumen al menos V. Queremos maximizar el número de
coches en funcionamiento (número de parejas con suma >= V).

Estrategia:
Ordenamos las pilas de mayor a menor (O(N log N)). Mantenemos dos punteros: i en la pila de
mayor voltaje aún libre y j en la de menor voltaje aún libre. En cada paso:
  - Si pila[i] + pila[j] >= V, forman un coche: las usamos (++i, --j).
  - Si no llegan a V, la pila de MENOR voltaje (j) no puede formar coche ni con la mayor
    disponible, así que es inservible y la descartamos (--j); i no se mueve.
Repetimos mientras i < j. Si al final queda una sola pila, no forma coche.

¿Por qué es óptimo?
La decisión la marca la pila de MENOR voltaje (pila[j]):
  - Si no alcanza V ni sumada con la de mayor voltaje disponible, no puede emparejarse con
    ninguna, luego descartarla es forzoso, no una elección.
  - Si sí alcanza V con la mayor, emparejarlas es al menos tan bueno como cualquier solución
    óptima: dada una óptima que emparejara la mayor con otra pila, podemos intercambiarla por
    la menor sin perder coches (la menor "estorba" menos en cualquier otra pareja). Por el
    argumento de intercambio, existe una óptima que contiene nuestra elección.
Aplicando este razonamiento sobre el subproblema restante, el voraz construye el óptimo.

Complejidad:
 - Temporal: O(N log N), dominada por la ordenación (el recorrido es O(N)).
 - Espacial: O(N), por el vector de pilas.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N, V;
    cin >> N >> V;

    vector<int> pilas(N);

    for (int i = 0; i < N; ++i) cin >> pilas[i];

    // resolver el caso posiblemente llamando a otras funciones

    sort(pilas.begin(), pilas.end(), greater<int>()); // ordenar de mayor a menor voltaje

    int i = 0;
    int j = N - 1;
    int total = 0;

    while (i < j) {
        if (pilas[i] + pilas[j] >= V) {
            ++total;
            ++i;
        }
        --j;
    }

    // escribir la solución

    cout << total << "\n";

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

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif

    return 0;
}
