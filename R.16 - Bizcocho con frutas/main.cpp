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
#include "Matriz.h"

/*@ <answer>

 El problema se resuelve mediante Programación Dinámica de intervalos, similar al problema del "Tiro al patíndromo".

 Definimos dp[i][j] como el número máximo de días exitosos que se pueden obtener con los trozos del bizcocho en el
 rango [i...j]. En cada paso (día), se eligen dos trozos de los extremos, lo que reduce el intervalo en dos unidades.

 Existen tres transiciones posibles para cada intervalo (i, j):
  1. Cortar ambos trozos de la izquierda: (i, i+1).
  2. Cortar ambos trozos de la derecha: (j-1, j).
  3. Cortar uno de cada extremo: (i, j).

 Un día es exitoso si ambos trozos tienen la misma fruta y esta es distinta de cero (naranja o limón).

 Complejidad:

 - Coste Temporal: O(N^2). Donde N es el número de trozos.
 - Coste Espacial: O(N^2). Por la matriz necesaria para almacenar los resultados.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int bizcocho_rec(vector<int> const &frutas, int i, int j, Matriz<int> &memoria) {
    // Caso básico: no quedan trozos suficientes para un día
    if (i >= j) return 0;

    // Si el subproblema ya ha sido resuelto
    int res = memoria[i][j];
    if (res != -1) return res;

    // Casos recursivos: evaluar las 3 opciones de corte diario

    // Opción 1: Consumir dos trozos de la izquierda (i, i+1)
    int izq = ((frutas[i] != 0 && frutas[i] == frutas[i + 1]) ? 1 : 0)
              + bizcocho_rec(frutas, i + 2, j, memoria);

    // Opción 2: Consumir dos trozos de la derecha (j-1, j)
    int der = ((frutas[j - 1] != 0 && frutas[j - 1] == frutas[j]) ? 1 : 0)
              + bizcocho_rec(frutas, i, j - 2, memoria);

    // Opción 3: Consumir uno de cada extremo (i, j)
    int ambos = ((frutas[i] != 0 && frutas[i] == frutas[j]) ? 1 : 0)
                + bizcocho_rec(frutas, i + 1, j - 1, memoria);

    // El resultado es el máximo de las tres decisiones
    return memoria[i][j] = max({izq, der, ambos});
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!cin) return false; // fin de la entrada

    vector<int> frutas(N);

    for (int i = 0; i < N; ++i) cin >> frutas[i];

    // escribir la solución

    Matriz<int> memoria(N, N, -1);

    int formas = bizcocho_rec(frutas, 0, N - 1, memoria);

    cout << formas << "\n";

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
