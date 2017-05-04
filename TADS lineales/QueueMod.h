/**
@file Cola.h

Implementaci�n del TAD Cola utilizando una
lista enlazada de nodos.

Estructura de Datos y Algoritmos
Facultad de Inform�tica
Universidad Complutense de Madrid

(c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __LINKED_LIST_QUEUE_H
#define __LINKED_LIST_QUEUE_H

#include "Exceptions.h"

/**
Implementaci�n del TAD Cola utilizando una lista enlazada.

Las operaciones son:

- EmptyQueue: -> Queue. Generadora implementada en el
constructor sin par�metros.
- push_back: Queue, Elem -> Queue. Generadora
- pop_front: Queue - -> Queue. Modificadora parcial.
- front: Queue - -> Elem. Observadora parcial.
- empty: Queue -> Bool. Observadora.
- size: Queue -> Entero. Observadora.

@author Marco Antonio G�mez Mart�n
*/
template <class T>
class Queue {
public:

	/** Constructor; operacion EmptyQueue */
	Queue() : _prim(NULL), _ult(NULL), _numElems(0) {
	}

	/** Destructor; elimina la lista enlazada. */
	~Queue() {
		libera();
		_prim = _ult = NULL;
	}

	/**
	A�ade un elemento en la parte trasera de la cola.
	Operaci�n generadora.

	@param elem Elemento a a�adir.
	*/
	void push_back(const T &elem) {
		Nodo *nuevo = new Nodo(elem, NULL);

		if (_ult != NULL)
			_ult->_sig = nuevo;
		_ult = nuevo;
		// Si la cola estaba vac�a, el primer elemento
		// es el que acabamos de a�adir
		if (_prim == NULL)
			_prim = nuevo;
		_numElems++;
	}

	/**
	Elimina el primer elemento de la cola.
	Operaci�n modificadora parcial, que falla si
	la cola est� vac�a.

	pop_front(Push_back(elem, EmptyQueue)) = EmptyQueue
	pop_front(Push_back(elem, xs)) = push_back(elem, pop_front(xs)) si !empty(xs)
	error: pop_front(EmptyQueue)
	*/
	void pop_front() {
		if (empty())
			throw EmptyQueueException();
		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		delete aBorrar;
		--_numElems;
		// Si la cola se qued� vac�a, no hay
		// �ltimo
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	Devuelve el primer elemento de la cola. Operaci�n
	observadora parcial, que falla si la cola est� vac�a.

	front(Push_back(elem, EmptyQueue)) = elem
	front(Push_back(elem, xs)) = primero(xs) si !empty(xs)
	error: front(EmptyQueue)

	@return El primer elemento de la cola.
	*/
	const T &front() const {
		if (empty())
			throw EmptyQueueException();
		return _prim->_elem;
	}

	/**
	Devuelve true si la cola no tiene ning�n elemento.

	empty(EmptyQueue) = true
	empty(Push_back(elem, p)) = false

	@return true si la cola no tiene ning�n elemento.
	*/
	bool empty() const {
		return _prim == NULL;
	}

	/**
	Devuelve el n�mero de elementos que hay en la
	cola.
	size(EmptyQueue) = 0
	size(Push_back(elem, p)) = 1 + size(p)

	@return N�mero de elementos.
	*/
	int size() const {
		return _numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Queue(const Queue<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Queue<T> &operator=(const Queue<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Queue<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Queue<T> &rhs) const {
		return !(*this == rhs);
	}

	/*
	* Parte de funciones propias
	*
	* La función invierte(int n) consiste en conservar, en todo momento, el primer elemento de la cola y
	* el primer elemento de la cola original, esté invertido o no. Por ejemplo, si tenemos una cola
	* {1, 2, 3, 4, 5}, en la primera iteración quedará tal que {2, 1, 3, 4, 5} y, por lo tanto, la
	* variable primerNodo será igual a 2 y nodo1 = 1.
	* Así, el funcionamiento quedará reducido a cambiar la posición de nodo1 y nodo2, luego hacer que
	* nodo2 pase a ser el primer elemento de la cola y, por último, tomar como nuevo nodo2 el nodo siguiente
	* a nodo1.
	*/
	void invierte(int n) {	// O(n-1) siendo n el n�mero de elementos a invertir
		if(_numElems > 1) {
			Nodo *primerNodo = _prim;
			Nodo *nodo1 = _prim;
			Nodo *nodo2 = _prim->_sig;

			if (n > _numElems) n = _numElems;

			for (int i = 0; i < n-1; i++) {
				if (nodo2->_sig != NULL) {
					nodo1->_sig = nodo2->_sig;
					nodo2->_sig = primerNodo;

					primerNodo = nodo2;
					nodo2 = nodo1->_sig;
				}
				else {
					nodo1->_sig = NULL;
					nodo2->_sig = primerNodo;
					primerNodo = nodo2;
					_ult = nodo1;
				}
			}

			_prim = primerNodo;
		}
	}

	/*
	* La función colar() trata de buscar el nodo correspondiente al "pringao" y guarda el puntero en
	* nodoPringao para luego enlazarlo con la cola "colegas" y volver a enlazar el último elemento de
	* ésta con el siguiente elemento a "pringao" correspondiete a la cola original, en el caso de que
	* exista. Al final, se limpia la cola colegas manualmente para que no se borren los punteros que
	* ahora forman parte de la cola original.
	*/
	void colar(Queue<int> &colegas, int pringao) {	// O(n) en el peor caso siendo n la longitud de la cola original
		Nodo * nodoPringao = _prim;
		Nodo * sigPringao = _prim;
		bool encontrado = false, ultimo = false;

		while (!encontrado && !ultimo) {	// El coste O(n) es debido a este bucle
			if(nodoPringao->_elem == pringao) encontrado = true;
			if(nodoPringao == _ult) ultimo = true;

			if(!encontrado && !ultimo) nodoPringao = nodoPringao->_sig;
		}

		if (encontrado) {
			if (!ultimo) sigPringao = nodoPringao->_sig;	// Sin embargo la operación de junta ambas colas es coste O(1), ya
															// que simplemente se realizan 3 operaciones para enlazar los nodos.
			nodoPringao->_sig = colegas._prim;
			if (!ultimo) colegas._ult->_sig = sigPringao;
		}

		colegas._numElems = 0;
		colegas._prim = NULL;
		colegas._ult = NULL;
	}

protected:

	void libera() {
		libera(_prim);
	}

	void copia(const Queue &other) {

		if (other.empty()) {
			_prim = _ult = NULL;
			_numElems = 0;
		}
		else {
			Nodo *act = other._prim;
			Nodo *ant;
			_prim = new Nodo(act->_elem);
			ant = _prim;
			while (act->_sig != NULL) {
				act = act->_sig;
				ant->_sig = new Nodo(act->_elem);
				ant = ant->_sig;
			}
			_ult = ant;
			_numElems = other._numElems;
		}
	}

private:

	/**
	Clase nodo que almacena internamente el elemento (de tipo T),
	y un puntero al nodo siguiente, que podr�a ser NULL si
	el nodo es el �ltimo de la lista enlazada.
	*/
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) :
			_elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};

	/**
	Elimina todos los nodos de la lista enlazada cuyo
	primer nodo se pasa como par�metro.
	Se admite que el nodo sea NULL (no habr� nada que
	liberar).
	*/
	static void libera(Nodo *prim) {
		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al �ltimo elemento. */
	Nodo *_ult;

	/** N�mero de elementos */
	int _numElems;
};

#endif // __LINKED_LIST_QUEUE_H
