/*@ <authors>
 *
 * Jonathan Paul Moyonero Espinoza (F28)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

El problema se resuelve mediante Programación Dinámica, tratándolo como una variante de la Mochila con cantidades
limitadas. La capacidad de la mochila es la masa de pan total.

Definición de la etapa:
    dp[j] representa el beneficio máximo que se puede obtener utilizando exactamente j gramos de masa de pan.

Ecuación de recurrencia: Para cada tipo de chorizo i:

1.  Calculamos u(i) = chorizo_disponible / chorizo_receta
    (unidades máximas que se pueden fabricar)

2.  dp[j] = max( dp[j], dp[j - k * masa] + k * precio );  si k * masa <= j

Casos base:
    dp[0]=0; (con 0 masa de pan el beneficio es 0).
    dp[j]=0; (inicialmente para todo j>0).

Complejidad:

 - Coste Temporal: O(N*M*U), donde N es el número de tipos de chorizo, M la masa de pan total y U el número máximo de unidades por tipo.
 - Coste Espacial: O(M). Solo necesitamos un vector de tamaño M+1 para almacenar los resultados óptimos de la etapa actual.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    // leer los datos de la entrada

    int N, MASA;
    cin >> N >> MASA;

    if (!std::cin) return false; // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones

    vector<EntInf> dp(MASA + 1, 0);

    for (int i = 0; i < N; ++i) {
        int gramosDisponibles, chorizoNecesario, masaNecesaria, precio;
        cin >> gramosDisponibles >> chorizoNecesario >> masaNecesaria >> precio;

        int unidadesMaximas = gramosDisponibles / chorizoNecesario;

        for (int j = MASA; j >= 0; --j) {
            for (int k = 1; k <= unidadesMaximas && k * masaNecesaria <= j; ++k) {
                dp[j] = max(dp[j], dp[j - k * masaNecesaria] + k * precio);
            }
        }
    }

    // escribir la solución

    cout << dp[MASA] << "\n";

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
