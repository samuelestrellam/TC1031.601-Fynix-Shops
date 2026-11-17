// main.cpp
// Proyecto Fynix - Avance 3
// Samuel Estrella Martinez A01714991

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "producto.h"
#include "avl.h"
#include "sorts.h"

using namespace std;

int siguienteId = 1;
bool hayCambios = false;

// Pide un numero y lo vuelve a pedir si escriben letras o un negativo. O(1)
int leerNumero(string mensaje) {
    int x;
    cout << mensaje;
    while (!(cin >> x) || x < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Numero no valido, intenta otra vez: ";
    }
    cin.ignore(1000, '\n');
    return x;
}

// Pide un texto sin comas para que no se rompa el csv. O(1)
string leerTexto(string mensaje) {
    string s;
    cout << mensaje;
    getline(cin, s);
    while (s == "" || s.find(',') != string::npos) {
        cout << "No puede estar vacio ni tener comas: ";
        getline(cin, s);
    }
    return s;
}

// Lee productos.csv y los mete al AVL. O(n log n)
void cargarArchivo(AVL &inventario) {
    ifstream archivo("productos.csv");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir productos.csv" << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // encabezado

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (linea.back() == '\r') linea.pop_back();

        stringstream ss(linea);
        string id, nombre, categoria, precio, stock;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, categoria, ',');
        getline(ss, precio, ',');
        getline(ss, stock, ',');

        // si la linea viene mal stoi falla, entonces me la salto
        try {
            Producto p(stoi(id), nombre, categoria, stoi(precio), stoi(stock));
            inventario.insertar(p);
            if (p.getId() >= siguienteId) siguienteId = p.getId() + 1;
        } catch (exception &e) {
            cout << "Se salto una linea con error: " << linea << endl;
        }
    }
    archivo.close();
}

// Guarda el inventario en el archivo. O(n)
void guardarArchivo(AVL &inventario) {
    ofstream archivo("productos.csv");
    if (!archivo.is_open()) {
        cout << "No se pudo guardar el archivo." << endl;
        return;
    }
    archivo << "id,nombre,categoria,precio,stock" << endl;
    for (Producto p : inventario.inorden()) {
        archivo << p.getId() << "," << p.getNombre() << "," << p.getCategoria() << ","
                << p.getPrecio() << "," << p.getStock() << endl;
    }
    archivo.close();
    hayCambios = false;
    cout << "Inventario guardado." << endl;
}

// Crea reporte.txt con el resumen y los productos que hay que resurtir. O(n log n)
void generarReporte(AVL &inventario) {
    ofstream archivo("reporte.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo crear el reporte." << endl;
        return;
    }

    vector<Producto> todos = inventario.inorden();
    vector<Producto> resurtir;
    int unidades = 0;
    int valor = 0;

    for (Producto p : todos) {
        unidades += p.getStock();
        valor += p.getPrecio() * p.getStock();
        if (p.getStock() <= 5) resurtir.push_back(p);
    }
    mergeSort(resurtir, 2);

    archivo << "REPORTE FYNIX" << endl;
    archivo << "Productos: " << todos.size() << endl;
    archivo << "Unidades: " << unidades << endl;
    archivo << "Valor del inventario: $" << valor << endl;
    archivo << endl << "Productos con 5 piezas o menos:" << endl;
    for (Producto p : resurtir) {
        archivo << p.getNombre() << " - " << p.getStock() << " piezas" << endl;
    }
    archivo.close();
    cout << "Reporte guardado en reporte.txt" << endl;
}

void mostrarLista(vector<Producto> lista) {
    cout << left << setw(5) << "ID" << setw(25) << "Nombre" << setw(15) << "Categoria"
         << right << setw(8) << "Precio" << setw(8) << "Stock" << endl;
    for (Producto p : lista) p.mostrar();
}

int main() {
    AVL inventario;
    cargarArchivo(inventario);

    int opcion;
    string nombre;

    do {
        cout << "___________________________________\n";
        cout << "FYNIX\n";
        cout << "1. Mostrar todos los productos\n";
        cout << "2. Ordenar por precio\n";
        cout << "3. Ordenar por stock\n";
        cout << "4. Buscar producto\n";
        cout << "5. Agregar producto\n";
        cout << "6. Eliminar producto\n";
        cout << "7. Actualizar stock\n";
        cout << "8. Guardar en archivo\n";
        cout << "9. Generar reporte\n";
        cout << "0. Salir\n";
        opcion = leerNumero("Opcion: ");
        cout << "___________________________________\n";

        if (opcion == 1) {
            mostrarLista(inventario.inorden());
        }
        else if (opcion == 2) {
            vector<Producto> lista = inventario.inorden();
            mergeSort(lista, 1);
            mostrarLista(lista);
        }
        else if (opcion == 3) {
            vector<Producto> lista = inventario.inorden();
            mergeSort(lista, 2);
            mostrarLista(lista);
        }
        else if (opcion == 4) {
            nombre = leerTexto("Nombre: ");
            Producto *p = inventario.buscar(nombre);
            if (p != nullptr) p->mostrar();
            else cout << "No se encontro el producto." << endl;
        }
        else if (opcion == 5) {
            nombre = leerTexto("Nombre: ");
            if (inventario.buscar(nombre) != nullptr) {
                cout << "Ese producto ya existe." << endl;
            }
            else {
                string categoria = leerTexto("Categoria: ");
                int precio = leerNumero("Precio: ");
                int stock = leerNumero("Stock: ");
                inventario.insertar(Producto(siguienteId, nombre, categoria, precio, stock));
                siguienteId++;
                hayCambios = true;
                cout << "Producto agregado." << endl;
            }
        }
        else if (opcion == 6) {
            nombre = leerTexto("Nombre: ");
            if (inventario.eliminar(nombre)) {
                hayCambios = true;
                cout << "Producto eliminado." << endl;
            }
            else cout << "No se encontro el producto." << endl;
        }
        else if (opcion == 7) {
            nombre = leerTexto("Nombre: ");
            Producto *p = inventario.buscar(nombre);
            if (p != nullptr) {
                p->setStock(leerNumero("Nuevo stock: "));
                hayCambios = true;
                cout << "Stock actualizado." << endl;
            }
            else cout << "No se encontro el producto." << endl;
        }
        else if (opcion == 8) {
            guardarArchivo(inventario);
        }
        else if (opcion == 9) {
            generarReporte(inventario);
        }
        else if (opcion == 0) {
            if (hayCambios) {
                int r = leerNumero("Tienes cambios sin guardar. Quieres guardar? (1 = si, 0 = no): ");
                if (r == 1) guardarArchivo(inventario);
            }
            cout << "Fin del programa.\n";
        }
        else {
            cout << "Selecciona una opcion valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
