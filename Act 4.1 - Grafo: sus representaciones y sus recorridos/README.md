Grafos

loadGraphMat Análisis de complejidad temporal

En el peor de los casos tenemos O(n) ya que la función lee todo el contenido de un archivo con longitud n y lo añade a una nueva matriz.

loadGraphList Análisis de complejidad temporal

Igualmente esta función tiene una complejidad de O(n) ya que lee todo lo del archivo pero en este caso lo pasa a una lista.

DFS Análisis de complejidad temporal

Esta función recorre el grafo por la profundidad de forma ordenada por cada uno de sus hijos y por esto su complejidad es O(V+E) donde V son vertices y E son los arcos

BFS Análisis de complejidad temporal

La última función sirve para encontrar el camino más corto al nodo buscado por niveles y por esto su complejidad es de O(V+E) donde V son vertices y E son los arcos
