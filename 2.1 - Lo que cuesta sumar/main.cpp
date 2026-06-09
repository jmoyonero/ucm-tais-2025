/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/*@ <answer>

Solución: Calcular lo que cuesta sumar.

El esfuerzo mínimo se obtiene con el algoritmo de mezcla óptima (Huffman): en cada paso se cogen los dos sumandos
menores, se suman (lo que añade ese valor al coste total) y el resultado se reinserta como un nuevo sumando.

Para ello usamos una priority_queue de mínimos: extraemos los dos menores, sumamos, acumulamos el coste y reinsertamos
la suma. Repetimos hasta que solo quede un elemento.

Como los valores acumulados pueden superar el rango de int (hasta ~10^12 con N=100.000 y sumandos de 10^6), usamos
long long.

Complejidad:
 - Temporal: O(n log n) por las n extracciones/inserciones en la priority_queue
 - Espacial: O(n) por el número de sumandos

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;

    priority_queue<long long, vector<long long>, greater<> > cola;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        cola.push(x);
    }

    long long costoSuma = 0;
    while (cola.size() > 1) {
        long long a = cola.top(); cola.pop();
        long long b = cola.top(); cola.pop();
        long long suma = a + b;
        costoSuma += suma;
        cola.push(suma);
    }

    cout << costoSuma << "\n";

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
