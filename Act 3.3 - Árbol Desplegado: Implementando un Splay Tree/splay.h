#ifndef SPLAY_H
#define SPLAY_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class SplayTree;

template <class T>
class Node{
private:
	T valor;
	Node *left, *right, *parent;
	Node<T>* succesor();
	Node<T>* r_right(Node<T>*);
	Node<T>* r_left(Node<T>*);
public:
	Node(T);
	Node(T,Node<T>*,Node<T>*,Node<T>*);
	Node<T>*add(T);
	Node<T>*find(T);
	Node<T>*remove(T);
	void removeChilds();
	void inorder(stringstream&) const;
	void verlista(stringstream&) const;
	void preorder(stringstream&) const;
	Node<T>* splay(Node<T>*,Node<T>*);
	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val): valor(val),left(0),right(0),parent(0) {}

template <class T>
Node<T>::Node(T val,Node<T> *le,Node<T> *ri,Node<T> *p)
: valor(val),left(le),right(ri),parent(p){}

template <class T>
Node<T>* Node<T>::add(T val){
	if(val<valor){
		if(left != 0){
			return left->add(val);
		}
		else{
			left = new Node<T>(val);
			left->parent =this;
			return left;
		}
	}
	else{
		if(right != 0){
			return right->add(val);
		}else{
			right = new Node<T>(val);
			right->parent=this;
			return right;
		}
	}
}

template<class T>
Node<T>* Node<T>::find(T val){
	if(val == valor){
		return this;
	}
	else if (val<valor){
		if(left != 0)
			return left->find(val);
		else
			return this;
	}
	else if (val>valor){
		if(right != 0)
			return right->find(val);
		else
			return this;
	}
	return 0;
}

template<class T>
Node<T>* Node<T>::succesor(){
	Node<T> *le,*ri;
	le = left;
	ri = right;

	if(right == 0){
		if(left != 0){
			left = 0;
		}
		if(le)
			le->parent = 0;
		return le;
	}
	if(right->left == 0){
		right = right->right;
		if(right)
			right->parent = parent;
		if(ri){
			ri->right = 0;
			ri->parent = 0;
		}
		return ri;
	}
	Node<T> *p,*c;
	p = right;
	c = right->left;
	while(c->left != 0){
		p = c;
		c = c->left;
	}
	p->left = c->right;
	if(p->left != 0)
		p->left->parent=p;
	c->right = 0;
	return c;
}

template<class T>
void Node<T>::removeChilds(){
	if(left != 0){
		left->removeChilds();
		delete left;
		left = 0;
	}
	if(right != 0){
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template<class T>
Node<T>* Node<T>::remove(T val){
	Node<T> *succ,*old;
	if(val<valor){
		if(left != 0){
			if(left->valor == val){
				old = left;
				succ = left->succesor();
				if(succ !=0){
					succ->left = old->left;
					succ->right = old->right;
					succ->parent = old->parent;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
				}
				left = succ;
				delete old;
				return this;
			}else{
				return left->remove(val);
			}
		}
	}else if (val >valor){
		if(right != 0){
			if(right->valor == val){
				old = right;
				succ = right->succesor();
				if(succ != 0){
					succ->left = old->left;
					succ->right = old->right;
					succ->parent = old->parent;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
				}
				right = succ;
				delete old;
				return this;
			}else{
				return right->remove(val);
			}
		}
	}
	return 0;
}

template <class T>
Node<T>* Node<T>::r_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right= x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->valor == x->valor)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template<class T>
Node<T>* Node<T>::r_left(Node<T>*x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->valor == x->valor)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template<class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x->parent->valor == root->valor){
			if(x->parent->left && x->parent->left->valor == x->valor){
				r_right(x->parent);
			}else{
				r_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent;
			Node<T>*g = p->parent;
			if(p->left && g->left &&
				x->valor == p->left->valor && p->valor == g->left->valor){
				r_right(g);
				r_right(p);
			}else if(p->right && g->right &&
			 x->valor==p->right->valor && p->valor == g->right->valor){
				r_left(g);
				r_left(p);
			}else if(p->left && g->right &&
			 x->valor == p->left->valor && p->valor == g->right->valor){
				r_right(p);
				r_left(g);
			}else{
				r_left(p);
				r_right(g);
			}
		}
	}

	return x;
}

template <class T>
void Node<T>::inorder(stringstream &aux) const {
	if(left != 0){
		left->inorder(aux);
	}
	if(aux.tellp() != 1){
		aux << " ";
	}
	aux << valor;
	if(right != 0){
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::verlista(stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << valor;
		aux << " parent " << parent->valor;
	}else
		aux << "\n root " << valor;
	if (left != 0)
		aux << " left " << left->valor;
	if (right != 0)
		aux << " right " << right->valor;
	aux << "\n";

	if (left != 0) {
		left->verlista(aux);
	}
	if (right != 0) {
		right->verlista(aux);
	}
}

template <class T>
void Node<T>::preorder(stringstream &aux) const {
	aux << valor;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template<class T>
class SplayTree{
private:
	Node<T> *root;
	unsigned int count;
public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	string inorder() const;
	string verlista() const;
	string preorder() const;
	int size() const;
};

template <class T>
SplayTree<T>::SplayTree():root(0) {}

template<class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template<class T>
bool SplayTree<T>::empty() const{
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val){
	if(root != 0){
		Node<T>* added = root->add(val);
		root = root->splay(root,added);
	}
	else{
		root = new Node<T>(val);
	}
	count++;
}

template<class T>
void SplayTree<T>::remove(T val){
	if(root != 0){
		if(val == root->valor){
			Node<T> *succ = root->succesor();
			if(succ != 0){
				succ->left = root->left;
				succ->right = root->right;
				succ->parent = 0;
				if(succ->left)
					succ->left->parent = succ;
				if(succ->right)
					succ->right->parent = succ;
			}
			delete root;
			root = succ;
		}else {
			Node<T>*p = root->remove(val);
			if (p != 0)
				root = root->splay(root,p);
		}
	}
	count--;
}


template<class T>
void SplayTree<T>::removeAll(){
	if(root != 0){
		root->removeChilds();
	}
	delete root;
	root = 0;
}


template<class T>
bool SplayTree<T>::find(T val){
	if(root != 0){
		Node<T>* found = root->find(val);
		if (found == 0) return false;
		root = root->splay(root,found);
		return(root->valor == val);
	}else{
		return false;
	}
}


template<class T>
string SplayTree<T>::inorder() const{
	stringstream aux;

	aux << "[";
	if(!empty()){
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}


template<class T>
string SplayTree<T>::verlista() const{
	stringstream aux;

	aux << "\n ////////////////////// ";
	if(!empty()){
		root->verlista(aux);
	}
	aux << " ////////////////////// \n";
	return aux.str();
}

template<class T>
string SplayTree<T>::preorder() const{
	stringstream aux;

	aux << "[";
	if(!empty()){
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
int SplayTree<T>::size() const {
	return (count);
}

#endif
