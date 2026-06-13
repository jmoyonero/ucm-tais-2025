/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

/*@ <answer>

Solución: Reparto de escaños por el método D'Hondt.

Repartimos los N escaños uno a uno. En cada paso el escaño va a la candidatura con mayor coeficiente
c_k = votos_k / (1 + escaños_k); a igual coeficiente gana la de más votos y si persiste el empate, la
de menor índice. Para elegir rápido la mejor en cada paso usamos una priority_queue de máximos: en la
cima está siempre la candidatura más prioritaria. Tras darle un escaño, la reinsertamos con su
coeficiente ya actualizado.

Para comparar coeficientes sin usar redondeos convertimos la división en multiplicación:
votos_a/(1+e_a) > votos_b/(1+e_b) equivale a votos_a*(1+e_b) > votos_b*(1+e_a).

Complejidad (C = candidaturas, N = escaños):
 - Temporal: O((C + N) log C) por construir la cola y los N repartos.
 - Espacial: O(C) por las candidaturas en la priority_queue.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Candidatura {
    int indice;
    long long votos;
    long long escanos;

    bool operator<(const Candidatura &otra) const {
        long long a = votos * (1 + otra.escanos);
        long long b = otra.votos * (1 + escanos);
        if (a != b) return a < b;
        if (votos != otra.votos) return votos < otra.votos;
        return indice > otra.indice;
    }
};

bool resuelveCaso() {
    int C, N;
    cin >> C >> N;
    if (C == 0 && N == 0) return false;

    priority_queue<Candidatura> cola;
    for (int i = 0; i < C; ++i) {
        long long votos;
        cin >> votos;
        cola.push({i, votos, 0});
    }

    // Repartimos los N escaños, uno a uno, al de mayor coeficiente.
    vector<int> escanos(C, 0);
    for (int s = 0; s < N; ++s) {
        Candidatura mejor = cola.top();
        cola.pop();
        ++escanos[mejor.indice];
        ++mejor.escanos;
        cola.push(mejor);
    }

    for (int i = 0; i < C; ++i)
        cout << escanos[i] << (i + 1 < C ? ' ' : '\n');

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
