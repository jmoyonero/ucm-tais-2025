/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"
#include "vector"

using namespace std;

/*@ <answer>

Solución: Simular cada sábado de vuelo con dos montículos de máximos.

Mantenemos dos max-heaps con las cargas de las pilas: uno de 9V y otro de 1.5V. Cada sábado emparejamos
las pilas más cargadas de cada tipo, hasta min(N, Num 9V, Num 1.5V) drones. Un dron con pilas a (9V) y b (1.5V)
vuela min(a,b) horas, la pila más cargada conserva |a-b| horas y vuelve a su caja, la otra se agota y se
descarta (si a==b se descartan las dos).

Sumamos las horas de cada sábado y repetimos mientras queden pilas de los dos tipos.

Importante: las sobras se devuelven después del sábado (no se reutilizan ese día), así que las guardamos
en un vector temporal y las reinsertamos al terminar el sábado.

Cada emparejamiento elimina al menos una pila del sistema, luego el nº total de emparejamientos de todo
el caso es <= A+B.

Complejidad:
 - Temporal: O((A+B) log(A+B)).
 - Espacial: O(A+B).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int N, A, B;
    if (!(cin >> N >> A >> B)) return false;

    // max-heaps (greater<> hace que la cima sea la pila más cargada)
    PriorityQueue<int, greater<> > nueve; // pilas de 9 V
    PriorityQueue<int, greater<> > peq; // pilas de 1.5 V
    for (int i = 0; i < A; ++i) {
        int x;
        cin >> x;
        nueve.push(x);
    }
    for (int i = 0; i < B; ++i) {
        int x;
        cin >> x;
        peq.push(x);
    }

    string sep;
    while (!nueve.empty() && !peq.empty()) {
        int drones = min({N, nueve.size(), peq.size()});
        long long total = 0;
        vector<int> sobran9, sobran15; // sobras que vuelven a la caja tras el sábado

        for (int i = 0; i < drones; ++i) {
            int a = nueve.top();
            nueve.pop();
            int b = peq.top();
            peq.pop();
            total += min(a, b);
            if (a > b) sobran9.push_back(a - b);
            else if (b > a) sobran15.push_back(b - a);
        }
        for (int x: sobran9) nueve.push(x);
        for (int x: sobran15) peq.push(x);

        cout << sep << total;
        sep = " ";
    }
    cout << "\n";

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
