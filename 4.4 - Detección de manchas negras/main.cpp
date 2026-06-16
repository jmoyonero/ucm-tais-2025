/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include "Grafo.h"

using namespace std;

/*@ <answer>

Modelamos el bitmap como un grafo no dirigido: cada píxel negro '#' es un vértice y ponemos una arista
entre dos píxeles negros adyacentes en horizontal o vertical. Cada mancha es entonces una componente
conexa, así que el problema se reduce a contar componentes y hallar el tamaño de la mayor.

Identificamos el píxel (f, c) con el vértice f*C + c del grafo (que tiene F*C vértices). Solo añadimos
aristas entre píxeles negros vecinos; los píxeles blancos quedan como vértices aislados que nunca
visitamos (solo arrancamos el recorrido desde píxeles negros), por lo que no cuentan como manchas.

El recorrido es un DFS ITERATIVO con pila explícita. No usamos la versión recursiva porque una mancha
puede tener hasta F*C = 10^6 píxeles y una recursión de esa profundidad desbordaría la pila del sistema.

Complejidad por caso (F filas, C columnas, V = F*C vértices):
 - Temporal: O(V) = O(F * C), cada píxel y cada arista se visitan una vez.
 - Espacial: O(V) por el grafo y los vectores auxiliares.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Manchas {
private:
    vector<bool> visit;

    // DFS iterativo desde s; devuelve el tamaño de la componente.
    int tamComponente(Grafo const &g, int s) {
        int tam = 0;
        stack<int> pila;
        visit[s] = true;
        pila.push(s);
        while (!pila.empty()) {
            int v = pila.top();
            pila.pop();
            ++tam;
            for (int w: g.ady(v))
                if (!visit[w]) {
                    visit[w] = true;
                    pila.push(w);
                }
        }
        return tam;
    }

public:
    Manchas(Grafo const &g) : visit(g.V(), false) {
    }

    // negro[v] indica si el vértice v es un píxel negro; solo esos forman manchas.
    pair<int, int> cuenta(Grafo const &g, vector<bool> const &negro) {
        int manchas = 0, mayor = 0;
        for (int v = 0; v < g.V(); ++v)
            if (negro[v] && !visit[v]) {
                ++manchas;
                mayor = max(mayor, tamComponente(g, v));
            }
        return {manchas, mayor};
    }
};

bool resuelveCaso() {
    int F, C;
    if (!(cin >> F >> C)) return false; // fin de la entrada

    vector<string> m(F);
    for (int i = 0; i < F; ++i)
        cin >> m[i]; // cada fila son C caracteres sin espacios

    Grafo g(F * C);
    vector<bool> negro(F * C, false);
    for (int f = 0; f < F; ++f)
        for (int c = 0; c < C; ++c)
            if (m[f][c] == '#') {
                int id = f * C + c;
                negro[id] = true;
                // unimos con el vecino derecho y el de abajo si también son negros
                // (basta esos dos sentidos: ponArista añade la arista en ambas direcciones)
                if (c + 1 < C && m[f][c + 1] == '#') g.ponArista(id, id + 1);
                if (f + 1 < F && m[f + 1][c] == '#') g.ponArista(id, id + C);
            }

    auto res = Manchas(g).cuenta(g, negro);
    cout << res.first << " " << res.second << "\n";
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
