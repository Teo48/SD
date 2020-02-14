// Copyright Teodor Matei 313 CA - 2019
#ifndef HEAPNODE_H_
#define HEAPNODE_H_

#include <string>

template <typename T>
class HeapNode {
 public:
 	/*
	  Getteri si setteri aferenti.
	  bool opertor< intoarce true daca data-ul instantei curente este mai mic
	  decat data-ul lui h, daca sunt egale intoarce true daca numele instantei
	  curente este mai mic decat numele lui h.

	  Analog operator> cu condtia de "mai mare".

	  bool operator== intoarce true daca numele instantei curente este egal cu
	  numele lui h.
 	*/
	T data;
	std::string name;
	HeapNode();
	HeapNode(T data, std::string name);
	bool operator<(const HeapNode& h);
	bool operator>(const HeapNode& h);
	bool operator==(const HeapNode& h);
};

#endif  // HEAPNODE_H_
