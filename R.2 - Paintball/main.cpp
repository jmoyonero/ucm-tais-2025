/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "Grafo.h"

/*@ <answer>

Para representar el problema usaremos un grafo donde los amigos corresponden a los vertices y las rivalidades a las
aristas.

El objetivo es determinar si el grafo es bipartito. Para lo cual, realizaremos un recorrido en profundidad en el cual
iremos asignando un color a los amigos (vertices) alternandolo con sus adyacentes.

En el momento en el que detectemos que un vertice y su adyacente tienen el mismo color el grafo deja de ser bipartito y
escribiremos un NO.

Complejidad:
 - Coste Temporal: O(V + A). Donde V es el número de vértices y A el número de aristas.
 - Coste Espacial: O(V + A).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Bipartito {
private:
    std::vector<bool> visit;
    std::vector<int> ant;
    std::vector<int> colores;
    bool bipartito = true;

    void dfs(Grafo const &G, int v, int color) {

        visit[v] = true;
        colores[v] = color;

        for (int w: G.ady(v)) {
            if (!bipartito) return;
            if (!visit[w]) {
                ant[w] = v;
                dfs(G, w, 1 - color);
            } else if (colores[w] == colores[v]) bipartito = false;
        }
    }

public:
    Bipartito(Grafo const &g) : visit(g.V(), false), ant(g.V()), colores(g.V(), -1) {
        for (int i = 0; i < g.V(); ++i)
            if (!visit[i]) {
                dfs(g, i, 0);
            }
    }

    bool esBipartito() const {
        return bipartito;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada

    int A, R;
    cin >> A >> R;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    Grafo g(A);

    for (int i = 0; i < R; ++i) {
        int amigoA, amigoB;
        cin >> amigoA >> amigoB;
        g.ponArista(amigoA - 1, amigoB - 1);
    }

    const Bipartito dfs(g);

    // escribir la solución

    if (dfs.esBipartito())
        cout << "SI\n";
    else
        cout << "NO\n";


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
