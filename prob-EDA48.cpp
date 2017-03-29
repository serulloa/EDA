// Sergio Ulloa L�pez

// Bibliotecas
#include <iostream>
#include "List.h"
using namespace std;


// Declaraci�n funciones
void procesa(List<int> &res, List<int> lista1, List<int> lista2);


// Main
int main() {
	List<int> lista1;
	List<int> lista2;
	List<int> res;
	int casos, num;
	char c;

	cin >> casos;
	cin.get(c);	// Cogemos el salto de l�nea correspondiente a los casos

	while (casos > 0) {
		lista1 = List<int>();
		lista2 = List<int>();
		res = List<int>();

		cin.get(c);
		while (c != '\n') {	// O(n)
			cin.putback(c);	// Devolvemos el car�cter en caso de que no sea salto
			cin >> num;
			lista1.push_back(num);
			cin.get(c);
		}
		cin.get(c);
		while (c != '\n') {	// O(n)
			cin.putback(c);
			cin >> num;
			lista2.push_back(num);
			cin.get(c);
		}

		procesa(res, lista1, lista2); // O(n+m) = O(n) 

		for (int i = 0; i < res.size(); i++)	// O(n)
			cout << res.at(i) << " ";
		cout << endl;

		casos--;
	}

	return 0;
}


// Definici�n funciones
void procesa(List<int> &res, List<int> lista1, List<int> lista2) {
	List<int>::ConstIterator it1 = lista1.cbegin(), it2 = lista2.cbegin();

	for (int i = 0; i < (lista1.size() + lista2.size()); i++) {
		if (it1 == lista1.cend()) {
			res.push_back(it2.elem());
			it2.next();
		}
		else if (it2 == lista2.cend()) {
			res.push_back(it1.elem());
			it1.next();
		}
		else {
			if (it1.elem() < it2.elem()) {
				res.push_back(it1.elem());
				it1.next();
			}
			else {
				res.push_back(it2.elem());
				it2.next();
			}
		}
	}

	return;
}