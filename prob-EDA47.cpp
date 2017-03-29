// Sergio Ulloa López

// Bibliotecas
#include <iostream>
#include <string.h>
#include "List.h"
using namespace std;


// Declaración funciones
int procesa(List<int> &lista);


// Main
int main() {
	List<int> lista;
	int casos = 1;
	int num = 0;
	char aux = '0';

	cin >> casos;
	cin.get(aux);
	while (casos > 0) {
		cin.get(aux);
		lista = List<int>();

		while (aux != '\n') {	//O(n)
			cin.putback(aux);
			cin >> num;
			lista.push_back(num);
			cin.get(aux);
		}

		num = procesa(lista);

		cout << num << ": ";
		List<int>::ConstIterator it = lista.cbegin();
		while (it != lista.cend()) {	//O(n)
			cout << it.elem() << " ";
			it.next();
		}
		cout << endl;

		casos--;
	}

	return 0;
}


// Definición funciones
int procesa(List<int> &lista) {
	List<int>::Iterator it = lista.begin();
	int suma = 0;
	int res = 0;

	for (int i = 0; i < lista.size(); i++) {	//O(n)
		bool ok = (it.elem() == suma);

		if (ok) {
			lista.insert(it.elem(), it);
			res++;
			i++;
		}

		suma += it.elem();
		it.next();
	}

	return res;
}
