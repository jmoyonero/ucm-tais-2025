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

Este problema es el clásico "mínimo número de puntos que pinchan todos los intervalos" (minimum stabbing),
resuelto con un algoritmo VORAZ.

Cada edificio es un intervalo entre su extremo occidental (W) y el oriental (E). Un túnel mide 1 metro de ANCHO y
debe quedar completamente debajo del edificio: si su borde izquierdo es x, ocupa [x, x+1] y necesita W <= x y
x+1 <= E, es decir W <= x <= E-1. Por tanto cada edificio se modela como el intervalo [W, E-1] y buscamos el mínimo
número de puntos (túneles) que pinchen todos esos intervalos.

Estrategia:
Ordenamos los edificios por su extremo ORIENTAL (E) ascendente. Recorriéndolos de izquierda a derecha mantenemos la
posición 'pos' del último túnel colocado (al principio ninguno):

  - Si el edificio actual no está cubierto (su W es mayor que 'pos'), necesita un túnel nuevo.
  - Ese túnel lo colocamos lo más a la derecha posible que aún quepa: pos = E - 1.

Repetimos hasta agotar los edificios.

¿Por qué es óptimo?
Ordenados por E, el primer edificio sin cubrir DEBE recibir un túnel. Colocarlo en E-1 es óptimo: cualquier túnel
válido para él está en [W, E-1], y E-1 es la posición que maximiza los edificios posteriores que también puede
pinchar (un punto más a la izquierda solo pincharía un subconjunto de ellos). Por el argumento de intercambio,
existe una solución óptima que usa esa posición; aplicándolo sobre el resto, el voraz construye el óptimo.

Complejidad:
 - Temporal: O(N log N), dominada por la ordenación.
 - Espacial: O(N), por el vector de edificios.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Edificio {
    int w;
    int e;

    bool operator<(const Edificio &o) const {
        return e < o.e;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones
    vector<Edificio> edificios(N);
    for (auto &ed: edificios) cin >> ed.w >> ed.e;

    sort(edificios.begin(), edificios.end()); // O(N log N) por E

    int numTuneles = 0;
    long long pos = -1; // borde del último túnel; -1 = ninguno
    for (const auto &ed: edificios) {
        if (ed.w > pos) {
            ++numTuneles;
            pos = ed.e - 1;
        }
    }

    // escribir la solución

    cout << numTuneles << "\n";

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
