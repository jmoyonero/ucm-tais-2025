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

Cada silla admite a lo sumo 2 usuarios y la suma de sus pesos no puede superar el máximo P de la silla. Queremos
minimizar el número de sillas.

Estrategia:
Ordenamos los pesos de mayor a menor (O(C log C)). Mantenemos dos punteros: i apunta al usuario más pesado aún sin subir
y j al más ligero. En cada paso:

  - Si pesos[i] + pesos[j] <= P, ambos caben: los subimos juntos (i++, j--).
  - Si no caben, el más pesado sube solo (i++); j no se mueve.

En ambos casos se usa una silla. Repetimos hasta que los punteros se cruzan. Cuando i == j queda un único usuario, que
sube solo en su propia silla.

¿Por qué es óptimo?
Al usuario más pesado hay que subirlo en ALGUNA silla, así que no perdemos nada tratándolo ya. Solo puede ir acompañado
por alguien con quien sume <= P:

  - Si el más ligero NO cabe con él, entonces NINGÚN otro usuario cabe (todos pesan >= que el más ligero), luego el más
    pesado debe ir solo. Es forzoso, no una elección.
  - Si el más ligero SÍ cabe, emparejarlos es siempre al menos tan bueno como cualquier otra solución óptima: dada una
    solución óptima donde el más pesado va con otro x (o solo), podemos intercambiar a x por el más ligero sin aumentar
    el número de sillas (el más ligero "estorba" menos en cualquier otra silla, pues su hueco lo puede ocupar
    cualquiera). Por tanto existe una solución óptima que contiene nuestra elección.

Aplicando este razonamiento repetidamente sobre el subproblema restante, el voraz construye una solución óptima.

Complejidad:
 - Temporal: O(C log C), dominada por la ordenación (el recorrido es O(C)).
 - Espacial: O(C), por el vector de pesos.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada
    int P, C;
    cin >> P >> C;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    vector<int> usuarios(C);

    for (int i = 0; i < C; ++i) {
        cin >> usuarios[i];
    }

    sort(usuarios.begin(), usuarios.end(), greater<int>()); // ordenar de mayor a menor peso

    int i = 0;
    int j = C - 1;
    int total = 0;

    while (i <= j) {
        if (usuarios[i] + usuarios[j] <= P) --j; // (ordenado ascendente) emparejas ligero+pesado
        ++i;
        ++total;
    }

    // escribir la solución

    cout << total << endl;

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
