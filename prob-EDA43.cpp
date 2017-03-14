// Bibliotecas
#include <iostream>
#include "Stack.h"
using namespace std;


// Constantes globales
const int MAX = 1000000000;


// Main
int main() {
	int numero = 0;
	int suma;
	Stack<int> pila;
	bool vacia;

	while (numero != -1) {
		cin >> numero;

		if (numero < 0) {
			if (numero < -1)
				cout << "El numero debe ser 0 o positivo" << endl;
		}
		else if (numero > MAX || cin.fail()) {
			cin.clear();
			cout << "El numero debe ser menor que 10^9" << endl;
		}
		else if (numero == 0) cout << "0 = 0" << endl;
		else {
			while (numero != 0) {
				pila.push(numero % 10);
				numero = numero / 10;
			}

			if (pila.empty()) vacia = true;
			else vacia = false;
			suma = 0;
			while (!vacia) {
				numero = pila.top();
				suma += numero;
				pila.pop();
				vacia = pila.empty();

				cout << numero << " ";
				if (!vacia) cout << "+ ";
			}
			cout << "= " << suma << endl;
		}

		cin.clear();
	}

	return 0;
}