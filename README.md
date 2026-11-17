# FYNIX - Sistema de Gestión para Tienda de Ropa Deportiva

**Alumno:** Samuel Estrella Martínez
**Matrícula:** A01714991

## Descripción del proyecto

FYNIX es un proyecto enfocado en desarrollar un sistema para la gestión de mi tienda de ropa deportiva.

El sistema tendrá como objetivo organizar y facilitar el manejo de la información relacionada con los productos de la tienda, permitiendo consultar el catálogo, organizar los productos, conocer su disponibilidad y acceder a la información de manera eficiente.

Los productos de FYNIX contarán con diferentes atributos, como:

* ID
* Nombre
* Categoría
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

## Tercer avance

En este avance terminé el programa para que se pueda cargar, consultar, ordenar y guardar todo.

Mejoré la función de guardar para que revise si el archivo se abrió bien antes de escribir. También, si haces cambios y quieres salir sin guardar, el programa te pregunta si quieres guardar.

Agregué la opción 9 que crea un archivo reporte.txt con cuántos productos hay, cuántas unidades, cuánto vale el inventario y qué productos tienen 5 piezas o menos para saber qué tengo que resurtir.

Antes si escribías letras en el precio o en el stock el programa se trababa, entonces hice las funciones leerNumero y leerTexto para que vuelva a pedir el dato. Tampoco deja poner comas en el nombre porque se rompía el csv. Y si una línea del archivo viene mal, el programa se la salta en lugar de cerrarse.

Por último agregué el análisis de complejidad de las funciones que faltaban y la complejidad final del programa.

## Instrucciones para compilar el avance de proyecto

```
g++ -std=c++17 main.cpp -o fynix
```

## Instrucciones para ejecutar el avance de proyecto

```
./fynix
```

## Descripción de las entradas del avance de proyecto

El programa lee el archivo productos.csv, que tiene que estar en la misma carpeta (si no está, el programa arranca vacío). Cada línea es un producto con este formato:
```
id,nombre,categoria,precio,stock
1,Dri-FIT,Playera,250,12
```

También el usuario escribe datos en el menú: el nombre para buscar, eliminar o cambiar el stock, y nombre, categoría, precio y stock para agregar. Para buscar o eliminar hay que escribir el nombre igual que como está, por ejemplo Gorra Fynix.

## Descripción de las salidas del avance de proyecto

En el menú puedes ver todos los productos (salen en orden alfabético), ordenarlos por precio o por stock, buscar uno por nombre, agregar, eliminar, cambiar el stock, guardar en el archivo y generar el reporte. Con 0 se sale.

En consola salen las tablas de productos y mensajes como "Producto agregado." o "No se encontro el producto.".

Al guardar (opción 8) se reescribe productos.csv con el inventario actualizado, y con la opción 9 se crea reporte.txt. Así se ve el reporte con los productos que tengo:
```
REPORTE FYNIX
Productos: 18
Unidades: 203
Valor del inventario: $45490

Productos con 5 piezas o menos:
Duffel Bag - 2 piezas
Quarter Zip - 3 piezas
Crop Hoodie Girl - 4 piezas
Windbreaker - 5 piezas
```

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

Uso Merge Sort, que es O(n log n) en mejor, promedio y peor caso. El vector se divide a la mitad log n veces y en cada nivel se mezclan los n elementos. Usa O(n) de memoria extra por el vector temporal.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.

##### Árbol AVL

* insertar: O(log n)
* buscar: O(1) en el mejor caso (si está en la raíz), O(log n) en promedio y peor caso
* eliminar: O(log n)
* inorden: O(n) porque pasa por todos los nodos
* rotaciones y balancear: O(1), solo cambian unos apuntadores

Insertar, buscar y eliminar son O(log n) porque solo bajan por la altura del árbol, y como el AVL se balancea su altura siempre es más o menos log n. En memoria ocupa O(n), un nodo por producto.

##### Producto

Todos los métodos de la clase (constructores, getters, setStock y mostrar) son O(1).

#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.

En el código puse la complejidad de cada función en un comentario arriba de ella.

* leerNumero y leerTexto: O(1)
* Cargar el archivo: O(n log n), porque son n productos y cada inserción en el árbol es O(log n)
* Guardar el archivo: O(n), recorre el árbol y escribe una línea por producto
* Mostrar productos: O(n)
* Ordenar por precio o stock: O(n log n), sacar la copia es O(n) y el merge sort O(n log n)
* Buscar, agregar, eliminar y actualizar stock: O(log n), en el mejor caso O(1) si el producto está en la raíz
* Generar reporte: saca los productos del árbol y los recorre una vez (O(n)) y luego ordena los que tienen poco stock con merge sort. Si ninguno tiene poco stock queda en O(n), pero en el peor caso todos tienen poco stock y queda en O(n log n)
* Salir: O(1), o O(n) si hay cambios y decides guardar

##### Complejidad final

Lo más pesado del programa es cargar el archivo, ordenar y generar el reporte, que son O(n log n). Lo demás es O(log n) u O(n), que crece más lento. Como el archivo siempre se carga al iniciar, el programa queda en O(n log n) en el mejor, promedio y peor caso. En memoria es O(n) por el árbol y las copias que hago para ordenar.

### SICT0302: Toma decisiones

#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

En el avance 1 usé Insertion Sort, pero para este avance comparé varios algoritmos usando su complejidad:

* Bubble Sort: O(n²) en promedio y peor caso
* Selection Sort: O(n²) en todos los casos
* Insertion Sort: O(n) en el mejor caso, pero O(n²) en promedio y peor caso
* Quick Sort: O(n log n) en promedio, pero O(n²) en el peor caso
* Merge Sort: O(n log n) en todos los casos

Elegí Merge Sort porque es el único que se mantiene en O(n log n) siempre. Con Insertion Sort, si la tienda tiene muchos productos, el tiempo crece bastante por ser O(n²). Quick Sort también es rápido pero puede caer en O(n²). Lo malo de Merge Sort es que necesita un vector extra (O(n) de memoria), pero para el inventario de una tienda no es problema.

Lo uso para ordenar por precio y por stock (opciones 2 y 3).

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

Para guardar los productos elegí un árbol AVL. Lo que más se hace en el programa es buscar productos por nombre, agregar y eliminar, entonces comparé:

* Vector o lista: buscar y eliminar es O(n) porque hay que recorrer todo
* BST: normalmente es O(log n), pero si los datos entran ordenados se hace como una lista y queda en O(n)
* AVL: siempre es O(log n) porque se balancea solo con rotaciones

Por eso el AVL fue la mejor opción. Otra ventaja es que al recorrerlo en inorden los productos ya salen en orden alfabético, así que para mostrar el catálogo no tengo que ordenar nada.

Para ordenar por precio o stock saco una copia de los productos del árbol y ordeno la copia, así el árbol no se desordena.

### SICT0303: Implementa acciones científicas

#### Implementa mecanismos para consultar información de las estructuras correctos.

Para buscar un producto uso la función buscar del árbol, que va comparando el nombre y se va a la izquierda o derecha hasta encontrarlo. Esto se usa en buscar producto y en actualizar stock. Si no existe, el programa avisa que no se encontró.

Para mostrar el catálogo uso el recorrido inorden, y para ver por precio o stock ordeno una copia con merge sort.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

En la función cargarArchivo abro productos.csv con ifstream, me salto la primera línea (el encabezado) y después leo cada línea separándola por comas con stringstream y getline. El id, precio y stock los convierto a int con stoi, creo el Producto y lo inserto en el árbol.

Si una línea viene mal, stoi marca error, entonces lo pongo en un try/catch para saltarme esa línea y que el resto sí se cargue.

#### Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta.

Para guardar uso la función guardarArchivo (main.cpp, línea 80). Abro productos.csv con ofstream y primero reviso que se haya abierto, si no aviso que no se pudo guardar. Luego escribo el encabezado y recorro el árbol con inorden escribiendo cada producto en una línea separado por comas. Es el mismo formato que leo en cargarArchivo, entonces lo que guardo se vuelve a cargar la siguiente vez que abro el programa. Se usa en la opción 8 y al salir si hay cambios sin guardar.

Para que el archivo no se rompa, al agregar un producto no se aceptan comas en el nombre ni en la categoría, y el precio y el stock tienen que ser números.

También escribo el archivo reporte.txt con la función generarReporte (main.cpp, línea 97), que se usa en la opción 9. Ahí guardo el resumen del inventario y los productos con poco stock, ordenados de menor a mayor con merge sort para que salga primero lo más urgente.

#### Dónde está en el código

Los productos se cargan en cargarArchivo (main.cpp, línea 45) y se insertan con insertar (avl.h, línea 111).

Para consultar uso buscar (avl.h, línea 119) en las opciones 4, 5 y 7, y el inorden (avl.h, línea 138) para mostrar, guardar y hacer el reporte.

El balanceo está en balancear (avl.h, línea 46) y el merge sort en sorts.h, que se usa en main.cpp en las líneas 114, 162 y 167.

Guardar está en guardarArchivo (main.cpp, línea 80) y el reporte en generarReporte (main.cpp, línea 97).

### SEG0701: Cultura digital

#### El producto entregado genera valor para un usuario final y se ejecuta sin errores.

El programa le sirve a alguien que tiene una tienda como FYNIX para llevar su inventario sin perderlo al cerrar el programa, encontrar rápido un producto, ver qué tiene menos piezas y con el reporte saber cuánto vale su inventario y qué tiene que resurtir.

Lo probé con datos que no son válidos (letras en el precio, nombres con comas, líneas mal escritas en el csv) y el programa no se traba ni se cierra.

## Objetivo del proyecto

El objetivo principal es desarrollar un sistema que permita organizar y consultar de manera eficiente la información de los productos de FYNIX, aplicando estructuras de datos, algoritmos de ordenamiento y búsqueda, análisis de complejidad y buenas prácticas de programación.

El proyecto busca que la información del catálogo pueda ser consultada y organizada de diferentes maneras, facilitando su manejo conforme aumente la cantidad de productos.
