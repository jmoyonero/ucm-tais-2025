/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

// propios o los de las estructuras de datos de clase


/*@ <answer>

 El problema se resuelve mediante una estrategia voraz (greedy) equivalente al Algoritmo de Huffman.
 Para minimizar el número total de gorras, en cada paso debemos seleccionar los dos equipos con la menor cantidad de
 seguidores para que se enfrenten entre sí.

 Lógica del algoritmo:

 Utilizamos una cola de prioridad de mínimos para almacenar el número de seguidores de cada equipo.
 Mientras haya más de un equipo en la cola:
 - Extraemos los dos valores mínimos, a y b.
 - El coste del partido es a+b.
 - Sumamos este coste al total de gorras necesarias.
 - Insertamos el nuevo equipo (con a+b seguidores) de nuevo en la cola.

 Complejidad:
 - Temporal: O(N log N). Realizamos N inserciones y aproximadamente 2N extracciones en la cola de prioridad, cada una
   con un coste de O(log N).
 - Espacial: O(N) para almacenar a los seguidores de los N equipos en la priority_queue.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada

    int N;
    cin >> N;

    if (N == 0) return false; // fin de la entrada

    priority_queue<long long, vector<long long>, greater<> > pq;

    for (int i = 0; i < N; ++i) {
        int seguidores;
        cin >> seguidores;
        pq.push(seguidores);
    }

    // resolver el caso posiblemente llamando a otras funciones

    long long necesarias = 0;

    while (pq.size() > 1) {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();

        long long actuales = a + b;

        necesarias += actuales;
        pq.push(actuales);
    }

    // escribir la solución

    cout << necesarias << "\n";

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
