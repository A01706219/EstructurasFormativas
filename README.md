-Act 2.2 - Verificación de las funcionalidades de una estructura de datos lineal (Double Linked List)

En la función de add se cambio la complejidad de O(n) a O(1).

-Act 3.2 - Árbol Heap: Implementando una fila priorizada

Al intentar correr el programa había un error que evitaba que se corriera el archivo y tuve que reescribirlo y añadirle el tipo de dato unsigned.
De igual forma en esta actividad cambie la complejidad de las funciones empty y size de O(n) a O(1) por el mismo error de la activiad pasada.

-Act 3.3 - Árbol Desplegado: Implementando un Splay Tree

No se podía compilar el archivo asi que tuve que cambiar las librerias y algunas funciones y casi rehacer todo el h.
También tenía mal la complejidad de:
-add porque puse O(n) y es O(log n).
-remove porque puse O(n) y es O(log n).

-Act 4.1 - Grafo: sus representaciones y sus recorridos

No se podia compilar y aparecia un mensaje en la consola que decia:

terminate called after throwing an instance of 'std::out_of_range'
 what():  basic_string::substr: __pos (which is 1) > this->size() (which is 0)

-En la linea 55 y 84 olvidé ponerle una condición para checar si el vertice esta vacío. "if(InicializarVertice != "")" y por eso mandaba el error.





