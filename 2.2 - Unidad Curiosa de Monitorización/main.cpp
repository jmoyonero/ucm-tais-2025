/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/*@ <answer>

Solución: Obtener identificadores de los usuarios que recibirán los K primeros envíos.

Usamos una priority_queue de mínimos ordenada por el instante del próximo envío, con desempate por id
creciente. Cada usuario entra con proximoEnvio = periodicidad; en cada envío extraemos el mínimo, imprimimos su id y lo
reinsertamos con proximoEnvio += periodicidad. Repetimos K veces.

Complejidad:
 - Temporal: O((n + K) log n) por las inserciones iniciales y las K extracciones/reinserciones
 - Espacial: O(n) por los usuarios en la priority_queue

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Usuario {
    int id;
    int periodicidad;
    int proximoEnvio; // instante del siguiente envío a este usuario

    // Se atiende primero a quien tenga el envío más próximo.
    // A igualdad de instante, gana el menor identificador.
    bool operator>(const Usuario &otro) const {
        if (proximoEnvio == otro.proximoEnvio) return id > otro.id;
        return proximoEnvio > otro.proximoEnvio;
    }
};


bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;

    // Min-heap de usuarios ordenado por el instante de su próximo envío.
    priority_queue<Usuario, vector<Usuario>, greater<> > cola;
    for (int i = 0; i < n; i++) {
        int id, periodicidad;
        cin >> id >> periodicidad;
        cola.push({id, periodicidad, periodicidad}); // primer envío al cumplirse un periodo
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        Usuario u = cola.top();
        cola.pop();
        cout << u.id << "\n";
        u.proximoEnvio += u.periodicidad; // se reprograma para el siguiente periodo
        cola.push(u);
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
