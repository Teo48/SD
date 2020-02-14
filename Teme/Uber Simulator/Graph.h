// Copyright Teodor Matei 313 CA - 2019
#ifndef GRAPH_H_
#define	GRAPH_H_

#include <list>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include "Driver.h"

template <typename T>
class Graph {
 private:
	int size;
	std::list<T> *adj;

 public:
 	/*
 	isPath intoarce true daca exista drum de la src la dest.
 	minDistance intoarce distanta minima de la src la dest.
 	minDistanceNode intoarce vectorul de distante de la src la toti vecinii sai.
 	check imi intoarce -1 daca nu exista soferi disponibili, -2 daca nu exista
 	nicio destinatie la care soferul poate sa ajunga, respectiv pozitia soferului
 	daca nu s-au returnat cazurile anterioare.
 	*/
	explicit Graph(int size);
	~Graph();
	void addEdge(T src, T dest);
	void removeEdge(T src, T dest);
	bool hasEdge(T src, T dest);
	bool isPath(T src, T dest);
	int minDistance(T src, T dest);
	std::vector<T> minDistanceNode(T src);
	int check(T src, T dest, std::vector<std::vector<T>> distances,
		Driver drivers[], int nr_drivers,
		int rating);
};

#endif  // GRAPH_H_
