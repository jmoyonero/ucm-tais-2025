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

Idea:
 - El STOCK sube y baja, así que necesita una cola de prioridad indexada (IndexPQ) sobre la que consultar el máximo: el
   elemento es el índice de la fruta y la prioridad es {nombre, cantidad}. top() da en O(1) la fruta más abundante y
   cada reposición/venta es un update() en O(log N).
 - Las VENTAS solo crecen y cada evento C modifica el total de una única fruta, por lo que la más vendida solo puede
   pasar a ser la fruta recién vendida. Basta con acumular las ventas en un vector indexado por la fruta y mantener
   una variable 'masVendida' que se actualiza en O(1) tras cada venta. No hace falta un montículo para las ventas.
 - Los empates se resuelven dentro de operator> (mayor cantidad y, a igualdad, nombre lexicográficamente menor), tanto
   en la cima del stock como en la comparación incremental de las ventas.

Complejidad:
 - Coste Temporal: O((N + E) log N). El coste logarítmico viene del stock (push/update/priority); la parte de ventas es
                                     O(1) por evento.
 - Coste Espacial: O(N): una cola y un vector de ventas de tamaño N, más el diccionario de índices.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


struct Fruta {
    string nombre;
    int cantidad;

    // Más prioritaria = mayor cantidad; a igualdad, nombre lexicográficamente menor.
    bool operator>(const Fruta &o) const {
        if (cantidad != o.cantidad) return cantidad > o.cantidad;
        return nombre < o.nombre;
    }

    string toString() const {
        if (cantidad == 0) return "NO HAY";
        return nombre + " " + to_string(cantidad);
    }
};

bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) return false; // fin de la entrada

    map<string, int> indice;
    vector<Fruta> ventas(N + 1);
    Fruta masVentida = {};
    IndexPQ<Fruta, greater<> > stock(N + 1);

    for (int i = 1; i <= N; ++i) {
        string nombre;
        int cantidadInicial;
        cin >> nombre >> cantidadInicial;
        indice[nombre] = i;
        stock.push(i, {nombre, cantidadInicial});
    }

    int E;
    cin >> E;

    for (int j = 0; j < E; ++j) {
        char evento;
        cin >> evento;
        evento = toupper(evento);

        if (evento == 'Q') {
            // Consulta: fruta más abundante y fruta más vendida.
            cout << stock.top().prioridad.toString() << "; " << masVentida.toString() << "\n";
            continue;
        }

        string nombre;
        int cantidad;
        cin >> nombre >> cantidad;
        int i = indice[nombre];

        Fruta f = stock.priority(i);

        if (evento == 'C') {
            // Venta: se vende lo pedido o, si no hay suficiente, lo que quede.
            int vendidas = min(cantidad, f.cantidad);
            f.cantidad -= vendidas;
            ventas[i].cantidad += vendidas;
            ventas[i].nombre = nombre;
            if (ventas[i] > masVentida) masVentida = ventas[i];
        } else {
            // 'P' Reposición de stock.
            f.cantidad += cantidad;
        }

        stock.update(i, f);
    }

    cout << "---" << "\n";

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
