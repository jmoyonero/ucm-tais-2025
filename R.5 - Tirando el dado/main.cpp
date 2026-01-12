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

 El problema se resuelve mediante Programación Dinámica, modelándolo como el cálculo de particiones de un entero S cuyos
 sumandos están restringidos al conjunto {1,2,...,k}. Dado que la suma es conmutativa, el orden no importa, para evitar
 contar permutaciones, se asume un orden no decreciente en los sumandos.

 Definición del estado:
    Sea dp[j] el número de formas distintas de obtener la suma exacta j utilizando un subconjunto de caras del dado.

 Ecuación de recurrencia:
    Para cada cara i∈{1,...,k}, actualizamos el vector de estados de forma ascendente:
        dp[j]+=dp[j−i]; Si j∈[i,S]
    Donde:
        dp[j−i]: Formas de obtener la suma restante tras usar la cara i al menos una vez.

 Casos base:
    dp[0]=1: Solo existe una forma de obtener la suma 0 (el conjunto vacío).
    dp[j]=0; Si j>0: Inicialización antes de procesar las caras.

 Complejidad:
    Temporal: O(k * S).
    Espacial: O(S), mediante la optimización de la tabla de programación dinámica a un vector unidimensional.

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int MONEDAS, OBJETIVO;
    cin >> MONEDAS >> OBJETIVO;

    // resolver el caso posiblemente llamando a otras funciones

    vector<int> dp(OBJETIVO + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= MONEDAS; ++i) {
        for (int j = i; j <= OBJETIVO; ++j) {
            dp[j] += dp[j - i];
        }
    }

    // escribir la solución

    cout << dp[OBJETIVO] << "\n";

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
