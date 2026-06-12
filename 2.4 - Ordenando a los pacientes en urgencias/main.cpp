/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

/*@ <answer>

Solución: Atender en cada evento 'A' al paciente más grave de los que esperan.

Mantenemos a los pacientes en espera en una priority_queue de máximos ordenada por gravedad. El
desempate "el que más tiempo lleva esperando" se resuelve asignando a cada paciente un id creciente
según su orden de llegada: a igual gravedad, gana el de menor id.

Por cada evento:
 - 'I nombre gravedad': insertamos el paciente.
 - 'A': imprimimos el nombre de la cima (el más prioritario) y lo extraemos.

Complejidad:
 - Temporal: O(N log N) por las N inserciones/extracciones en el montículo.
 - Espacial: O(N) por los pacientes en la priority_queue.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Paciente {
    int id;
    string nombre;
    int gravedad;

    bool operator>(const Paciente &otro) const {
        if (gravedad == otro.gravedad) return id < otro.id;
        return gravedad > otro.gravedad;
    }
};


bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;

    // Max-heap de pacientes: en la cima el paciente que mas grave se encuentre.
    PriorityQueue<Paciente, greater<> > pacientes;
    for (int i = 0; i < n; ++i) {
        char event;
        cin >> event;
        if (event == 'A') {
            cout << pacientes.top().nombre << "\n";
            pacientes.pop();
            continue;
        }

        string nombre;
        int gravedad;
        cin >> nombre >> gravedad;

        pacientes.push({i, nombre, gravedad});
    }

    cout << "---\n";

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
