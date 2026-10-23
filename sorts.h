// sorts.h
// Samuel Estrella Martinez A01714991
// Merge Sort: O(n log n) en todos los casos

#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include "producto.h"

// criterio 1 = precio, 2 = stock
bool esMenor(const Producto &a, const Producto &b, int criterio) {
    if (criterio == 1) return a.getPrecio() < b.getPrecio();
    return a.getStock() < b.getStock();
}

void mergeArray(vector<Producto> &A, vector<Producto> &B, int low, int mid, int high, int criterio) {
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (esMenor(A[j], A[i], criterio)) B[k++] = A[j++];
        else B[k++] = A[i++];
    }
    while (i <= mid) B[k++] = A[i++];
    while (j <= high) B[k++] = A[j++];

    for (int x = low; x <= high; x++) A[x] = B[x];
}

void mergeSplit(vector<Producto> &A, vector<Producto> &B, int low, int high, int criterio) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSplit(A, B, low, mid, criterio);
        mergeSplit(A, B, mid + 1, high, criterio);
        mergeArray(A, B, low, mid, high, criterio);
    }
}

void mergeSort(vector<Producto> &v, int criterio) {
    if (v.size() < 2) return;
    vector<Producto> tmp(v.size());
    mergeSplit(v, tmp, 0, v.size() - 1, criterio);
}

#endif
