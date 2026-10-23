# FYNIX - Sistema de Gestión para Tienda de Ropa Deportiva

**Alumno:** Samuel Estrella Martínez
**Matrícula:** A01714991

## Descripción del proyecto

FYNIX es un proyecto enfocado en desarrollar un sistema para la gestión de una tienda de ropa deportiva.

El sistema tendrá como objetivo organizar y facilitar el manejo de la información relacionada con los productos de la tienda, permitiendo consultar el catálogo, organizar los productos, conocer su disponibilidad y acceder a la información de manera eficiente.

Los productos de FYNIX contarán con diferentes atributos, como:

* ID
* Nombre
* Categoría
* Talla
* Precio
* Stock

A lo largo del desarrollo del proyecto se irán agregando diferentes funcionalidades para mejorar la administración así como la consulta del catálogo.

Entre las funcionalidades que se contemplan para el proyecto se encuentran:

* Registro y almacenamiento de productos.
* Consulta del catálogo.
* Ordenamiento de productos por diferentes atributos.
* Filtros para consultar productos específicos.
* Búsqueda de productos.
* Consulta de disponibilidad y stock.
* Organización de los productos por categoría, precio, talla u otros atributos.
* Acceso eficiente a la información almacenada.

El programa está dividido en diferentes archivos para que posteriormente podamos agregar nuevas funciones de manera sencilla sin modificar todo el código:

* **main.cpp:** menú del programa y lectura y escritura del archivo.
* **producto.h:** clase Producto.
* **avl.h:** árbol AVL donde se almacenan los productos.
* **sorts.h:** algoritmo de ordenamiento Merge Sort.
* **productos.csv:** archivo con los datos de los productos.

## Primer avance

En el primer avance se trabajó principalmente con el almacenamiento de los productos y su organización mediante algoritmos de ordenamiento.

Los productos se almacenaban en un arreglo dentro del código y se ordenaban por precio y por stock utilizando **Insertion Sort**.

## Segundo avance

En este segundo avance los datos se almacenan en una estructura que permite organizarlos de forma natural y se cambia el algoritmo de ordenamiento por uno más eficiente.

Los cambios realizados en este avance son:

* Los productos se cargan desde el archivo **productos.csv** en lugar de estar escritos en el código.
* Los productos se almacenan en un **árbol AVL** ordenado por nombre.
* Se reemplazó Insertion Sort por **Merge Sort** para ordenar los productos por precio y por stock.
* Se agregaron opciones para buscar, agregar, eliminar y actualizar el stock de un producto.
* Se agregó una opción para guardar los cambios en el archivo.

### Cambios realizados con base en la retroalimentación

* **Evalúa los componentes:** se actualizó el análisis de complejidad incluyendo el nuevo algoritmo de ordenamiento, la estructura de datos y las funciones del programa.
* **Toma decisiones:** se realizó el análisis de complejidad de varios algoritmos de ordenamiento para tener un criterio de selección. Con base en ese análisis se seleccionó Merge Sort en lugar de Insertion Sort.

## Cómo usar el programa

Para compilar el programa:

```
g++ -std=c++17 main.cpp -o fynix
```

Para ejecutarlo (el archivo **productos.csv** debe estar en la misma carpeta):

```
./fynix
```

Al iniciar, el programa carga los productos del archivo y muestra el siguiente menú:

* **1.** Mostrar todos los productos en orden alfabético.
* **2.** Ordenar los productos por precio.
* **3.** Ordenar los productos por stock.
* **4.** Buscar un producto por nombre.
* **5.** Agregar un producto.
* **6.** Eliminar un producto.
* **7.** Actualizar el stock de un producto.
* **8.** Guardar los cambios en el archivo.
* **0.** Salir.

Para buscar, eliminar o actualizar un producto se debe escribir el nombre tal como aparece en el catálogo, por ejemplo: *Gorra Fynix*.

El archivo **productos.csv** utiliza el siguiente formato:

```
id,nombre,categoria,precio,stock
1,Dri-FIT,Playera,250,12
2,Oversize,Playera,300,8
```

## Estructura de datos

Para este avance se utiliza un **árbol AVL**.

El árbol AVL es un árbol binario de búsqueda que se balancea automáticamente. Cada vez que se inserta o elimina un producto, el árbol revisa la diferencia de altura entre sus subárboles y, si está desbalanceado, realiza rotaciones para mantener su altura en log n.

Los productos se ordenan dentro del árbol por su nombre, por lo que al recorrerlo en inorden se obtiene el catálogo en orden alfabético.

## Algoritmo de ordenamiento

Para este avance se utiliza **Merge Sort**.

El algoritmo divide el vector de productos a la mitad hasta llegar a elementos individuales y después los va mezclando de manera ordenada de acuerdo con el atributo seleccionado (precio o stock).

Para ordenar, se obtiene una copia de los productos del árbol con el recorrido inorden y se ordena esa copia, de esta forma el árbol no pierde su orden.

## SICT0301: Evalúa los componentes

Para el segundo avance se realiza el análisis de complejidad de la estructura de datos, del algoritmo de ordenamiento y de cada una de las funciones del programa.

### Árbol AVL

* **Insertar:** O(log n) en el mejor, promedio y peor caso.
* **Buscar:** O(1) en el mejor caso, O(log n) en el caso promedio y en el peor caso.
* **Eliminar:** O(log n) en el mejor, promedio y peor caso.
* **Recorrido inorden:** O(n) en todos los casos.
* **Rotaciones y balanceo:** O(1) en todos los casos.

Insertar, buscar y eliminar recorren únicamente la altura del árbol. Como el árbol AVL se balancea después de cada inserción o eliminación, su altura siempre es log n, por lo que estas operaciones son O(log n) incluso en el peor caso.

El mejor caso de la búsqueda ocurre cuando el producto se encuentra en la raíz, por lo que la complejidad es O(1).

El recorrido inorden visita cada uno de los nodos una sola vez, por lo que su complejidad es O(n).

Las rotaciones solo cambian unos cuantos apuntadores, por lo que su complejidad es O(1).

La complejidad espacial del árbol es **O(n)**, debido a que se crea un nodo por cada producto.

### Merge Sort

* **Mejor caso:** O(n log n)
* **Caso promedio:** O(n log n)
* **Peor caso:** O(n log n)

El algoritmo divide el vector a la mitad hasta llegar a elementos individuales, generando log n niveles. En cada nivel se mezclan los n elementos, por lo que la complejidad es O(n log n) sin importar el orden inicial de los datos.

La complejidad espacial de Merge Sort es **O(n)**, debido al vector temporal que se utiliza para mezclar los elementos.

### Clase Producto

Los constructores, getters, setters y la función mostrar tienen complejidad **O(1)** en todos los casos, debido a que únicamente asignan, regresan o imprimen los atributos del producto.

### Programa principal

* **Cargar el archivo:** O(n log n), se leen n productos y cada uno se inserta en el árbol en O(log n).
* **Guardar el archivo:** O(n), se recorre el árbol y se escribe cada producto.
* **Mostrar productos:** O(n), se realiza el recorrido inorden del árbol.
* **Ordenar por precio o por stock:** O(n log n), el recorrido inorden es O(n) y Merge Sort es O(n log n).
* **Buscar producto:** O(log n).
* **Agregar producto:** O(log n).
* **Eliminar producto:** O(log n).
* **Actualizar stock:** O(log n), se busca el producto en O(log n) y se modifica en O(1).

La complejidad final del programa es **O(n log n)**, debido a que las operaciones más costosas son la carga del archivo y el ordenamiento de los productos.

## SICT0302: Toma decisiones

### Selección del algoritmo de ordenamiento

Para seleccionar el algoritmo de ordenamiento se utilizó como criterio su complejidad temporal. Se compararon los siguientes algoritmos:

* **Bubble Sort:** O(n) en el mejor caso, O(n²) en el caso promedio y en el peor caso.
* **Selection Sort:** O(n²) en el mejor, promedio y peor caso.
* **Insertion Sort:** O(n) en el mejor caso, O(n²) en el caso promedio y en el peor caso.
* **Quick Sort:** O(n log n) en el mejor caso y en el caso promedio, O(n²) en el peor caso.
* **Merge Sort:** O(n log n) en el mejor, promedio y peor caso.

Se seleccionó **Merge Sort** debido a que es el único de estos algoritmos que mantiene una complejidad de O(n log n) en todos los casos.

Insertion Sort, que se utilizó en el primer avance, así como Bubble Sort y Selection Sort, tienen una complejidad de O(n²) en el caso promedio, por lo que el tiempo de ejecución crece mucho conforme aumenta la cantidad de productos. Quick Sort es eficiente en el caso promedio, pero en el peor caso también llega a O(n²).

La desventaja de Merge Sort es que utiliza O(n) de memoria adicional, sin embargo, para la cantidad de productos que maneja una tienda esto no representa un problema.

### Selección de la estructura de datos

Las operaciones más comunes del sistema son buscar productos por nombre, agregarlos, eliminarlos y mostrar el catálogo en orden. Para seleccionar la estructura se compararon las siguientes opciones:

* **Arreglo o vector:** buscar O(n), insertar O(1), eliminar O(n).
* **Lista ligada:** buscar O(n), insertar O(1), eliminar O(n).
* **Árbol binario de búsqueda (BST):** buscar, insertar y eliminar en O(log n) en el caso promedio, pero O(n) en el peor caso.
* **Árbol AVL:** buscar, insertar y eliminar en O(log n) en todos los casos.

Se seleccionó el **árbol AVL** debido a que garantiza una complejidad de O(log n) incluso en el peor caso. Un árbol binario de búsqueda normal puede convertirse en una lista si los productos se insertan ordenados, haciendo que sus operaciones sean O(n). El árbol AVL evita este problema al balancearse con rotaciones.

Además, el recorrido inorden del árbol AVL regresa los productos ordenados alfabéticamente, por lo que el catálogo se puede mostrar sin necesidad de ordenarlo.

## SICT0303: Implementa acciones científicas

### Mecanismos para consultar información

* **Búsqueda por nombre:** la función buscar del árbol compara el nombre con cada nodo y avanza hacia la izquierda o la derecha, descartando la mitad del árbol en cada paso.
* **Mostrar catálogo:** el recorrido inorden regresa todos los productos en orden alfabético.
* **Consultar por precio o stock:** se ordena una copia de los productos con Merge Sort y se muestran en pantalla.
* **Actualizar stock:** se busca el producto en el árbol y se modifica su stock directamente.

Si el producto que se busca no existe, el programa muestra un mensaje en lugar de fallar.

### Mecanismos de lectura de archivos

La función **cargarArchivo** se encarga de leer los productos del archivo **productos.csv** de la siguiente manera:

* Abre el archivo con ifstream y, si no se puede abrir, muestra un mensaje.
* Se salta la primera línea, que corresponde al encabezado.
* Lee cada línea con getline y la separa por comas utilizando stringstream.
* Convierte el ID, el precio y el stock a números enteros con stoi.
* Crea un objeto Producto y lo inserta en el árbol AVL.

Además, la opción 8 del menú permite guardar el inventario actualizado en el mismo archivo utilizando ofstream.

## Objetivo del proyecto

El objetivo principal es desarrollar un sistema que permita organizar y consultar de manera eficiente la información de los productos de FYNIX, aplicando estructuras de datos, algoritmos de ordenamiento y búsqueda, análisis de complejidad y buenas prácticas de programación.

El proyecto busca que la información del catálogo pueda ser consultada y organizada de diferentes maneras, facilitando su manejo conforme aumente la cantidad de productos.
