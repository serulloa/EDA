// Sergio Ulloa López

// Bibliotecas
#include <iostream>
#include "Queue.h"
using namespace std;


// Constantes globales
const int MAX = 1000000;


// Declaración funciones
int procesa(Queue<int> &cola, int alumnos, int m);


// Main
int main() {
	int alumnos = 1, m = 1;
	Queue<int> cola;

	while (alumnos != 0 || m != 0) {
		cin >> alumnos;
		cin >> m;

		if ((alumnos > 0 && m > 0) && (alumnos < MAX && m < MAX)) {
			for (int i = 1; i <= alumnos; i++)
				cola.push_back(i);

			cout << procesa(cola, alumnos, m) << endl;
		}
	}

	return 0;
}


// Definición funciones
int procesa(Queue<int> &cola, int alumnos, int m) {
	int res = 0;
	int i = 1;

	while (cola.size() > 1) {
		if (i % m == 0) cola.pop_front();
		else {
			res = cola.front();
			cola.pop_front();
			cola.push_back(res);
		}

		i++;
	}

	res = cola.front();
	cola.pop_front();

	return res;
}