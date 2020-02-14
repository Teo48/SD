// Copyright Teodor Matei - 313 CA
#include <bits/stdc++.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "SkipList.h"
#include "Racer.h"
#include "Functions.h"

#define FAIR_COIN_FLIP 0.5
#define maxLevel (int) (log2(nrRacers))

/*
	Functie ce imi initializeaza vectorul de playeri de la inceputul jocului.
	Initial, toti vor avea timpul, punctajul si rank-ul la print egal cu 0.
	ID-urile vor fi asignate in ordine crescatoare de la 1 la numarul de 
	jucatori, la fel si rank-ul din timpul cursei. 
*/

void initializeRacers(Racer* racers, int nrRacers) {
	for (int i = 0 ; i < nrRacers ; ++i) {
		racers[i].setId(i + 1);
		racers[i].setPoints(0);
		racers[i].setPrevRank(i + 1);
		racers[i].setPrintRank(0);
		racers[i].setTime(0);
	}
}

/*
  	Functie ce imi citeste datele necesare desfasurarii jocului.
  	Imi creez un vector de tipul Racer, il initializez, modific
  	continutul in urma fiecarei curse, introduc in SkipList obiectele
  	de tip Racer(Am supraincarcat operatorii de comparare si asftel,
  	SkipList-ul imi va introduce Racerii in ordine descrescatoare a 
  	punctajelor pentru a realiza clasamentul mai usor. O(log nrRacers))
*/

void readData() {
	srand((unsigned)time(NULL));
	std::ifstream fileIn;
	fileIn.open("races.in");
	std::ifstream& in = fileIn;

	std::ofstream fileOut;
	fileOut.open("races.out");
	std::ofstream& out = fileOut;

	std::string input;
	Racer* racers;
	int nrRacers, nrRaces, nrPrints;
	in >> nrRacers >> nrRaces >> nrPrints;

	std::string::size_type sz;

	racers = new Racer[nrRacers];
	Racer header = header.setHeader(header);
	initializeRacers(racers, nrRacers);
	for (int i = 0 ; i < nrRaces + nrPrints ; ++i) {
		in >> input;
		if (input == "print") {
			SkipList<Racer> skipL(header, maxLevel, FAIR_COIN_FLIP);
			for (int i = 0 ; i < nrRacers ; ++i) {
				skipL.insert(racers[i]);
				racers[i].setPrintRank(i + 1);
			}

			SkipNode<Racer>* node = skipL.getHeader();
			node = node->forward[0];

			while (node) {
				out << node->key.getId() << " " << node->key.getPoints() << " ";
				node->key.getPrintRank() > 0 ? out << node->key.getPrintRank() -
					node->key.getPrevRank() : out << 0;
				node = node->forward[0];
				out << '\n';
			}

		} else {
			int nrParticipants = 0;
			std::sort(racers, racers + nrRacers, compareWithId);
			racers[0].setTime(stoi(input, &sz));
			if (racers[0].getTime()) {
				++nrParticipants;
			}
			for (int i = 1 ; i < nrRacers ; ++i) {
				in >> input;
				racers[i].setTime(stoi(input, &sz));
				if (racers[i].getTime()) {
					++nrParticipants;
				}
			}

			int nrPoints = nrParticipants / 2;
			std::sort(racers, racers + nrRacers, compareWithTime);
			for (int i = 0 ; i < nrRacers ; ++i) {
				if (racers[i].getTime()) {
					racers[i].setPoints(racers[i].getPoints() + nrPoints);
					--nrPoints;

					if (nrPoints == 0 && nrParticipants % 2 == 0) {
						--nrPoints;
					}
				}
			}

			std::sort(racers, racers + nrRacers, compareWithPoints);
			for (int i = 0 ; i < nrRacers; ++i) {
				racers[i].setPrevRank(i + 1);
			}
		}
	}
	fileIn.close();
	fileOut.close();
	delete [] racers;
}


int main() {
	readData();
	return 0;
}
