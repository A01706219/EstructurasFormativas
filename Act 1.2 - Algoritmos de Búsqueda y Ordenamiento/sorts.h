#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <list>
#include <iostream>

using namespace std;

template <class T>
class Sorts {
private:
	void swap(vector<T>&, int, int);
	void copyArray(vector<T>&, vector<T>&, int, int);
	void mergeArray(vector<T>&, vector<T>&, int, int, int);
	void mergeSplit(vector<T>&, vector<T>&, int, int);
	int bs_aux(vector<T>&, int, int, int);
public:
	vector<T> ordenaSeleccion(vector<T>&);
	vector<T> ordenaBurbuja(vector<T>&);
	vector<T> ordenaMerge(vector<T>&);
	int busqSecuencial(vector<T>&, int);
	int busqBinaria(vector<T>&, int);

};

template <class T>
void Sorts<T>::swap(vector<T>& prueba, int i, int j) {
	T aux = prueba[i];
	prueba[i] = prueba[j];
	prueba[j] = aux;
}

template <class T>
void Sorts<T>::copyArray(vector<T>& A, vector<T>& B, int low, int high) {

	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(vector<T>& A, vector<T>& B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid && j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		}
		else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	}
	else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(vector<T>& A, vector<T>& B, int low, int high) {
	int mid;

	if ((high - low) < 1) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T> &prueba) {
	for (int i = prueba.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (prueba[j] > prueba[j + 1]) {
				swap(prueba, j, j + 1);
			}
		}
	}
	return prueba;
}

template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T> &prueba) {
	int pos;

	for (int i = prueba.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (prueba[j] > prueba[pos]) {
				pos = j;
			}
		}

		if (pos != i) {
			swap(prueba, i, pos);
		}
	}
	return prueba;
}

template <class T> 
vector<T> Sorts<T>::ordenaMerge(vector<T> &prueba) {
	vector<T> tmp(prueba.size());
	mergeSplit(prueba, tmp, 0, prueba.size() - 1);
	return prueba;
}

template <class T>
int Sorts<T>::busqSecuencial(vector<T>& prueba, int dato) {
	for (int i = 0; i < prueba.size(); i++) {
		if (dato == prueba[i]) {
			return i;
		}
	}
	return -1;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T>& prueba, int val) {
	int min = 0;
	int max = prueba.size() - 1;

	while (min < max) {
		int mid = (max + min) / 2;
		if (prueba[mid] == val) {
			return mid;
		}
		else if (prueba[mid] < val) {
		  min = mid + 1;
		}
		else if (prueba[mid] > val) {
			max = mid - 1;
		}
	}
	return min;
}

#endif


