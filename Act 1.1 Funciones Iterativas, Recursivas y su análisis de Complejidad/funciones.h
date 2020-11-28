
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

using namespace std;

class Funciones {
public:
	Funciones() {};
	int sumaIterativa(int n);
	int sumaRecursiva(int n);
	int sumaDirecta(int n);
};

int Funciones::sumaIterativa(int n) {
	int suma = 0;
	while (n > 0) {
		suma = suma + n;
		n -= 1;
	}

	return suma;

}

int Funciones::sumaRecursiva(int n) {
	if (n >= 1) {
		return n + sumaRecursiva(n - 1);
	}
	else {
		return 0;
	}
}

int Funciones::sumaDirecta(int n) {
	int suma = 0;

	suma = (n * (n + 1)) / 2;

	return suma;
}

#endif
