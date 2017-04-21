// Bibliotecas
#include <iostream>
#include "ArbinMod.h"	// Biblioteca modificada con funciones como leerArbol(int vacio)
using namespace std;


// Declaración funciones
int procesa(Arbin<int> arbol, bool &ok);


// Main
int main() {
	int casos = 0;

	cin >> casos;
	while (casos > 0) {
		Arbin<int> arbol = Arbin<int>();
		int res = 0;
		bool ok = true;

		// Entrada
		arbol = arbol.leerArbol(-1);	// O(n) siendo n el total de números de entrada

		// Procesamiento
		if(!arbol.esVacio())
			res = procesa(arbol, ok);	// O(n) siendo n el número de ramas del árbol
		
		// Salida
		if (ok) cout << "YES " << res << endl;
		else cout << "NO" << endl;

		casos--;
	}

	return 0;
}


// Definición funciones
int procesa(Arbin<int> arbol, bool &ok) {
	int res = 1;
	int dr = 0, iz = 0;

	if (!arbol.hijoDr().esVacio() && !arbol.hijoIz().esVacio()) {
		if ((arbol.hijoIz().raiz() - arbol.hijoDr().raiz()) < 2) ok = false;
	}

	if (arbol.hijoDr().esVacio() && arbol.hijoIz().esVacio()) {
		return res;
	}

	if (ok) {
		if (!arbol.hijoIz().esVacio()) {
			if (!(arbol.raiz() >= arbol.hijoIz().raiz() + 18)) ok = false;
			else {
				iz = procesa(arbol.hijoIz(), ok);
			}

			if (!arbol.hijoDr().esVacio()) {
				if (!(arbol.raiz() >= arbol.hijoDr().raiz() + 18)) ok = false;
				else {
					dr = procesa(arbol.hijoDr(), ok);
				}
			}

			if (iz > dr) res += iz;
			else res += dr;
		}
		else ok = false;
	}

	if (!ok) res = 0;

	return res;
}