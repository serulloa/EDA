// Sergio Ulloa López

#include <iostream>
#include <cmath>
using namespace std;


// Clases
class Complejo
{
public:
	float real;
	float imag;
	
	Complejo(float a, float b) {	// Constructor con dos argumentos
		real = a;
		imag = b;
	}

	float mod() {					// Función que calcula el módulo del número complejo
		return sqrt(pow(real, 2) + pow(imag, 2));
	}	
};


// Sobrecarga de operadores
Complejo operator +(Complejo a, Complejo b) {
	float real, imag;

	real = a.real + b.real;
	imag = a.imag + b.imag;

	return Complejo(real, imag);
}

Complejo operator *(Complejo a, Complejo b) {
	float real, imag;

	real = (a.real * b.real - a.imag * b.imag);
	imag = (a.real * b.imag + b.real * a.imag);

	return Complejo(real, imag);
}


// Definición funciones
bool mandelbrot(float real, float imag, int i);


// Main
int main() {
	int casos = 0;
	int iteraciones;
	float real, imag;
	bool ok = false;
	cin >> casos;

	while (casos > 0) {
		while (!ok) {
			cin >> real;
			cin >> imag;

			if ((real >= -2 && real <= 2) && (imag >= -2 && imag <= 2)) ok = true;
			else cout << "Los numeros deben estar entre -2 y 2" << endl;
		}

		ok = false;
		while (!ok) {
			cin >> iteraciones;
			if (iteraciones >= 100 && iteraciones <= 500) ok = true;
			else cout << "El numero de iteraciones debe estar entre 100 y 500" << endl;
		}

		ok = mandelbrot(real, imag, iteraciones);

		if (ok) cout << "NO";
		else cout << "SI";
		cout << endl;

		ok = false;
		casos--;
	}

	return 0;
}


bool mandelbrot(float real, float imag, int i) {
	bool ok = false;
	Complejo c = Complejo(real, imag);
	Complejo anterior = Complejo(0, 0);
	float modulo = 0;

	while (i > 0 && !ok) {
		anterior = (anterior * anterior) + c;
		modulo = anterior.mod();

		if (modulo > 2) ok = true;

		i--;
	}

	return ok;
}