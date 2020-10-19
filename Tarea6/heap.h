#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T>
class Heap {
private:
	T *valor; 
	int size; 
	int count; 
	int parent(int) const; 
	int left(int) const; 
	int right(int) const; 
	void swap(int, int);
    void heapify(int); 
public:
	Heap(int);
	void push(T); 
	void pop(); 
    T top() const; 
    bool empty() const; 
    int size() const;
	string toString() const;
};

template <class T>
Heap<T>::Heap(int _size) { 
	size = _size;
	valor = new T[size]; 
	count = 0;
}

template <class T>
int Heap<T>::parent(int pos) const {
	return (pos - 1) / 2;
}

template <class T>
int Heap<T>::left(int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
int Heap<T>::right(int pos) const {
	return ((2 * pos) + 2);
}

template <class T>
string Heap<T>::toString() const {
	stringstream aux;
	aux << "[";	for (int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << valor[i];
	} aux << "]";
	return aux.str();
}

template <class T>
void Heap<T>::swap(int i, int j) {
	T aux = valor[i];
	valor[i] = valor[j];
	valor[j] = aux;
}

template <class T>
void Heap<T>::heapify(int pos) {
	int le = left(pos);
	int ri = right(pos);
	int min = pos;
	if (le <= count && valor[le] < valor[min]) {
		min = le;
	}
	if (ri <= count && valor[ri] < valor[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val){ 
	int pos;
	pos = count;
	count++;

	while (pos > 0 && val < valor[parent(pos)]) {
		valor[pos] = valor[parent(pos)];
		pos = parent(pos);
	}
	valor[pos] = val;
}

template <class T>
void Heap<T>::pop(){
	T aux = valor[0];

	valor[0] = valor[--count];
	heapify(0);
}

template <class T>
T Heap<T>::top() const{
	T aux = valor[0];
	return aux;
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

template <class T>
int Heap<T>::size() const{
	return count;
}

#endif
