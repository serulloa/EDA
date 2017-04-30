// Bibliotecas
#include <iostream>
#include "QueueMod.h"
using namespace std;

// Declaración funciones
int entradaDatos(Queue<int> &cola);	// O(n) siendo n el tamaño de la nueva cola
void salidaDatos(Queue<int> cola);	// O(n) siendo n el tamaño de la cola

// Main
int main() {
	int casos = 0, k = 0;

	cin >> casos;

	while (casos > 0) {
		Queue<int> cola = Queue<int>();

		k = entradaDatos(cola);
		salidaDatos(cola);

		if (!cola.empty() && k >= 2)
			cola.invierte(k);

		salidaDatos(cola);

		casos--;
	}

	return 0;
}

// Definición funciones
int entradaDatos(Queue<int> &cola) {
	int n = 0;

	cin >> n;

	while (n != -1) {
		cola.push_back(n);
		cin >> n;
	}

	cin >> n;

	return n;
}

void salidaDatos(Queue<int> cola) {
	cout << "{";

	while (!cola.empty()) {
		cout << cola.front();
		cola.pop_front();

		if (!cola.empty()) cout << ",";
	}

	cout << "}" << endl;

	return;
}