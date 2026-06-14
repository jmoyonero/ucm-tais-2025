 /*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

/*@ <answer>

Solución: Mantener la mediana de las edades (el ave de la punta) según se añaden parejas.

La bandada va ordenada por edad y la punta es el ave central (la mediana). Como se empieza con 1 ave y
se añaden parejas (2 aves), el total es siempre impar, así que la mediana es el elemento central único.

Mantenemos la mediana con dos montículos: 'menores' (max-heap con la mitad de edades más bajas) y
'mayores' (min-heap con la mitad más altas). Tras cada inserción reequilibramos para que 'menores' tenga
a lo sumo un elemento más que 'mayores'. Con el total impar, la mediana es siempre la cima de 'menores'.

Por cada pareja insertamos sus dos edades e imprimimos la nueva punta.

Complejidad (k = nº total de aves del caso):
 - Temporal: O(k log k) por las inserciones en los montículos.
 - Espacial: O(k) por las aves almacenadas.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Bandada {
    priority_queue<int> menores;                           // max-heap: mitad más joven
    priority_queue<int, vector<int>, greater<>> mayores;   // min-heap: mitad más vieja

    void anade(int edad) {
        if (menores.empty() || edad <= menores.top()) menores.push(edad);
        else mayores.push(edad);

        // 'menores' tiene a lo sumo un elemento más que 'mayores'.
        if (menores.size() > mayores.size() + 1) {
            mayores.push(menores.top());
            menores.pop();
        } else if (mayores.size() > menores.size()) {
            menores.push(mayores.top());
            mayores.pop();
        }
    }

    // La punta es la mediana; como el total es impar, es la cima de 'menores'.
    int punta() const { return menores.top(); }
};

bool resuelveCaso() {
    int primera, parejas;
    cin >> primera >> parejas;
    if (primera == 0 && parejas == 0) return false;

    Bandada bandada;
    bandada.anade(primera);

    for (int i = 0; i < parejas; ++i) {
        int a, b;
        cin >> a >> b;
        bandada.anade(a);
        bandada.anade(b);
        cout << bandada.punta() << (i + 1 < parejas ? ' ' : '\n');
    }

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
