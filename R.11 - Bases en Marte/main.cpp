/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

// propios o los de las estructuras de datos de clase


/*@ <answer>

 El problema se resuelve mediante una estrategia voraz (greedy) equivalente al Algoritmo de Huffman.

 El problema se resuelve mediante una simulación de eventos utilizando una cola de prioridad (min-heap).
 Almacenamos las baterías activas en el heap ordenadas por su tiempo de agotamiento (fin).
 En cada paso, procesamos la batería que se agota primero:
    1. Si se puede recargar (carga > perdida), se reinserta con su nuevo tiempo.
    2. Si no, se intenta sustituir por el primer repuesto disponible (FIFO usando queue).

 Complejidad: O(E log B), donde E es el número de eventos de mantenimiento y B el número de baterías.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Bateria {
    int id;
    long long fin;
    long long carga;

    bool operator<(const Bateria &otro) const {
        if (fin != otro.fin) return fin > otro.fin;
        return id > otro.id;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int numBaterias;
    cin >> numBaterias;

    if (!cin) return false; // fin de la entrada

    priority_queue<Bateria> baterias;

    for (int i = 0; i < numBaterias; ++i) {
        int capacidad;
        cin >> capacidad;
        baterias.push({i + 1, capacidad, capacidad});
    }

    int numRepuestos;
    cin >> numRepuestos;

    queue<pair<int, int> > repuestos;

    for (int i = numBaterias; i < numRepuestos + numBaterias; ++i) {
        int capacidad;
        cin >> capacidad;
        repuestos.push({i + 1, capacidad});
    }

    int perdida, tiempoConsulta;
    cin >> perdida >> tiempoConsulta;

    while (!baterias.empty() && baterias.top().fin <= tiempoConsulta) {
        auto bateria = baterias.top();
        baterias.pop();

        if (bateria.carga > perdida) {
            // Recargamos
            bateria.carga -= perdida;
            bateria.fin += bateria.carga;
            baterias.push(bateria);
        } else if (!repuestos.empty()) {
            // Cambiamos
            auto repuesto = repuestos.front();
            repuestos.pop();
            baterias.push({repuesto.first, bateria.fin + repuesto.second, repuesto.second});
        }
    }

    if (baterias.empty()) {
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    } else {
        if (baterias.size() != numBaterias) {
            cout << "FALLO EN EL SISTEMA\n";
        } else {
            cout << "CORRECTO\n";
        }

        while (!baterias.empty()) {
            cout << baterias.top().id << " " << baterias.top().fin << "\n";
            baterias.pop();
        }
    }

    // escribir la solución

    cout << "---\n";

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
