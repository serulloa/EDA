//Sergio Ulloa López

#include <iostream>
using namespace std;

const int PRODMAX = 3;
const int SUPRMAX = 20;

void precio(int compras[SUPRMAX][SUPRMAX], int &sol, int &res, int k, int contador[], int nSupers, int nProds, bool &ok);
bool esValida(int pos, int contador[], int nProds);
bool esSolucion(int k, int nProds);

int main() {
	int casos, nSupers, nProds;
	int compras[SUPRMAX][SUPRMAX];
	int contador[SUPRMAX]; //lleva la cuenta de los productos en un mismo supermercado
	int sol = 0, res = 0;  //sol es la solucion final. res son soluciones parciales, donde se van sumando los precios
	bool ok = false;
	int k = 0;

	for (int i = 0; i < SUPRMAX; i++)
		contador[i] = 0;

	cin >> casos;

	while (casos > 0) {
		cin >> nSupers;
		cin >> nProds;

		if (nSupers < SUPRMAX && nProds < SUPRMAX) {
			for (int i = 0; i < nSupers; i++) {
				for (int j = 0; j < nProds; j++) {
					cin >> compras[i][j];
					sol += compras[i][j];
				}
			}

			if (nSupers == 0 || nProds == 0)
				cout << 0 << endl;
			else {
				precio(compras, sol, res, k, contador, nSupers, nProds, ok);

				if (ok)
					cout << sol << endl;
				else
					cout << "Sin solucion factible" << endl;
			}
		}

		casos--;
	}

	return 0;
}


//funcion principal vuelta atras
void precio(int compras[SUPRMAX][SUPRMAX], int &sol, int &res, int k, int contador[], int nSupers, int nProds, bool &ok) {
	for (int i = 0; i < nSupers; i++) {
		if (esValida(i, contador, nProds)) {
			res += compras[i][k];
			if(esSolucion(k, nProds)) {
				if (res < sol)
					sol = res;
				ok = true;
			}
			else {
				if (res < sol) {
					precio(compras, sol, res, k+1, contador, nSupers, nProds, ok);
				}
			}

			res = res - compras[i][k];
			contador[i] = contador[i] - 1;
		}
	}
}

//comprueba si el nodo actual (pos) cumple que no se hayan cogido más de 3 productos de ese supermercado
bool esValida(int pos, int contador[], int nProds) {
	bool ok = false;
	
	if (contador[pos] < PRODMAX) {
		ok = true;
		contador[pos]++;
	}
	return ok;
}

//comprueba que k es el ultimo producto (ultima posicion) de la lista de la compra
bool esSolucion(int k, int nProds) {
	return k == nProds - 1;
}
