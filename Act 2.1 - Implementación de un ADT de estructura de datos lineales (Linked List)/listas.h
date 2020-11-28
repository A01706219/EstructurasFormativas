#ifndef LISTAS_H_
#define LISTAS_H_

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include "exception.h"

using namespace std;

template <class T> class List;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);

	T	    value;
	Link<T>* next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&) throw (OutOfMemory);
	~List();

	void addFirst(T) throw (OutOfMemory);
	void add(T) throw (OutOfMemory);
	T find(T) const;
	bool update(int, T) throw (IndexOutOfBounds);
	T    removeFirst() throw (NoSuchElement);
	T    remove(int) throw (IndexOutOfBounds);

	bool empty() const;
	std::string toString() const;
	void operator= (const List&) throw (OutOfMemory);

private:
	Link<T>* head;
	int 	size;

};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T>* p;

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
void List<T>::addFirst(T val) throw (OutOfMemory) {
	Link<T>* newLink;
	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::add(T val) throw (OutOfMemory) {
	Link<T>* newLink, * p;
	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	if (empty()) {
		addFirst(val);
		return;
	}
	p = head;
	while (p->next != 0) {
		p = p->next;
	}
	newLink->next = 0;
	p->next = newLink;
	size++;
}

template <class T>
T List<T>::find(T val) const {
	Link<T>* p;

	p = head;
	T index = 0;
	while (p != 0) {
		if (p->value == val) {
			return index;
		}
		p = p->next;
		index++;
	}
	return -1;
}

template <class T>
T List<T>::removeFirst() throw (NoSuchElement) {
	T val;
	Link<T>* p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	head = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}
template <class T>
T List<T>::remove(int index) throw (IndexOutOfBounds) {
	int pos;
	T val;
	Link<T>* p, * q;

	if (index == 0) {
		return removeFirst();
	}
	p = head;
	q = 0;

	pos = 0;
	while (pos != index) {
		q = p;
		p = p->next;
		pos++;
	}
	val = p->value;
	q->next = p->next;

	delete p;
	size--;

	return val;
}

template <class T>
bool List<T>::update(int index, T val) throw (IndexOutOfBounds) {
	int pos;
	Link<T>* p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}
	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	p->value = val;
	return true;
}


#endif
