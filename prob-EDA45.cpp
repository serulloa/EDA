// Sergio Ulloa López

/*
	-- Números afortunados --
	Dado un N ≥ 2 , se llaman números afortunados a los que resultan de ejecutar el siguiente proceso:
	se comienza generando un cola que contiene los números desde 1 hasta N en este orden; se elimina de la
	cola un número de cada 2 (es decir, los números 1, 3, 5, etc.); de la nueva cola se elimina un número de
	cada 3, etc. El proceso termina cuando se va a eliminar un número de cada m y el tamaño de la cola es
	menor que m. Los números que queden en la cola en este momento son los afortunados.

	-Entrada-
	La entrada consistirá en distintos casos de prueba, cada uno en una línea. Cada caso de prueba
	contiene el número con el que se calcularán los números afortunados. Ese número será siempre mayor o
	igual que 2 y no mayor que un millón. La entrada terminará con un 0, que marcará el final de la entrada
	y no generará salida.

	-Salida-
	Para cada caso de prueba se escribirá una línea que contendrá al principio el n de partida, seguido
	dos puntos, un espacio y todos los números afortunados en orden decreciente.
*/

// Bibliotecas
#include <iostream>
#include "Queue.h"
#include "Stack.h"
using namespace std;


// Constantes globales
const int MIN = 2;
const int MAX = 1000000;


// Declaración funciones
void procesa(Queue<int> &cola, int numeros);


// Main
int main() {
	int numeros = 1;
	Queue<int> cola;
	Stack<int> pila;

	while (numeros != 0) {
		cin >> numeros;

		if (numeros >= MIN && numeros <= MAX) {		// Comprobamos el rango de numeros
			for (int i = 1; i <= numeros; i++)		// Rellenamos la cola
				cola.push_back(i);
			procesa(cola, numeros);

			while (!cola.empty()) {
				pila.push(cola.front());
				cola.pop_front();
			}

			cout << numeros << ":";
			while (!pila.empty()) {
				cout << " " << pila.top();
				pila.pop();
			}
			cout << endl;
		}
	}

	return 0;
}


// Definición funciones
/*
	Función que se encarga de decidir qué
	números son afortunados dentro de la cola 
	de tamaño numeros
*/
void procesa(Queue<int> &cola, int numeros) {
	int m = 2;
	int i = 1;
	int size = cola.size();

	while (cola.size() >= m) {
		if (i % m == 1)
			cola.pop_front();
		else {
			cola.push_back(cola.front());
			cola.pop_front();
		}

		if (i == size) {
			i = 1;
			m++;
			size = cola.size();
		}
		else i++;
	}
	
	return;
}