// producto.h
// Samuel Estrella Martinez A01714991

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Producto {
private:
    int id;
    string nombre;
    string categoria;
    int precio;
    int stock;

public:
    Producto() : id(0), nombre(""), categoria(""), precio(0), stock(0) {}
    Producto(int i, string n, string c, int p, int s)
        : id(i), nombre(n), categoria(c), precio(p), stock(s) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getCategoria() const { return categoria; }
    int getPrecio() const { return precio; }
    int getStock() const { return stock; }
    void setStock(int s) { stock = s; }

    void mostrar() const {
        cout << left << setw(5) << id << setw(25) << nombre << setw(15) << categoria
             << right << setw(8) << precio << setw(8) << stock << endl;
    }
};

#endif
