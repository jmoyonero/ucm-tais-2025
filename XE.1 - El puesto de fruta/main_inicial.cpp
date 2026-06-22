/*@ <authors>
*
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

#include "IndexPQ.h"

// propios o los de las estructuras de datos de clase

/*@ <answer>


Complejidad:
 - Coste Temporal: O(N*Q log N) por las inserciones en la IndexPQ.
 - Coste Espacial: O(N ). Solo se usa un vector.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


struct Fruta {
    string nombre;
    int cantidad;

    bool operator>(const Fruta &f) const {
        return cantidad > f.cantidad;
    }

    bool operator<(const Fruta &f) const {
        return cantidad < f.cantidad;
    }
};

string ToString(const Fruta &f) {
    if (f.cantidad > 0) return f.nombre + " " + to_string(f.cantidad);
    return "NO HAY";
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (N == 0) return false; // fin de la entrada

    map<string, int> inventario;
    map<string, int> indices;
    map<string, int> ventas;
    IndexPQ<Fruta, greater<> > pq(N + 1);
    IndexPQ<Fruta, greater<> > pqVentas(N + 1);

    for (int i = 1; i <= N; ++i) {
        string nombre;
        int cantidadInicial;
        cin >> nombre >> cantidadInicial;
        inventario[nombre] = cantidadInicial;
        indices[nombre] = i;
        pq.push(i, {nombre, cantidadInicial});
        pqVentas.push(i, {nombre, 0});
    }

    int E;
    cin >> E;

    for (int j = 0; j < E; ++j) {
        char evento;
        cin >> evento;

        if (tolower(evento) == 'q') {
            // Consulta fruta más vendida (Q)

            // escribir la solución
            cout << ToString(pq.top().prioridad) << "; " << ToString(pqVentas.top().prioridad) << endl;
        } else {
            string eNombre;
            int eCantidad;
            cin >> eNombre >> eCantidad;

            if (tolower(evento) == 'c') {
                // Venta
                if (inventario[eNombre] >= eCantidad) {
                    ventas[eNombre] += eCantidad;
                    inventario[eNombre] -= eCantidad;
                } else {
                    ventas[eNombre] += inventario[eNombre];
                    inventario[eNombre] = 0;
                }
                pqVentas.update(indices[eNombre], {eNombre, ventas[eNombre]});
            } else {
                // Stock (P)
                inventario[eNombre] += eCantidad;
            }
            pq.update(indices[eNombre], {eNombre, inventario[eNombre]});
        }
    }

    cout << "---" << endl;

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
