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

// propios o los de las estructuras de datos de clase

/*@ <answer>

 El problema se resuelve mediante un algoritmo voraz.
 Para maximizar el descuento debemos intentar que los libros regalados (el tercero de cada lote) sean los de mayor
 precio posible.

 Para ello:
    1. Ordenamos los precios de los libros de mayor a menor.
    2. Los agrupamos de tres en tres.
    3. El tercer libro de cada grupo será el regalo de máximo valor para ese lote.

 Complejidad:

 - Coste Temporal: O(N log N). Debido a la ordenación del vector de precios (donde N es el número de libros).
 - Coste Espacial: O(N). Para almacenar los precios de los libros en un vector.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!cin) return false; // fin de la entrada

    vector<int> libros(N);

    for (int i = 0; i < N; ++i) {
        cin >> libros[i];
    }

    sort(libros.begin(), libros.end(), greater<int>());

    int ahorro = 0;

    for (int i = 2; i < N; i += 3) {
        ahorro += libros[i];
    }

    // escribir la solución

    cout << ahorro << "\n";

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
