/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// propios o los de las estructuras de datos de clase


/*@ <answer>

 Problema: Subsecuencia Común Más Larga (LCS)

 Recurrencia:
 dp[i][j] = 1 + dp[i-1][j-1]      (Si A[i-1] == B[j-1])
 dp[i][j] = max(dp[i-1][j], dp[i][j-1]) (Si son distintos)

 Complejidad:
 - Coste Temporal: O(N * M), donde N y M son las longitudes de las listas de canciones.
 - Coste Espacial: O(N * M). Necesario para reconstruir la solución.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// Función auxiliar para leer una línea y convertirla en vector de palabras
vector<string> leerLista() {
    string linea, palabra;
    vector<string> lista;
    if (getline(cin, linea)) {
        stringstream ss(linea);
        while (ss >> palabra) {
            lista.push_back(palabra);
        }
    }
    return lista;
}

bool resuelveCaso() {
    // leer los datos de la entrada

    // Lectura de la primera lista
    // Usamos peek para ver si hay fin de archivo o líneas vacías
    if (cin.peek() == EOF) return false;

    vector<string> A = leerLista();
    // Si la lectura falló o estaba vacía (y era EOF), terminamos
    if (A.empty() && cin.eof()) return false;

    vector<string> B = leerLista();

    int N = A.size();
    int M = B.size();

    // resolver el caso posiblemente llamando a otras funciones

    // Programación dinámica: dp

    vector<vector<int> > dp(N + 1, vector<int>(M + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstrucción
    vector<string> solucion;
    int i = N, j = M;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            solucion.push_back(A[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(solucion.begin(), solucion.end());

    for (const string &s: solucion) cout << s << " ";

    cout << "\n";

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
