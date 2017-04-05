/* Bibliotecas */
#include <iostream>
#include "Arbin.h"
using namespace std;


/* Declaración funciones */
int procesa(Arbin<int> arbol, int &cont, int nivel);


/* Main */
int main() {
	int casos, suma, cont, nivel;
	Arbin<int> arbol;

	cin >> casos;
	cin.get();
	while (casos > 0) {
		arbol = Arbin<int>();
		suma = 0; cont = 0; nivel = 0;
		arbol = arbol.leerArbol(-1); //O(n) siendo n la lista de numeros introducidos en consola

		if (!arbol.esVacio()) procesa(arbol, cont, nivel); //O(n) siendo n el numero de nodos del arbol
		
		cout << cont << endl;

		casos--;
	}

	return 0;
}


/* Definición funciones */
int procesa(Arbin<int> arbol, int &cont, int nivel) {	// Calcula el caudal que SALE de cada nodo, por eso,
														// es necesario tener en cuenta el nivel actual, ya
	nivel++;											// que el que sale de la raíz del árbol es irrelevante

	int ret = 0;

	if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) ret = 1;
	else {
		if (!arbol.hijoIz().esVacio()) {
			ret += procesa(arbol.hijoIz(), cont, nivel);
		}
		if (!arbol.hijoDr().esVacio()) {
			ret += procesa(arbol.hijoDr(), cont, nivel);
		}

		ret -= arbol.raiz(); // Se resta el nivel del embalse al caudal actual
	}

	if (ret >= 3 && nivel > 1) cont++;
	if (ret < 0) ret = 0;
	return ret;
}