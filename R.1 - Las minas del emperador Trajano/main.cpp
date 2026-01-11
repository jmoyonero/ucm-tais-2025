/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <limits>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

Para representar el problema usaremos un grafo dirigido donde las cámaras corresponden a los vertices y las galerías a
las aristas.

Como no tenemos una restricción en el recorrido de las galerías y estamos usando un grafo dirigido, crearemos una arista
en ambos sentidos para garantizar que podemos llegar a ambos vertices que une un camino.

Una vez creado el grafo, usaremos una variación de Dijkstra para encontrar un camino que une a palencia Jones con el
tesoro minimizando el tiempo que permanecemos bajo el agua. Eso quiere decir que NO buscamos el camino mínimo, si no, un
camino en el que sus galerías sean mínimas para aguantar la respiración lo minimo posible en cada tramo.

Además, debemos tener en cuenta lo siguiente:
    Si en la entrada de datos nos indican que Palencia Jones y el tesoro ya se encuentran en la misma cámara, no tenemos
    que aguantar la respiración bajo el agua con lo que escribimos un 0 y continuamos con el siguiente caso.

    Si tras aplicar Dijkstra detectamos que no hay camino que una a Palencia Jones con el tesoro escribimos IMPOSIBLE y
    pasamos al siguiente caso.

Complejidad:
 - Coste Temporal: O(A log V).
 - Coste Espacial: O(V).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template<typename Valor>
using Camino = deque<AristaDirigida<Valor> >;

template<typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const &g, int orig) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a: g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }

    Camino<Valor> camino(int v) const {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor> > ulti;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();

        // Esta es la modificación: NO queremos hallar el camino mínimo, si no, el camino donde la arista más grande sea
        // la de menor tamaño posible.
        int maximo = max(dist[v], a.valor());

        if (dist[w] > maximo) {
            dist[w] = maximo;
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int N, M;
    cin >> N >> M;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    DigrafoValorado<int> dv(N);

    for (int i = 0; i < M; ++i) {
        int inicio, fin, tiempo;
        cin >> inicio >> fin >> tiempo;
        dv.ponArista({inicio - 1, fin - 1, tiempo});
        dv.ponArista({fin - 1, inicio - 1, tiempo});
    }

    int palencia, tesoro;
    cin >> palencia >> tesoro;

    if (palencia == tesoro) {
        cout << "0\n";
        return true;
    }

    const Dijkstra<int> dij(dv, palencia - 1);

    if (!dij.hayCamino(tesoro - 1)) {
        cout << "IMPOSIBLE\n";
        return true;
    }

    // escribir la solución

    cout << dij.distancia(tesoro - 1) << "\n";

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
