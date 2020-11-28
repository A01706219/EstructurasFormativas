#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(const DLink<T>&);

	T value;
	DLink<T>* next;
	DLink<T>* previous;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), next(0), previous(0) {}

template <class T>
DLink<T>::DLink(const DLink<T>& source) : value(source.value), next(source.next), previous(source.previous) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	void addFirst(T);
	void add(T);
	T find(T) const;
	bool update(int, T);
	T removeFirst();
	T remove(int);

	bool empty() const;
	std::string toStringForward() const;
	std::string toStringBackward() const;
	void operator= (const DList&);

private:
	DLink<T>* head;
	DLink<T>* tail;
	int size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {}

template <class T>
bool DList<T>::empty() const {
	return (head == 0);
}

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T>* p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T>* p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template <class T>
void DList<T>::addFirst(T val) {
	DLink<T>* newLink; //Creamos el nuevo objeto
	newLink = new DLink<T>(val);
	if (empty()) { //Si la lista esta vacia decimos que el nuevo objeto es el head y el tail
		head = newLink;
		tail = newLink;
	}
	else { //Si tiene más elementos la lista añadimos el valor que queramos en el objeto al principio
		newLink->next = head; //El elemento nuevo como va al principio va a ser la head
		head->previous = newLink; //Creamos el apuntador del que era la head hacia la nueva head que es el valor que añadiste
		head = newLink; //Definimos que el nuevo valor es la head
	}
	size++; //El tamaño de la lista crece por uno
}

template <class T>
void DList<T>::add(T val) {
	DLink<T>* newLink; //Creamos el nuevo objeto
	newLink = new DLink<T>(val);

	if (empty()) { //Si la lista esta vacia decimos que el nuevo objeto es el head y el tail
		head = newLink; 
		tail = newLink;
	}
	else {
		tail->next = newLink; //Como vamos a añadir el nuevo objeto al final de la lista decimos que va despues de la tail
		newLink->previous = tail; //Creamos un apuntador al elemento pasado que era la tail
		tail = newLink; //Ahora decimos que el nuevo elemento es tail
	}
	size++; //El tamaño de la lista crece por uno
}

template <class T>
T DList<T>::removeFirst() {
	T val;
	DLink<T>* p;

	if (empty()) {
		return -1; //Si esta vacio que devuelva un -1
	}

	p = head; //Definimos un auxiliar p y le damos el valor del objeto que vamos a borrar
	val = p->value;  //Guardamos ese valor en p

	if (head == tail) { //Si solo hay un elemento en la lista decimos que el head y el tail apunten a null
		head = 0; 
		tail = 0;
	}
	else {
		head = p->next; //Si hay mas elementos decimos que head ahora va a ser el valor que sigue del que vamos a borrar
		p->next->previous = 0; //Quitamos los apuntadores del primero elemento apuntandolos a null
	}

	delete p; //Ya que no esta enlazado con nada lo podemos borrar
	size--; //La lista mide uno menos porque borramos b

	return val; //Regresamos el valor del elemento que borramos
}

template <class T>
T DList<T>::remove(int index) {
	int pos; //Definimos una variable auxilar
	T val;
	DLink<T>* p; //Creamos un apuntador auxiliar

	if (empty()) { //Si esta vacia la lista no podemos borrar nada y regresa un -1
		return -1;
	}

	if (index == 0) { //Si quiere borrar el primer elemento usamos la función removeFirst()
		return removeFirst();
	}

	p = head; //Decimos que p auxiliar es la head
	pos = 0; //variable auxiliar
	while (index != pos) { //Mientras la posición que se busque sea diferente a la posición actual, p se itera y la posición auxiliar crece
		p = p->next;
		pos++;
	}
	val = p->value; //Cuando encontremos el valor lo guardamos en val
	p->previous->next = p->next; //Quitamos los apuntadores del elemento y el elemento pasado ahora apunta al siguiente que puede ser otro elemento o null

	if (p->next != 0) { //Si el elemento que sigue no es un null, creamos un apuntador del siguiente de p al pasado
		p->next->previous = p->previous;
	}

	size--; //La lista disminuye 1

	delete p; //borramos p
	return val; //Regresamos el valor de p
}

template <class T>
bool DList<T>::update(int index, T val) {
	DLink<T>* p; //Creamos dos variables auxiliares
	DLink<T>* q;
	int pos; //Creamos una variable auxiliar de la posición 

	if (index < 0 || index >= size) { //Si el elemento que busca cambiar esta fuera de rango regresamos un -1
		return -1;
	}
	p = head; //Inicializamos p con head
	pos = 0; 
	while (pos != index) { //Mientras la posición no llegue al index buscado, iteramos p y aumentamos la posición
		p = p->next;
		pos++;
	}
	p->value = val; //Cuando encontremos el valor decimos que su valor pasado ahora es val que es lo que recibe la función
	return true;
}

template <class T>
T DList<T>::find(T val) const {
	DLink<T>* p; //Creamos variable auxiliar

	p = head; //Inicializamos p en head
	T index = 0; //Inicializamos index en 0
	while (p != 0) { //Mientras la iteración no se salga de la lista que se vaya iterando
		if (p->value == val) { //Por cada iteración comprobamos si el valor buscado es el actual
			return index; //Si lo es buscamos la posición donde esta
		}
		p = p->next; //Iteramos p
		index++; //Crece el index
	}
	return -1; //Si no encotramos el valor regresamos un -1
}

#endif
