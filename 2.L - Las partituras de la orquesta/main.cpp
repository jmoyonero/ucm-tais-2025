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

Solución: Minimizar el atril más concurrido al repartir p partituras.

Si un instrumento con m músicos recibe s partituras (atriles), su atril más lleno tiene techo(m/s)
músicos. Hay que repartir p partituras (al menos una por instrumento) minimizando el máximo de
techo(m/s) entre todos los instrumentos.

Priority_queue de máximos: empezamos dando 1 partitura a cada instrumento (n partituras) y
repartimos las p-n restantes una a una, dándole cada vez una partitura más al instrumento cuyo atril
esté en ese momento más concurrido (la cima del montículo) eso reduce su techo(m/s). Al terminar, la
cima indica el atril más concurrido, que es la respuesta.

Complejidad (n = instrumentos, p = partituras):
 - Temporal: O(p log n) por los repartos sobre el montículo.
 - Espacial: O(n) por los instrumentos en la priority_queue.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Instrumento {
    int musicos;
    int particiones;

    // Músicos en el atril más lleno: techo(musicos / particiones).
    int atril() const {
        return (musicos + particiones - 1) / particiones;
    }

    // Más prioritario = atril más concurrido (max-heap por atril()).
    bool operator<(const Instrumento &otro) const {
        return atril() < otro.atril();
    }
};

bool resuelveCaso() {
    int p, n;
    if (!(cin >> p >> n)) return false;

    priority_queue<Instrumento> cola;
    for (int i = 0; i < n; ++i) {
        int musicos;
        cin >> musicos;
        cola.push({musicos, 1}); // al menos una partitura por instrumento
    }

    // Repartimos las p - n partituras restantes al atril más concurrido cada vez.
    for (int restantes = p - n; restantes > 0; --restantes) {
        Instrumento peor = cola.top();
        cola.pop();
        ++peor.particiones;
        cola.push(peor);
    }

    cout << cola.top().atril() << "\n";

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
