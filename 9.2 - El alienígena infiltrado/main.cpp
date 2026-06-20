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

Recubrimiento mínimo de un intervalo (minimum interval cover), resuelto con un algoritmo VORAZ.

Hay que cubrir [C, F) con el mínimo número de trabajos [c_i, f_i), que pueden solapar; si no se
puede cubrir todo el intervalo, es "Imposible".

Estrategia:
Ordenamos los trabajos por su comienzo c ascendente. Llevamos 'cubierto' = punto hasta el que
tenemos cobertura continua desde C (inicialmente C). En cada ronda, entre todos los trabajos cuyo
comienzo c <= cubierto (los que no dejan hueco), elegimos el de mayor fin f y hacemos cubierto = f,
sumando 1 al contador. Repetimos hasta que cubierto >= F.

Si en una ronda ningún trabajo disponible avanza más allá de 'cubierto' (queda un hueco), es
imposible.

¿Por qué es óptimo?
Para cubrir a partir de 'cubierto' hay que usar algún trabajo que no deje hueco (c <= cubierto).
Entre ellos, elegir el de mayor f nunca es peor: cualquier solución óptima que usara otro se puede
transformar para usar este sin aumentar el total, porque deja cubierto al menos tanto terreno
(argumento de intercambio). Aplicado de forma repetida, el voraz da el mínimo.

Complejidad:
 - Temporal: O(N log N), dominada por la ordenación (el recorrido es O(N) con un puntero).
 - Espacial: O(N), por el vector de trabajos.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Intervalo {
    int c;
    int f;

    bool operator<(const Intervalo &o) const {
        return c < o.c;
    }
};

bool resuelveCaso() {
    int C, F, N;
    cin >> C >> F >> N;
    if (!cin) return false; // fin de entrada
    if (C == 0 && F == 0 && N == 0) return false;

    vector<pair<int, int> > v(N); // (comienzo c, fin f)
    for (auto &p: v) cin >> p.first >> p.second;

    sort(v.begin(), v.end());

    long long cubierto = C; // cubierto sin huecos desde C
    int usados = 0;
    int i = 0;
    bool posible = true;

    while (cubierto < F) {
        long long mejorFin = cubierto; // mejor alcance de esta ronda
        while (i < N && v[i].first <= cubierto) {
            mejorFin = max(mejorFin, (long long) v[i].second);
            ++i;
        }
        if (mejorFin == cubierto) {
            posible = false;
            break;
        } // nadie avanza → hueco
        cubierto = mejorFin;
        ++usados;
    }

    cout << (posible ? to_string(usados) : "Imposible") << "\n";
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
