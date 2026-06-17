/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "ConjuntosDisjuntos.h"

using namespace std;

/*@ <answer>

La noticia se propaga entre amigos (dos usuarios son amigos si comparten algún grupo) hasta que no
queda ninguna pareja amigo-conoce / amigo-no-conoce. Eso significa que la noticia acaba alcanzando
exactamente a TODOS los usuarios de la misma componente conexa del grafo de amistades. Por tanto, el
número de usuarios que conocen la noticia partiendo de i es el tamaño de la componente conexa de i.

No hace falta construir el grafo con aristas entre todos los pares de un grupo (un grupo de k usuarios
daría k*(k-1)/2 aristas). Basta una estructura de CONJUNTOS DISJUNTOS: por cada grupo unimos a todos sus
miembros con el primero de ellos, lo que deja a cada componente conexa en un único conjunto.
La respuesta para el usuario i es el cardinal de su conjunto.

Complejidad por caso (N usuarios, S = suma de tamaños de los grupos):
 - Temporal: O((N + S) · α(N)), prácticamente lineal por la unión por tamaño y compresión de caminos.
 - Espacial: O(N) por la estructura de partición.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int N, M;
    if (!(cin >> N >> M)) return false; // fin de la entrada

    ConjuntosDisjuntos cjs(N); // usuarios 0..N-1 (los identificadores 1..N van -1)
    for (int g = 0; g < M; ++g) {
        int k;
        cin >> k;
        int primero = -1;
        for (int i = 0; i < k; ++i) {
            int u;
            cin >> u;
            --u;
            if (primero == -1) primero = u;
            else cjs.unir(primero, u); // todos los del grupo quedan en el mismo conjunto
        }
    }

    for (int i = 0; i < N; ++i)
        cout << cjs.cardinal(i) << (i + 1 < N ? " " : "\n");
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
