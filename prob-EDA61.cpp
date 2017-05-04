// Bibliotecas
#include <iostream>
#include "QueueMod.h"
using namespace std;

// Declaración funciones
int entradaDatos(Queue<int> &cola, Queue<int> &colegas);	// O(n+m) siendo n el tamaño de cola y m el tamaño de colegas.
void salidaDatos(Queue<int> cola);	// O(n) siendo n el tamaño de cola.

// Main
int main() {
  int casos = 0;
  int pringao = 0;
  Queue<int> cola, colegas;

  cin >> casos;

  while (casos > 0) {
	cola = Queue<int>();
	pringao = entradaDatos(cola, colegas);

	salidaDatos(cola);

	cola.colar(colegas, pringao);

	salidaDatos(cola);

	casos--;
  }

  return 0;
}

// Definición funciones
int entradaDatos(Queue<int> &cola, Queue<int> &colegas) {
  int pringao = 0;
  int n;

  colegas.push_back(0);
  colegas.pop_front();

  cin >> n;
  while (n != -1) {
    cola.push_back(n);
    cin >> n;
  }

  cin >> pringao;

  cin >> n;
  while (n != -1) {
    colegas.push_back(n);
    cin >> n;
  }

  return pringao;
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
