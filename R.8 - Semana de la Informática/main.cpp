/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// propios o los de las estructuras de datos de clase


/*@ <answer>

 El objetivo es determinar el número máximo de intervalos que se solapan en un instante dado, lo cual define el número
 de recursos (personas) necesarios.

 Estrategia: Utilizamos un enfoque voráz (greedy):

 Ordenamos las actividades por su tiempo de inicio.

 Utilizamos una cola de prioridad de mínimos para almacenar los tiempos de finalización de las actividades que están
 siendo atendidas actualmente.

 Para cada nueva actividad:
    - Si su inicio es mayor o igual al fin más próximo en la cola (minimos.top()), la persona ha quedado libre.
      Actualizamos ese tiempo de fin con el de la nueva actividad.
    - Si su inicio es menor, necesitamos una persona adicional.

 Complejidad:
 - Temporal: O(N log N) debido a la ordenación inicial y a las operaciones de la cola de prioridad.
 - Espacial: O(N) para almacenar las actividades y la cola de prioridad.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Actividad {
    int inicio, fin;

    bool operator<(const Actividad &otra) const {
        return inicio < otra.inicio;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (N == 0) return false; // fin de la entrada

    vector<Actividad> actividades(N);

    for (int i = 0; i < N; ++i) {
        cin >> actividades[i].inicio >> actividades[i].fin;
    }

    sort(actividades.begin(), actividades.end());

    // resolver el caso posiblemente llamando a otras funciones

    priority_queue<int, vector<int>, greater<> > finActividades;

    for (Actividad act: actividades) {
        if (!finActividades.empty() && act.inicio >= finActividades.top()) {
            finActividades.pop();
        }
        finActividades.push(act.fin);
    }

    // escribir la solución

    cout << finActividades.size() - 1 << "\n";

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
