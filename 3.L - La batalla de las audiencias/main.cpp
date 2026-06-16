/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "TreeSet_AVL.h"

using namespace std;

/*@ <answer>

Solución: el canal líder solo puede cambiar cuando llega una actualización, así que entre dos
actualizaciones consecutivas el líder es constante y dura (minuto_actual - minuto_anterior) minutos.

Mantenemos:
 - vector<long long> aud: la audiencia actual de cada canal (1..C);
 - Set<Canal, PorAudiencia>: todos los canales ordenados por (audiencia desc, id asc), de modo que
   begin() es siempre el canal más visto. Como nunca hay empate en el máximo, ese líder es único.

Recorrido temporal:
 - Empezamos con las audiencias del minuto 0 e insertamos los C canales en el Set.
 - Para cada actualización del minuto m: el tramo [anterior, m) lo lideró begin(); le sumamos
   (m - anterior) minutos. Después aplicamos cada cambio "c e" como borrado + reinserción en el Set
   (cambiar la clave de un canal equivale a sacarlo con su valor viejo y meterlo con el nuevo).
 - Tras la última actualización, el tramo final [anterior, D) lo lidera begin(); sumamos (D - anterior).

Los minutos por líder se guardan en un unordered_map<int,long long> (solo aparecen los que lideraron).
Al final ordenamos por minutos desc y a igualdad, por número de canal asc e imprimimos. Cierre "---".

Complejidad (C = canales, U = total de cambios en las actualizaciones, K = canales que lideraron):
 - Temporal: O((C + U) log C + K log K).
 - Espacial: O(C).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Canal {
    long long aud;
    int id;
};

struct PorAudiencia {
    bool operator()(const Canal &a, const Canal &b) const {
        if (a.aud != b.aud) return a.aud > b.aud; // más audiencia va antes
        return a.id < b.id; // a igualdad, menor número de canal antes
    }
};

bool resuelveCaso() {
    long long D;
    int C, N;
    if (!(cin >> D >> C >> N)) return false;

    vector<long long> aud(C + 1);
    Set<Canal, PorAudiencia> ranking; // todos los canales ordenados por audiencia

    for (int c = 1; c <= C; ++c) {
        cin >> aud[c];
        ranking.insert({aud[c], c});
    }

    unordered_map<int, long long> tiempo; // canal -> minutos que ha sido el más visto
    long long anterior = 0;

    for (int i = 0; i < N; ++i) {
        long long m;
        cin >> m;
        // el tramo [anterior, m) lo lidera el canal más visto actual
        tiempo[ranking.begin()->id] += m - anterior;

        int c;
        while (cin >> c && c != -1) {
            long long e;
            cin >> e;
            ranking.erase({aud[c], c}); // saca la entrada con el valor viejo
            aud[c] = e;
            ranking.insert({aud[c], c}); // reinserta con el nuevo
        }
        anterior = m;
    }

    // tramo final [anterior, D)
    tiempo[ranking.begin()->id] += D - anterior;

    // ordenar por minutos desc y a igualdad por número de canal asc
    vector<pair<long long, int> > res; // (minutos, canal)
    res.reserve(tiempo.size());
    for (auto const &p: tiempo) res.push_back({p.second, p.first});
    sort(res.begin(), res.end(), [](auto const &a, auto const &b) {
        if (a.first != b.first) return a.first > b.first; // más minutos antes
        return a.second < b.second; // a igualdad, menor canal antes
    });

    for (auto const &p: res)
        cout << p.second << " " << p.first << "\n";

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
