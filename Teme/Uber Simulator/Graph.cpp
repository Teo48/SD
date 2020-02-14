// Copyright Teodor Matei 313 CA - 2019
#include <list>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include "./Graph.h"

#define min_value 9999999

template <typename T>
Graph<T>::Graph(int size) {
		this->size = size;
		adj = new std::list<T>[size];
	}

template <typename T>
Graph<T>::~Graph() {
		for (int i = 0 ; i < size; ++i) {
			adj[i].clear();
		}

		delete[] adj;
	}

template <typename T>
void Graph<T>::addEdge(T src, T dest) {
		adj[src].push_back(dest);
	}

template <typename T>
void Graph<T>::removeEdge(T src, T dest) {
		for (typename std::list<T>::iterator it = adj[src].begin() ;
				it != adj[src].end() ; ++it) {
			if (*it == dest) {
				adj[src].erase(it);
				break;
			}
		}
	}

template <typename T>
bool Graph<T>::hasEdge(T src, T dest) {
		for (typename std::list<T>::iterator it = adj[src].begin() ;
				it != adj[src].end() ; ++it) {
			if (*it == dest) {
				return true;
			}
		}

		return false;
	}

template <typename T>
bool Graph<T>::isPath(T src, T dest) {
		if (src == dest) {
			return true;
		}

		std::vector<bool> visited(size, false);

		std::queue<T> Q;
		visited[src] = true;
		Q.push(src);

		while (!Q.empty()) {
			src = Q.front();
			Q.pop();

			for (typename std::list<T>::iterator it = adj[src].begin() ;
				it != adj[src].end() ; ++it) {
				if (*it == dest) {
					return true;
				}

				if (!visited[*it]) {
					visited[*it] = true;
					Q.push(*it);
				}
			}
		}
		return false;
	}

template <typename T>
int Graph<T>::minDistance(T src, T dest) {
		std::vector<bool> visited(size, false);
		std::vector<int> distance(size, 0);
		std::queue<T> Q;

		Q.push(src);
		visited[src] = true;
		if (src == dest) {
			return 0;
		}
		while (!Q.empty()) {
			int index = Q.front();
			Q.pop();

			for (typename std::list<T>::iterator it = adj[index].begin() ;
				it != adj[index].end() ; ++it) {
				if (visited[*it]) {
					continue;
				}

				distance[*it] = distance[index] + 1;
				Q.push(*it);
				visited[*it] = true;
			}
		}

		return distance[dest];
	}

template <typename T>
std::vector<T> Graph<T>::minDistanceNode(T src) {
		std::vector<bool> visited(size, false);
		std::vector<int> distance(size, 0);
		std::queue<T> Q;

		Q.push(src);
		visited[src] = true;

		while (!Q.empty()) {
			int index = Q.front();
			Q.pop();

			for (typename std::list<T>::iterator it = adj[index].begin() ;
				it != adj[index].end() ; ++it) {
				if (visited[*it]) {
					continue;
				}

				distance[*it] = distance[index] + 1;
				Q.push(*it);
				visited[*it] = true;
			}
		}

		return distance;
	}

template <typename T>
int Graph<T>::check(T src, T dest, std::vector<std::vector<T>> distances,
		Driver drivers[], int nr_drivers,
		int rating) {
		int exit_code, aux[nr_drivers], k = 0, sw = 0, min = min_value, position;
		Driver test_driver;
		test_driver.setRating(-999.9);
		if (nr_drivers == 0) {
			return exit_code = -1;
		}

		for (int i = 0 ; i < nr_drivers ; ++i) {
			int min_dist = distances[drivers[i].getPosition()][src];
			if (drivers[i].getStatus() == true) {
				if (min_dist != 0 || (min_dist == 0 &&
					drivers[i].getPosition() == src)) {
					aux[k] = i;
					++k;

					if (min_dist < min) {
						min = min_dist;
					}
				}
			}
		}

		if (k == 0) {
			return exit_code = -1;
		}

		for (int i = 0 ; i < k ; ++i) {
			if (distances[drivers[aux[i]].getPosition()][src] == min &&
				(drivers[aux[i]] < test_driver)
				&& drivers[aux[i]].getStatus() == true) {
				test_driver = drivers[aux[i]];
				position = aux[i];
			}
		}

		// Cand nu avem drum de la sursa la destinatie
		if (distances[src][dest] == 0 && src != dest) {
			for (typename std::list<T>::iterator it = adj[dest].begin() ;
				it != adj[dest].end() ; ++it) {
					if (distances[src][*it] != 0 || (distances[src][*it] == 0
							&& src == *it)) {
						min = distances[src][*it];
						dest = *it;
						sw = 1;
						break;
					}
			}

			if (sw == 0) {
				return exit_code = -2;
			} else {
				int nr = drivers[position].getNrRaces();
				++nr;
				drivers[position].setNrRaces(nr);
				nr = drivers[position].getDistance();
				nr += distances[drivers[position].getPosition()][src] + min;
				drivers[position].setDistance(nr);
				drivers[position].setPosition(dest);
				float x;
				x = ((drivers[position].getRating() *
					(drivers[position].getNrRaces() - 1) + rating)) /
					drivers[position].getNrRaces();
				drivers[position].setRating(x);

				return position;
			}
		} else if (distances[src][dest] == 0 && src == dest) {
			int nr = drivers[position].getNrRaces();
			++nr;
			drivers[position].setNrRaces(nr);
			nr = drivers[position].getDistance();
			nr += distances[drivers[position].getPosition()][dest];
			drivers[position].setDistance(nr);
			drivers[position].setPosition(dest);
			float x;
			x = (drivers[position].getRating() *
					(drivers[position].getNrRaces() - 1) + rating) /
				drivers[position].getNrRaces();
			drivers[position].setRating(x);

			return position;
		} else if (distances[src][dest] != 0 && src != dest) {
			int nr = drivers[position].getNrRaces();
			++nr;
			drivers[position].setNrRaces(nr);
			nr = drivers[position].getDistance();
			nr += distances[drivers[position].getPosition()][src] +
				distances[src][dest];
			drivers[position].setDistance(nr);
			drivers[position].setPosition(dest);
			float x;
			x = (drivers[position].getRating() *
					(drivers[position].getNrRaces() - 1) + rating) /
						drivers[position].getNrRaces();
			drivers[position].setRating(x);
		}

		return position;
	}

template class Graph<int>;
