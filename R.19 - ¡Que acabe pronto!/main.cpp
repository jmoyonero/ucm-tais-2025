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

El problema se resuelve mediante Programación Dinámica, tratándolo como una variante del Problema de la Partición (Subset Sum).
El objetivo es repartir las actividades en dos aulas de forma que la duración de la que más tarde termine sea mínima.

Definición del estado:
    dp[j] es un valor booleano que indica si es posible obtener una suma de duraciones exactamente igual a j.

Ecuación de recurrencia:
    Para cada actividad con duración 'd':
    dp[j] = dp[j] || dp[j - d]  (para todo j desde SumaTotal/2 hasta d)

Estrategia:
    1. Calculamos la suma total de duraciones (S).
    2. Buscamos el subconjunto de actividades cuya suma 's1' sea lo más cercana posible a S/2 (sin excederlo).
    3. La duración del evento será max(s1, S - s1).

Complejidad:
    - Temporal: O(N * S), donde N es el número de actividades y S la suma total de duraciones.
    - Espacial: O(S), ya que solo necesitamos un vector booleano de tamaño S/2 + 1.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    vector<int> duraciones(N);
    int total = 0;

    for (int i = 0; i < N; ++i) {
        cin >> duraciones[i];
        total += duraciones[i];
    }

    int objetivo = total / 2;

    vector<bool> dp(objetivo + 1, false);
    dp[0] = true;

    for (int i = 0; i < N; ++i) {
        for (int j = objetivo; j >= duraciones[i]; --j) {
            if (dp[j - duraciones[i]])
                dp[j] = true;
        }
    }

    int aula1 = 0;

    for (int i = objetivo; i >= 0; --i) {
        if (dp[i]) {
            aula1 = i;
            break;
        };
    }

    int aula2 = total - aula1;

    // escribir la solución

    cout << max(aula1, aula2) << "\n";

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
