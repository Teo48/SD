// Copyright 2019 SD_Homework_Team

#ifndef SOLVER_H_
#define SOLVER_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Graph.h"
#include "Hashtable.h"
#include "Heap.h"
#include "HeapNode.h"

#define MAXDRIVES 160
#define MAXNODES 500

class solver {
	public:
		Driver drivers[MAXDRIVES];
		int nr_drivers = 0;
		Graph<int> graph = Graph<int>(MAXNODES);
		Hashtable<std::string, int> hashtable = Hashtable<std::string, int>(MAXNODES);
		std::vector<std::vector<int>> distances =
			std::vector<std::vector<int>>(MAXNODES, std::vector<int>(MAXNODES));
		int nr_nodes;
		std::string road[MAXNODES];
		/*
			Citesc strazile, imi creeze un hashtable in care le adaug, 
			creeze graful si apoi verific daca este drum intre intersectii.
		*/

		void task1_solver(std::ifstream& fin, std::ofstream& fout) {
			int n, m, node_src, node_dest;
			std::string src, dest;
			fin >> n >> m;
			nr_nodes = n;

			for (int i = 0 ; i < n ; ++i) {
				fin >> src;
				hashtable.put(src, i);
				road[i] = src;
			}

			for (int i = 0 ; i < m ; ++i) {
				fin >> src >> dest;
				node_src = hashtable.get(src);
				node_dest = hashtable.get(dest);

				graph.addEdge(node_src, node_dest);
			}

			fin >> n;

			for (int i = 0 ; i < n ; ++i) {
				fin >> src >> dest;
				node_src = hashtable.get(src);
				node_dest = hashtable.get(dest);

				if (graph.isPath(node_src, node_dest) || node_src == node_dest) {
					fout << "y" << '\n';
				} else {
					fout << "n" << '\n';
				}
			}
		}

		/*
			Citesc intersectiile primite ca input, calculez distanta minima
			dintre ele si afisez in functie de conditii.
		*/
		void task2_solver(std::ifstream& fin, std::ofstream& fout) {
			int n, min_dist, node_src, node_dest;
			std::string src, dest;
			fin >> n;

			for (int i = 0 ; i < n ; ++i) {
				fin >> src >> dest;
				node_src = hashtable.get(src);
				node_dest = hashtable.get(dest);
				min_dist = graph.minDistance(node_src, node_dest);

				min_dist > 0 ? fout << min_dist << '\n' : node_src == node_dest
					? fout << 0 << '\n' : fout << -1 << '\n';
			}
		}

		/*
			Citesc comanda si in functie de instructiunea primita fac modificari
			in harta initiala obtinand noua harta pe care o voi folosi la task 4
			Tot aici, imi precalculez in matricea distances distantele intre
			toate nodurile pentru a le putea folosi mai departe.
		*/

		void task3_solver(std::ifstream& fin, std::ofstream& fout) {
			int n, node_src, node_dest, node_aux, query_type, min_dist;
			std::string query, src, dest, aux;
			fin >> n;

			for (int i = 0 ; i < n ; ++i) {
				fin >> query;

				if (query == "c") {
					fin >> src >> dest >> query_type;
					node_src = hashtable.get(src);
					node_dest = hashtable.get(dest);
					switch(query_type) {
						case 0:
							if (!graph.hasEdge(node_src, node_dest)) {
								graph.addEdge(node_src, node_dest);
							}
							break;
						case 1:
							if (graph.hasEdge(node_src, node_dest)) {
								graph.removeEdge(node_src, node_dest);
							}

							if (graph.hasEdge(node_dest, node_src)) {
								graph.removeEdge(node_dest, node_src);
							}
							break;
						case 2:
							if (!graph.hasEdge(node_src, node_dest) &&
								!graph.hasEdge(node_dest, node_src)) {
								graph.addEdge(node_src, node_dest);
								graph.addEdge(node_dest, node_src);
							} else if (graph.hasEdge(node_src, node_dest) &&
								!graph.hasEdge(node_dest, node_src)) {
								graph.addEdge(node_dest, node_src);
							} else if (!graph.hasEdge(node_src, node_dest) &&
								graph.hasEdge(node_dest, node_src)) {
								graph.addEdge(node_src, node_dest);
							}
							break;
						case 3:
							if ((graph.hasEdge(node_src, node_dest) &&
								graph.hasEdge(node_dest, node_src)) ||
									(!graph.hasEdge(node_src, node_dest) &&
										!graph.hasEdge(node_dest, node_src))) {
								break;
							} else if (graph.hasEdge(node_src, node_dest)) {
								graph.removeEdge(node_src, node_dest);
								graph.addEdge(node_dest, node_src);
							} else if (graph.hasEdge(node_dest, node_src)) {
								graph.removeEdge(node_dest, node_src);
								graph.addEdge(node_src, node_dest);
							}
						default: break;
					}
				}

				if (query == "q") {
					fin >> src >> dest >> query_type;
					node_src = hashtable.get(src);
					node_dest = hashtable.get(dest);

					switch(query_type) {
						case 0:
							if (graph.isPath(node_src, node_dest) || node_src == node_dest) {
								fout << "y" << '\n';
							} else {
								fout << "n" << '\n';
							}
							break;
						case 1:
							min_dist = graph.minDistance(node_src, node_dest);
							min_dist > 0 ? fout << min_dist << '\n' : node_src == node_dest
								? fout << 0 << '\n' : fout << -1 << '\n';
							break;
						case 2: {
							fin >> aux;
							node_aux = hashtable.get(aux);
							int min_dist_src_aux, min_dist_aux_dest;
							min_dist_src_aux = graph.minDistance(node_src, node_aux);
							min_dist_aux_dest = graph.minDistance(node_aux, node_dest);

							if ((min_dist_src_aux == 0 && node_src != node_aux) ||
								(min_dist_aux_dest == 0 && node_aux != node_dest)) {
								fout << -1 << '\n';
							} else {
								if (node_src != node_aux && node_aux != node_dest) {
									fout << min_dist_src_aux + min_dist_aux_dest << '\n';
								} else if (node_src == node_aux) {
									fout << min_dist_aux_dest << '\n';
								} else if (node_aux == node_dest) {
									fout << min_dist_src_aux << '\n';
								} else {
									fout << 0 << '\n';
								}
							}
							break;
						}
						default: break;
					}
				}
			}
			std::vector<int> temp_distance;
			for (int i = 0 ; i < nr_nodes ; ++i) {
				temp_distance = graph.minDistanceNode(i);
				for (int j = 0 ; j < nr_nodes ; ++j) {
					distances[i][j] = temp_distance[j];
				}
			}
		}

		/*
			Citesc comenzile, in cazul top, info, d, b urmez stric pasii
			din enunt.
			In cazul comenzii r ma folosesc de matricea de distante calculata
			anterior si de metoda check din "Graph.h" care imi returneaza
			-1 daca nu exista soferi, -2 daca nu exista destinatii respectiv
			pozitia soferului cautat in cadrul acestui task.

			Imi creez 3 vectori HeapNode care vor fi folositi pentru realizarea
			topurilor. La intalnirea oricari comenzi top, voi sorta vectorii
			doar daca au fost alterati anterior (un heapsort), in caz contrar 
			doar voi afisa topul.
		*/
		void task4_solver(std::ifstream& fin, std::ofstream& fout) {
			int n, node_src, node_dest, rating, nr;
			std::string query, src, dest, driver_name;
			int dist_sorted = 1, rides_sorted = 1, rating_sorted = 1;

			HeapNode<int> top_dist[160];
			HeapNode<int> top_rides[160];
			HeapNode<float> top_rating[160];
			fin >> n;
			for (int i = 0 ; i < n ; ++i) {
				fin >> query;
				int sw = 0;
				if (query == "d") {
					fin >> driver_name >> src;
					node_src = hashtable.get(src);

					for (int j = 0 ; j < nr_drivers ; ++j) {
						if (drivers[j].getName() == driver_name) {
							drivers[j].setStatus(true);
							drivers[j].setPosition(node_src);
							sw = 1;
							break;
						}
					}

					if (sw == 0) {
						drivers[nr_drivers].setName(driver_name);
						drivers[nr_drivers].setPosition(node_src);
						drivers[nr_drivers].setStatus(true);
						top_dist[nr_drivers].name = driver_name;
						top_rides[nr_drivers].name = driver_name;
						top_rating[nr_drivers].name = driver_name;
						top_dist[nr_drivers].data = 0;
						top_rides[nr_drivers].data = 0;
						top_rating[nr_drivers].data = 0.0;
						dist_sorted = 0;
						rides_sorted = 0;
						rating_sorted = 0;
						++nr_drivers;
					}

				} else if (query == "b") {
					fin >> driver_name;
					for (int j = 0 ; j < nr_drivers ; ++j) {
						if (drivers[j].getName() == driver_name) {
							drivers[j].setStatus(false);
							break;
						}
					}
				} else if (query == "r") {
					fin >> src >> dest >> rating;
					node_src = hashtable.get(src);
					node_dest = hashtable.get(dest);
					int position;
					position = graph.check(node_src, node_dest, distances,
						drivers, nr_drivers, rating);
					if (position == -1) {
						fout << "Soferi indisponibili" << '\n';
					} else if (position == -2) {
						fout << "Destinatie inaccesibila" << '\n';
					} else {
						for (int j = 0 ; j < nr_drivers; ++j) {
							if (top_dist[j].name == drivers[position].getName()) {
								top_dist[j].data = drivers[position].getDistance();
								dist_sorted = 0;
							}

							if (top_rides[j].name == drivers[position].getName()) {
								top_rides[j].data = drivers[position].getNrRaces();
								rides_sorted = 0;
							}

							if (top_rating[j].name == drivers[position].getName()) {
								top_rating[j].data = drivers[position].getRating();
								rating_sorted = 0;
							}
						}
					}
				} else if (query == "top_dist") {
					fin >> nr;
					int min_val = std::min(nr, nr_drivers);
					if (dist_sorted == 0) {
						heapSort(top_dist, nr_drivers);
						dist_sorted = 1;
					}
					for (int j = 0 ; j < min_val; ++j) {
						fout << top_dist[j].name << ":" << top_dist[j].data
							<< " ";
					}

					fout << '\n';
				} else if (query == "top_rides") {
					fin >> nr;
					int min_val = std::min(nr, nr_drivers);
					if (rides_sorted == 0) {
						heapSort(top_rides, nr_drivers);
						rides_sorted = 1;
					}
					for (int j = 0 ; j < min_val; ++j) {
						fout << top_rides[j].name << ":" << top_rides[j].data
							<< " ";
					}

					fout << '\n';
				} else if (query == "top_rating") {
					fin >> nr;
					int min_val = std::min(nr, nr_drivers);
					if (rating_sorted == 0) {
						heapSort(top_rating, nr_drivers);
						rating_sorted = 1;
					}
					for (int j = 0 ; j < min_val; ++j) {
						fout << std::fixed;
						fout << top_rating[j].name << ":" <<
							std::setprecision(3) << top_rating[j].data << " ";
					}

					fout << '\n';
				} else if (query == "info") {
					fin >> driver_name;
					for (int j = 0 ; j < nr_drivers ; ++j) {
						if (drivers[j].getName() == driver_name) {
							if (drivers[j].getStatus() == true) {
								fout << drivers[j].getName() <<": "
									<< road[drivers[j].getPosition()] << " ";
								fout << std::fixed;
								fout << std::setprecision(3) <<
									drivers[j].getRating() << " ";
								fout << drivers[j].getNrRaces() << " "
									<< drivers[j].getDistance() << " online" << '\n';
								break;
							} else {
								fout << drivers[j].getName() <<": "
									<< road[drivers[j].getPosition()] << " ";
								fout << std::fixed;
								fout << std::setprecision(3) <<
									drivers[j].getRating() << " ";
								fout << drivers[j].getNrRaces() << " "<<
									drivers[j].getDistance() << " offline" << '\n';
								break;
							}
						}
					}
				}
		}
	}
		/*
			Citesc cantitatea de combustibil pe care o are soferul,
			citesc numele soferului. Ii gasesc pozitia in vectorul drivers
			Ma folosesc de matricea de distante calculata la task3 si 
			verific ca distantele dintre pozitia curenta a soferului si
			locatiile primite sa fie mai mici sau egal decat cantitea
			de combustibil pe care o are. Daca se indeplineste conditia
			pun totul intr-un HeapNode pe care il voi sorta la final
			pentru a afisa lista ceruta.
		*/
		void task5_solver(std::ifstream& fin, std::ofstream& fout) {
			int node_end, n, nr_roads, sw;
			std::string driver_name, road_name;
			fin >> n >> driver_name;
			fin >> nr_roads;
			HeapNode<int> road_names[MAXDRIVES];
			int position;
			for (int i = 0 ; i < nr_drivers ; ++i) {
				if (drivers[i].getName() == driver_name) {
					position = drivers[i].getPosition();
					break;
				}
			}

			int k = 0;
			for (int i = 0 ; i < nr_roads ; ++i) {
				fin >> road_name;
				node_end = hashtable.get(road_name);
				sw = 0;
				for (int j = 0 ; j < k ; ++j) {
					if (road_names[j].name == road_name) {
						sw = 1;
					}
				}
				if (sw == 0 && distances[position][node_end] == 0
						&& position == node_end) {
					road_names[k].name = road_name;
					road_names[k].data = n;
					++k;
				} else if (sw == 0 && distances[position][node_end] <= n
					&& distances[position][node_end] != 0) {
						road_names[k].name = road_name;
						road_names[k].data = n - distances[position][node_end];
						++k;
				}
			}
			heapSort(road_names, k);

			for (int i = 0 ; i < k ; ++i) {
				fout << road_names[i].name << " ";
			}
		}
};
#endif  // SOLVER_H_
