// Copyright Teodor Matei 313 CA - 2019
#ifndef HEAP_H_
#define HEAP_H_

#include "HeapNode.h"
#include <utility>

/*
	Functie pentru creearea unui heap
*/
template <typename T>
void heapify(HeapNode<T> v[], int n, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && v[left] < v[smallest]) {
        smallest = left;
	}

    if (right < n && v[right] < v[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        std::swap(v[i], v[smallest]);
        heapify(v, n, smallest);
    }
}

/*
	Functie pentru sortare
*/
template <typename T>
void heapSort(HeapNode<T> v[], int n) {
	for (int i = n / 2 - 1 ; i >= 0 ; --i) {
		heapify(v, n, i);
	}

	for (int i = n - 1 ; i >= 0 ; --i) {
		std::swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}
#endif  // HEAP_H_
