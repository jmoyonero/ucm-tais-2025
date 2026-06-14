/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "TreeSet_AVL.h"

using namespace std;

/*@ <answer>

Solución: Mantener el podio de los 3 temas más citados con actualizaciones dinámicas.

Cada tema tiene un nº de citas y la marca temporal de su último evento C (para desempatar). El podio se
ordena por más citas y a igualdad, por evento C más reciente.

Usamos dos estructuras coordinadas:
 - unordered_map<string,Tema>: estado actual (citas, últimoC) de cada tema;
 - TreeSet<Tema> ordenado por (citas desc, últimoC desc): sus 3 primeros elementos
   (begin()..) son el podio, porque el comparador deja "el mejor" como el menor del árbol.

Para actualizar un tema usamos borrado + reinserción en el Set (cambiar su clave equivale a sacarlo y
volverlo a meter con la nueva).

Eventos:
 - "C tema n": con datos[tema] (lo crea si es nuevo). Si ya tenía citas lo borramos del Set, sumamos n,
   fijamos últimoC al índice del evento y lo reinsertamos.
 - "E tema n": lo buscamos con datos.find(tema) (consulta segura: si no existe devuelve end() y no creamos
   un tema fantasma). Lo borramos del Set, restamos n y lo reinsertamos solo si le quedan citas (>0); con
   0 no reaparece. E no cambia últimoC.
 - "TC": recorremos el Set desde begin() y mostramos hasta los 3 primeros.
Al terminar el caso escribimos "---".

Como (citas, últimoC) es único por tema (cada evento C tiene un índice distinto), el orden del Set es
total y no hacen falta más criterios de desempate. El Set solo contiene temas con citas > 0.

Complejidad (n = eventos, D = temas distintos):
 - Temporal: O(n log D).
 - Espacial: O(D).

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Tema {
    long long citas;
    int ultimoC; // índice del último evento C (marca temporal para desempate)
    string nombre;
};

struct PorPodio {
    bool operator()(const Tema &a, const Tema &b) const {
        if (a.citas != b.citas) return a.citas > b.citas; // más citas va antes
        return a.ultimoC > b.ultimoC; // a igualdad, más reciente va antes
    }
};

bool resuelveCaso() {
    int n;
    if (!(cin >> n)) return false;

    unordered_map<string, Tema> datos; // nombre -> estado actual
    Set<Tema, PorPodio> ranking; // temas con citas > 0, ordenados por podio (AVL)

    for (int i = 0; i < n; ++i) {
        string tipo;
        cin >> tipo;

        if (tipo == "TC") {
            int puesto = 0;
            for (auto it = ranking.begin(); it != ranking.end() && puesto < 3; ++it)
                cout << ++puesto << " " << it->nombre << "\n";
        } else {
            string tema;
            long long num;
            cin >> tema >> num;

            if (tipo == "C") {
                Tema &d = datos[tema]; // crea {0,0,""} si es nuevo
                if (d.citas > 0) ranking.erase(d); // quita la entrada previa
                d.nombre = tema;
                d.citas += num;
                d.ultimoC = i;
                ranking.insert(d);
            } else {
                // "E"
                auto it = datos.find(tema);
                if (it == datos.end()) continue;
                Tema &d = it->second;
                if (d.citas > 0) ranking.erase(d);
                d.citas -= num;
                if (d.citas > 0) ranking.insert(d); // si llega a 0, no reaparece
            }
        }
    }

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
