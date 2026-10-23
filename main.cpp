// main.cpp
// Proyecto Fynix - Avance 2
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

        Producto p(stoi(id), nombre, categoria, stoi(precio), stoi(stock));
        inventario.insertar(p);
        if (p.getId() >= siguienteId) siguienteId = p.getId() + 1;
    }
    archivo.close();
}

// Guarda el inventario en el archivo. O(n)
void guardarArchivo(AVL &inventario) {
    ofstream archivo("productos.csv");
    archivo << "id,nombre,categoria,precio,stock" << endl;
    for (Producto p : inventario.inorden()) {
        archivo << p.getId() << "," << p.getNombre() << "," << p.getCategoria() << ","
                << p.getPrecio() << "," << p.getStock() << endl;
    }
    archivo.close();
    cout << "Inventario guardado." << endl;
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
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }
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
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            Producto *p = inventario.buscar(nombre);
            if (p != nullptr) p->mostrar();
            else cout << "No se encontro el producto." << endl;
        }
        else if (opcion == 5) {
            string categoria;
            int precio, stock;
            cin.ignore();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Categoria: ";
            getline(cin, categoria);
            cout << "Precio: ";
            cin >> precio;
            cout << "Stock: ";
            cin >> stock;

            if (inventario.insertar(Producto(siguienteId, nombre, categoria, precio, stock))) {
                cout << "Producto agregado." << endl;
                siguienteId++;
            }
            else cout << "Ese producto ya existe." << endl;
        }
        else if (opcion == 6) {
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            if (inventario.eliminar(nombre)) cout << "Producto eliminado." << endl;
            else cout << "No se encontro el producto." << endl;
        }
        else if (opcion == 7) {
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            Producto *p = inventario.buscar(nombre);
            if (p != nullptr) {
                int stock;
                cout << "Nuevo stock: ";
                cin >> stock;
                p->setStock(stock);
                cout << "Stock actualizado." << endl;
            }
            else cout << "No se encontro el producto." << endl;
        }
        else if (opcion == 8) {
            guardarArchivo(inventario);
        }
        else if (opcion == 0) {
            cout << "Fin del programa.\n";
        }
        else {
            cout << "Selecciona una opcion valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
