#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T>
class Heap{ //Clase principal
private:
	T *valor;
	unsigned int extent;
	unsigned int count;
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);
public:
	Heap(unsigned int);
	void push(T);
	T pop();
  T top();
	int size() const;
  bool empty() const;
	string toString() const;
};

template <class T> //Funcion padre
unsigned int Heap<T>::parent(unsigned int position) const {
	return (position - 1) / 2;
}

template <class T> //Funcion izquierda
unsigned int Heap<T>::left(unsigned int position) const {
	return ((2 * position) + 1);
}

template <class T> //Funcion derecha
unsigned int Heap<T>::right(unsigned int position) const {
	return ((2 * position) + 2);
}

template <class T> //Creamos el constructor de la clase principal
Heap<T>::Heap(unsigned int _ext){
	extent = _ext;
	valor = new T[extent];
	count = 0;
}

template <class T> //Funcion para voltear valores dentro del heap
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = valor[i];
	valor[i] = valor[j];
	valor[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int position) {
	unsigned int le = left(position);
	unsigned int ri = right(position);
	unsigned int min = position;
	if (le <= count && valor[le] < valor[min]) {
		min = le;
	}
	if (ri <= count && valor[ri] < valor[min]) {
		min = ri;
	}
	if (min != position) {
		swap(position, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val){ //Aniadimos un valor a la fila
	unsigned int position;
	position = count;
	count++;
	while (position > 0 && val < valor[parent(position)]){
		valor[position] = valor[parent(position)];
		position = parent(position);
	}
	valor[position] = val;
}

template <class T>
T Heap<T>::pop(){ //Sacar un valor de la fila
	T aux = valor[0];
	valor[0] = valor[--count];
	heapify(0);
	return aux;
}

template <class T>
T Heap<T>::top(){ //Retornar el primer valor de la lista
  T aux = valor[0];
  return aux;
}

template <class T>
bool Heap<T>::empty() const { //Funcion booleana para  comprobar fila
	return (count == 0);
}

template <class T>
int Heap<T>::size() const { //Longitud de la fila
	return count;
}

template <class T>
string Heap<T>::toString() const { //Pasar a string
	stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << valor[i];
	} aux << "]";
	return aux.str();
}

#endif
