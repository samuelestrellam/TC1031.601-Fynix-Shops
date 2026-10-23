// avl.h
// Samuel Estrella Martinez A01714991
// Arbol AVL ordenado por nombre del producto

#ifndef AVL_H
#define AVL_H

#include <vector>
#include "producto.h"

struct Nodo {
    Producto dato;
    Nodo *izq, *der;
    int altura;
    Nodo(Producto p) : dato(p), izq(nullptr), der(nullptr), altura(1) {}
};

class AVL {
private:
    Nodo *raiz;
    int tam;

    int altura(Nodo *n) { return n ? n->altura : 0; }
    int balance(Nodo *n) { return n ? altura(n->izq) - altura(n->der) : 0; }
    void actualizar(Nodo *n) { n->altura = 1 + max(altura(n->izq), altura(n->der)); }

    Nodo* rotarDer(Nodo *y) {
        Nodo *x = y->izq;
        y->izq = x->der;
        x->der = y;
        actualizar(y);
        actualizar(x);
        return x;
    }

    Nodo* rotarIzq(Nodo *x) {
        Nodo *y = x->der;
        x->der = y->izq;
        y->izq = x;
        actualizar(x);
        actualizar(y);
        return y;
    }

    Nodo* balancear(Nodo *n) {
        actualizar(n);
        if (balance(n) > 1) {
            if (balance(n->izq) < 0) n->izq = rotarIzq(n->izq);
            return rotarDer(n);
        }
        if (balance(n) < -1) {
            if (balance(n->der) > 0) n->der = rotarDer(n->der);
            return rotarIzq(n);
        }
        return n;
    }

    Nodo* insertar(Nodo *n, Producto p, bool &ok) {
        if (n == nullptr) {
            ok = true;
            return new Nodo(p);
        }
        if (p.getNombre() < n->dato.getNombre()) n->izq = insertar(n->izq, p, ok);
        else if (p.getNombre() > n->dato.getNombre()) n->der = insertar(n->der, p, ok);
        else return n; // ya existe
        return balancear(n);
    }

    Nodo* eliminar(Nodo *n, string nombre, bool &ok) {
        if (n == nullptr) return nullptr;

        if (nombre < n->dato.getNombre()) n->izq = eliminar(n->izq, nombre, ok);
        else if (nombre > n->dato.getNombre()) n->der = eliminar(n->der, nombre, ok);
        else {
            ok = true;
            if (n->izq == nullptr || n->der == nullptr) {
                Nodo *hijo = n->izq ? n->izq : n->der;
                delete n;
                return hijo;
            }
            Nodo *suc = n->der;
            while (suc->izq != nullptr) suc = suc->izq;
            n->dato = suc->dato;
            n->der = eliminar(n->der, suc->dato.getNombre(), ok);
        }
        return balancear(n);
    }

    void inorden(Nodo *n, vector<Producto> &v) {
        if (n == nullptr) return;
        inorden(n->izq, v);
        v.push_back(n->dato);
        inorden(n->der, v);
    }

    void borrarTodo(Nodo *n) {
        if (n == nullptr) return;
        borrarTodo(n->izq);
        borrarTodo(n->der);
        delete n;
    }

public:
    AVL() : raiz(nullptr), tam(0) {}
    ~AVL() { borrarTodo(raiz); }

    int size() { return tam; }

    // O(log n)
    bool insertar(Producto p) {
        bool ok = false;
        raiz = insertar(raiz, p, ok);
        if (ok) tam++;
        return ok;
    }

    // O(log n)
    Producto* buscar(string nombre) {
        Nodo *actual = raiz;
        while (actual != nullptr) {
            if (nombre == actual->dato.getNombre()) return &actual->dato;
            if (nombre < actual->dato.getNombre()) actual = actual->izq;
            else actual = actual->der;
        }
        return nullptr;
    }

    // O(log n)
    bool eliminar(string nombre) {
        bool ok = false;
        raiz = eliminar(raiz, nombre, ok);
        if (ok) tam--;
        return ok;
    }

    // O(n)
    vector<Producto> inorden() {
        vector<Producto> v;
        inorden(raiz, v);
        return v;
    }
};

#endif
