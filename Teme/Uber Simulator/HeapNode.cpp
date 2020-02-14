// Copyright Teodor Matei 313 CA - 2019
#include <string>
#include "./HeapNode.h"

template <typename T>
HeapNode<T>::HeapNode() {
}

template <typename T>
HeapNode<T>::HeapNode(T data, std::string name) {
	this->data = data;
	this->name = name;
}

template <typename T>
bool HeapNode<T>::operator<(const HeapNode& h) {
	if (this->data < h.data) {
		return true;
	} else if (this->data == h.data) {
		return this->name > h.name;
	}

	return false;
}
template <typename T>
bool HeapNode<T>::operator>(const HeapNode& h) {
	if (this->data > h.data) {
		return false;
	} else if (this->data == h.data) {
		return this->name < h.name;
	}

	return false;
}

template <typename T>
bool HeapNode<T>::operator==(const HeapNode& h) {
	return this->name == h.name;
}

template class HeapNode<int>;
template class HeapNode<float>;
