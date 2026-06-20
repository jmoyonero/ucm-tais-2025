/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ConjuntosDisjuntos.h"

using namespace std;

/*@ <answer>

Se usa la estructura de CONJUNTOS DISJUNTOS (Union-Find). Cada celda de la rejilla es un
elemento; unimos celdas contaminadas ('#') adyacentes en las 8 direcciones. El tamaño de la
mayor mancha es el cardinal del mayor conjunto.

Construcción: al recorrer la rejilla, cada '#' se une con sus 4 vecinos "hacia delante"
(abajo-izq, abajo, abajo-der y derecha) que sean '#'. Así cada arista se trata una sola vez.
Para cada imagen nueva, marcamos la celda como '#' y la unimos con sus 8 vecinos contaminados.
Tras cada cambio, la respuesta es el mayor cardinal visto (al menos 1 si hay alguna celda
contaminada).

Complejidad:
 - Temporal: O(F*C + N), casi lineal por la casi-constante de Union-Find.
 - Espacial: O(F*C).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// traduce la coordenada (i, j) de la rejilla a un indice 1D
int idx(int i, int j, int C) {
    return i * C + j;
}

bool resuelveCaso() {
    int F, C;
    if (!(cin >> F >> C)) return false; // fin de la entrada

    vector<string> info(F);
    for (int i = 0; i < F; ++i) cin >> info[i];

    ConjuntosDisjuntos g(F * C);
    int mayor = 0;

    // construccion: unir cada '#' con sus 4 vecinos "hacia delante" (cada arista una vez)
    const int dx4[4] = {1, 1, 1, 0}, dy4[4] = {-1, 0, 1, 1};
    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < C; ++j) {
            if (info[i][j] != '#') continue;
            mayor = max(mayor, 1);
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx4[d], nj = j + dy4[d];
                if (ni >= 0 && ni < F && nj >= 0 && nj < C && info[ni][nj] == '#') {
                    g.unir(idx(i, j, C), idx(ni, nj, C));
                    mayor = max(mayor, g.cardinal(idx(i, j, C)));
                }
            }
        }
    }

    int N;
    cin >> N;

    string salida = to_string(mayor);

    // cada celda nueva se une con sus 8 vecinos contaminados
    const int dx8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int x = 0; x < N; ++x) {
        int i, j;
        cin >> i >> j;
        --i;
        --j;

        if (info[i][j] != '#') {
            info[i][j] = '#';
            mayor = max(mayor, 1);
            for (int d = 0; d < 8; ++d) {
                int ni = i + dx8[d], nj = j + dy8[d];
                if (ni >= 0 && ni < F && nj >= 0 && nj < C && info[ni][nj] == '#')
                    g.unir(idx(i, j, C), idx(ni, nj, C));
            }
            mayor = max(mayor, g.cardinal(idx(i, j, C)));
        }
        salida += " " + to_string(mayor);
    }
    cout << salida << "\n";
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
