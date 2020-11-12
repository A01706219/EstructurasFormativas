#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

string ImprimirVector(vector<int> vec){ //Funcion promedio para cambiar de vector a string para poderla imprimir
	string resultado = "";
	for (int i = 0; i < vec.size(); i++) { //Por cada iteracion de la longitud del vector cambiamos cada uno a string
		resultado = resultado + to_string(vec[i]) + " ";
	}
	return resultado; //Imprimimos el string resultante
}

class Graph { //Creamos la funcion de grafos y definimos sus funciones
	private:
	vector<vector<int>> adj_matriz;
	vector<vector<int>> adj_list;
	int numvertices;
	int numarcos;

	public:
	Graph(){}
	void loadGraphMat(string nombreArch, int vertices, int arcos);
	void loadGraphList(string nombreArch, int vertices, int arcos);

	string printAdjMat();
	string printAdjList();

	string DFS(int InicializarVertice, int target_vertex);
	string BFS(int InicializarVertice, int target_vertex);
};

void Graph::loadGraphMat(string nombreArch, int vertices, int arcos){ //Esta primera funcion cambia de grafo a una matriz de adjacencia
	numarcos = arcos;
	numvertices = vertices; 

	for (int i = 0; i < vertices; i++){
		vector<int> row(vertices, 0);
		adj_matriz.push_back(row);
	}

	ifstream file;
	file.open(nombreArch);
	while(file.good()){
		string InicializarVertice; 
		string FinalizarVertice;

		getline(file, InicializarVertice, ',');
		getline(file, FinalizarVertice, '\n');

		InicializarVertice = InicializarVertice.substr(1, InicializarVertice.length()-1);

		FinalizarVertice = FinalizarVertice.substr(1, FinalizarVertice.length()-2);

		int InicializarNodo = stoi(InicializarVertice);
		int FinalizarNodo = stoi(FinalizarVertice);
		
		adj_matriz[InicializarNodo][FinalizarNodo] = 1; //Rellenamos la matriz
		adj_matriz[FinalizarNodo][InicializarNodo] = 1;
	}
}

void Graph::loadGraphList(string nombreArch, int vertices, int arcos){
	numvertices = vertices;
	numarcos = arcos;
	for (int i=0; i<vertices; i++){ //Aqui creamos la matriz 
		vector<int> row;
		adj_list.push_back(row);
	}

	ifstream file;
	file.open(nombreArch);
	while(file.good()){ //Leemos el archivo y sacamos su contenido
		string InicializarVertice;
		string FinalizarVertice;
		getline(file, InicializarVertice, ',');
		getline(file, FinalizarVertice, '\n');
		InicializarVertice = InicializarVertice.substr(1, InicializarVertice.length()-1);
		FinalizarVertice = FinalizarVertice.substr(1, FinalizarVertice.length()-2);
		int InicializarNodo = stoi(InicializarVertice);
		int FinalizarNodo = stoi(FinalizarVertice);
		adj_list[InicializarNodo].push_back(FinalizarNodo); //Con estas funciones llenamos la matriz
		adj_list[FinalizarNodo].push_back(InicializarNodo);
	}
}

string Graph::printAdjMat(){ //Funcion para imprimir la matriz
	string resultado = "";
	for(int i = 0; i < adj_matriz.size(); i++){
		for(int j = 0; j < adj_matriz[i].size(); j++){
			resultado = resultado + to_string(adj_matriz[i][j]) + " ";
		}
	}
	return resultado;
}

string Graph::printAdjList(){ //Funcion para imprimir la lista
	string resultado = "";
	for(int i = 0; i < adj_list.size(); i++){
		resultado += "vertex " + to_string(i) + " : ";
		sort(adj_list[i].begin(), adj_list[i].end());
		for(int j = 0; j < adj_list[i].size(); j++){
			resultado += to_string(adj_list[i][j]) + " ";
		}
	}
	return resultado;
}

string Graph::DFS(int InicializarVertice, int target_vertex){ //Empezamos con la Depth-first search
	vector<vector<int>> adj_list_copy; //Copiamos la lista
	for (int i = 0; i < adj_list.size(); i++){
		adj_list_copy.push_back(adj_list[i]);
	}
	vector<int> stack;
	vector<int> visited;
	bool found = false;
	int current = InicializarVertice;

	while (!found && !(visited.size() >= numvertices)){ //Vamos checando si el actual ya fue visitado
		bool already_visited = false;
		for (int i=0; i<visited.size(); i++){
			if(current == visited[i]) {
				already_visited = true;
				break;
			}
		}

		if (!already_visited) visited.push_back(current); //Si todavia no la hemos visitado la añadimos

		if (current == target_vertex){ //Si lo encontramos cambiamos la variable a verdadero
			found = true;
			break;
		}

		for (int i = 0; i < adj_list_copy[current].size(); i++){ //Esta funcion sirve para resetear las variables de visitado
			for (int j = 0; j < visited.size(); j++){
				if(adj_list_copy[current][i] == visited[j])
					adj_list_copy[current].erase(adj_list_copy[current].begin()+i);
			}
		}
		if (adj_list_copy[current].size() > 0){ //Buscamos al hijo del nodo
			stack.push_back(current);
			int temp_index = current;
			current = adj_list_copy[current].back();
			adj_list_copy[temp_index].pop_back();
		} 
		else {
			current = stack[stack.size()-1];
			stack.pop_back();
		}
	}
	stack.push_back(current); //Aniadimos el valor al stack
	
	string visited_str = ImprimirVector(visited);
	string path_str = ImprimirVector(stack);
	string resultado = "visited: " + visited_str + "path: " + path_str;
	resultado = resultado.substr(0, resultado.size()-1);
	return resultado; //Finalmente lo convertimos a un string
}


string Graph::BFS(int InicializarVertice, int target_vertex){ //Iniciamos con el Breadth-First Search
	vector<vector<int>> queue;
	vector<vector<int>> visited;
	int current = InicializarVertice;
	int parent = -1;
	bool found = false;

	while (true){
		visited.push_back(vector<int>({parent, current}));

		if (current == target_vertex){
			found = true;
			break;
		}

		for (int i=0; i<adj_list[current].size(); i++){ //Los hijos son enviados al queue si no han sido visitados
			int val = adj_list[current][i];
			bool already_visited = false;
			for (int j=0; j<visited.size(); j++){
				if (visited[j][1] == val){
					already_visited = true;
					break;
				}
			}
			if (!already_visited) queue.push_back(vector<int>({current, val}));
		}
		parent = queue[0][0];
		current = queue[0][1];
		queue.erase(queue.begin());
	}
	vector<int> path; //Finalmente buscamos el camino
	int find = target_vertex;
	do {
		for (int i=0; i<visited.size(); i++){
			if (visited[i][1] == find){
				path.insert(path.begin(), find);
				find = visited[i][0];
			}
		}
	} while (find != -1);
	vector<int> converted_visited;
	for (int i=0; i<visited.size(); i++){
		converted_visited.push_back(visited[i][1]);
	}

	string visited_str = ImprimirVector(converted_visited);
	string path_str = ImprimirVector(path);
	string resultado = "visited: " + visited_str + "path: " + path_str;
	resultado = resultado.substr(0, resultado.size()-1);
	return resultado;	//Finalmente lo pasamos a string
}

#endif
