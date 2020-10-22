SPLAY

Add Análisis de complejidad temporal

Ya que mandamos a llamar recursivamente la función dentro de múltiples condiciones tenemos complejidad de O(n) cuando n es la longitud del arbol.

Remove Análisis de complejidad temporal

En el remove entra el dato que queremos borrar y recorremos todo el arbol con rotaciones hasta encontrar el dato buscado, y por eso es O(n)

Find Análisis de complejidad temporal

En la función entra un dato que queremos encontrar y regresa un valor booleano si existe dentro del arbol o no. Igual que el remove recorre todo el arbol hasta encontrarlo
y por eso tenemos una complejidad de O(n)

Inorder Análisis de complejidad temporal

La función retorna el árbol en forma de string pero organizado ya que recorre el árbol y lo va acomodando. Igual tenemos un O(n)
 
Size Análisis de complejidad temporal

Finalmente en la función size tenemos O(n) ya que imprime el valor de la longitud del árbol donde n es este valor.
