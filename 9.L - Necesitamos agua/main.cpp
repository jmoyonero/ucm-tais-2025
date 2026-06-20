/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include "GrafoValorado.h"

using namespace std;

/*@ <answer>

Combinación de CAMINOS MÍNIMOS (Dijkstra) y un reparto VORAZ con restricción de mitad y mitad.

El nodo 1 es la planta norte y el nodo N la sur; los N-2 nodos restantes son pueblos. Cada camión
sale de su planta, sirve a un pueblo y vuelve, así que servir el pueblo v desde una planta cuesta
2 * (camino mínimo planta -> v). Hay que asignar exactamente (N-2)/2 pueblos al norte y el resto al
sur minimizando el coste total.

Estrategia:
1. Dijkstra desde el nodo 0 (norte) -> dN[v], y desde el nodo N-1 (sur) -> dS[v].
2. Para repartir con la restricción de mitad y mitad: partimos de "todos los pueblos al sur"
   (coste base = suma de dS) y movemos al norte los (N-2)/2 pueblos con menor dN[v]-dS[v], es decir,
   los de mayor ahorro al cambiarlos de planta.
3. El coste de ida y vuelta es el doble de la suma de caminos de ida: respuesta = 2 * suma.

¿Por qué es óptimo el reparto?
La única restricción es el número de pueblos por planta (k = (N-2)/2 a cada una). El coste es la
suma independiente de los costes de cada pueblo, así que minimizar = elegir, entre todas las formas
de marcar k pueblos como "norte", la que minimiza la suma. Como mover el pueblo v al norte cambia el
coste en (dN[v]-dS[v]), elegir los k menores de esos incrementos es óptimo (argumento de
intercambio: cambiar uno elegido por otro no elegido con menor incremento nunca empeora).

Complejidad:
 - Temporal: O(M log N) por los dos Dijkstra, más O(N log N) por la ordenación.
 - Espacial: O(N + M).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// Caminos mínimos desde 'origen' con Dijkstra sobre el grafo valorado.
vector<long long> dijkstra(const GrafoValorado<int> &g, int origen) {
    int n = g.V();
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<> > pq;
    dist[origen] = 0;
    pq.push({0, origen});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue; // entrada obsoleta
        for (const auto &arista: g.ady(u)) {
            int v = arista.otro(u);
            long long w = arista.valor();
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    if (!std::cin) return false; // fin de la entrada

    GrafoValorado<int> carretera(N);
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        carretera.ponArista({a - 1, b - 1, c});
    }

    // caminos mínimos desde la planta norte (0) y la sur (N-1)
    vector<long long> dN = dijkstra(carretera, 0);
    vector<long long> dS = dijkstra(carretera, N - 1);

    // partimos de "todos los pueblos al sur" y calculamos el incremento de llevarlos al norte
    long long base = 0;
    vector<long long> delta;
    delta.reserve(N - 2);
    for (int v = 1; v <= N - 2; ++v) {
        base += dS[v];
        delta.push_back(dN[v] - dS[v]);
    }
    sort(delta.begin(), delta.end());

    // movemos al norte los (N-2)/2 pueblos de menor incremento
    int k = (N - 2) / 2;
    long long suma = base;
    for (int i = 0; i < k; ++i) suma += delta[i];

    // el coste es de ida y vuelta -> el doble de la suma de caminos de ida
    cout << 2 * suma << "\n";

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
