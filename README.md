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

El programa estará dividido en diferentes partes para que posteriormente podamos agregar nuevas funciones de manera sencilla sin modificar todo el código.

## Primer avance

En el primer avance los productos estaban en un arreglo dentro del main y los ordenaba por precio y por stock con Insertion Sort.

## Segundo avance

Para este avance hice varios cambios. Los productos ya no están escritos en el código, ahora los leo del archivo productos.csv y los guardo en un árbol AVL ordenado por nombre. También cambié Insertion Sort por Merge Sort.

Aparte agregué al menú las opciones de buscar, agregar, eliminar, actualizar stock y guardar en el archivo.

Separé el código en estos archivos:
* main.cpp: el menú y la lectura del archivo
* producto.h: la clase Producto
* avl.h: el árbol AVL
* sorts.h: el merge sort
* productos.csv: los productos

### Correcciones del avance 1

El profe me comentó que para tomar una decisión necesitaba comparar opciones con un criterio. Ahora en la sección de Toma decisiones comparo varios algoritmos por su complejidad, y por eso cambié Insertion Sort por Merge Sort. También actualicé el análisis de complejidad con lo nuevo.

## Cómo usar el programa

Compilar:
```
g++ -std=c++17 main.cpp -o fynix
```

Ejecutar:
```
./fynix
```

El archivo productos.csv tiene que estar en la misma carpeta, si no el programa arranca vacío.

En el menú puedes ver todos los productos (salen en orden alfabético), ordenarlos por precio o por stock, buscar uno por nombre, agregar, eliminar, cambiar el stock y guardar los cambios en el archivo. Con 0 se sale.

Para buscar o eliminar hay que escribir el nombre igual que como está, por ejemplo Gorra Fynix.

Si quieres agregar productos directo en el archivo, cada línea va así:
```
id,nombre,categoria,precio,stock
1,Dri-FIT,Playera,250,12
```

## SICT0302: Toma decisiones

### Algoritmo de ordenamiento

En el avance 1 usé Insertion Sort, pero para este avance comparé varios algoritmos usando su complejidad:

* Bubble Sort: O(n²) en promedio y peor caso
* Selection Sort: O(n²) en todos los casos
* Insertion Sort: O(n) en el mejor caso, pero O(n²) en promedio y peor caso
* Quick Sort: O(n log n) en promedio, pero O(n²) en el peor caso
* Merge Sort: O(n log n) en todos los casos

Elegí Merge Sort porque es el único que se mantiene en O(n log n) siempre. Con Insertion Sort, si la tienda tiene muchos productos, el tiempo crece bastante por ser O(n²). Quick Sort también es rápido pero puede caer en O(n²). Lo malo de Merge Sort es que necesita un vector extra (O(n) de memoria), pero para el inventario de una tienda no es problema.

Lo uso para ordenar por precio y por stock (opciones 2 y 3).

### Estructura de datos

Para guardar los productos elegí un árbol AVL. Lo que más se hace en el programa es buscar productos por nombre, agregar y eliminar, entonces comparé:

* Vector o lista: buscar y eliminar es O(n) porque hay que recorrer todo
* BST: normalmente es O(log n), pero si los datos entran ordenados se hace como una lista y queda en O(n)
* AVL: siempre es O(log n) porque se balancea solo con rotaciones

Por eso el AVL fue la mejor opción. Otra ventaja es que al recorrerlo en inorden los productos ya salen en orden alfabético, así que para mostrar el catálogo no tengo que ordenar nada.

Para ordenar por precio o stock saco una copia de los productos del árbol y ordeno la copia, así el árbol no se desordena.

## SICT0301: Evalúa los componentes

### Árbol AVL

* insertar: O(log n)
* buscar: O(1) en el mejor caso (si está en la raíz), O(log n) en promedio y peor caso
* eliminar: O(log n)
* inorden: O(n) porque pasa por todos los nodos
* rotaciones y balancear: O(1), solo cambian unos apuntadores

Insertar, buscar y eliminar son O(log n) porque solo bajan por la altura del árbol, y como el AVL se balancea su altura siempre es más o menos log n. En memoria ocupa O(n), un nodo por producto.

### Merge Sort

Es O(n log n) en mejor, promedio y peor caso. El vector se divide a la mitad log n veces y en cada nivel se mezclan los n elementos. Usa O(n) de memoria extra por el vector temporal.

### Producto

Todos los métodos de la clase (constructores, getters, setStock y mostrar) son O(1).

### Programa

* Cargar el archivo: O(n log n), porque son n productos y cada inserción en el árbol es O(log n)
* Guardar el archivo: O(n)
* Mostrar productos: O(n)
* Ordenar por precio o stock: O(n log n), sacar la copia es O(n) y el merge sort O(n log n)
* Buscar, agregar, eliminar y actualizar stock: O(log n)

En total el programa queda en O(n log n), por la carga del archivo y el ordenamiento.

## SICT0303: Implementa acciones científicas

### Consultas

Para buscar un producto uso la función buscar del árbol, que va comparando el nombre y se va a la izquierda o derecha hasta encontrarlo. Esto se usa en buscar producto y en actualizar stock. Si no existe, el programa avisa que no se encontró.

Para mostrar el catálogo uso el recorrido inorden, y para ver por precio o stock ordeno una copia con merge sort.

### Lectura de archivos

En la función cargarArchivo abro productos.csv con ifstream, me salto la primera línea (el encabezado) y después leo cada línea separándola por comas con stringstream y getline. El id, precio y stock los convierto a int con stoi, creo el Producto y lo inserto en el árbol.

También se puede guardar el inventario en el mismo archivo con la opción 8, usando ofstream.

### Dónde está en el código

Los productos se cargan en cargarArchivo (main.cpp, línea 19) y se insertan con insertar (avl.h, línea 110).

Para consultar uso buscar (avl.h, línea 118) en las opciones 4 y 7, y el inorden (avl.h, línea 137) para mostrar el catálogo.

El balanceo está en balancear (avl.h, línea 45) y el merge sort en sorts.h, que se usa en main.cpp en las líneas 100 y 105.

## Objetivo del proyecto

El objetivo principal es desarrollar un sistema que permita organizar y consultar de manera eficiente la información de los productos de FYNIX, aplicando estructuras de datos, algoritmos de ordenamiento y búsqueda, análisis de complejidad y buenas prácticas de programación.

El proyecto busca que la información del catálogo pueda ser consultada y organizada de diferentes maneras, facilitando su manejo conforme aumente la cantidad de productos.
