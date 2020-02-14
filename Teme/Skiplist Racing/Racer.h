// Copyright Teodor Matei - 313 CA
#ifndef RACER_H_
#define RACER_H_

#include <iostream>
/*
	Racer() -> constructorul default.
	**setterii si getteri aferenti**
	setHeader() -> initializeaza toate campurile unui Racer cu INT_MAX definit
		in biblioteca <limits>
	operator< -> returneaza true daca punctajul instantei curente este mai mic
		decat punctajul lui r. In cazul in care punctajele doua sunt egale se
		returneaza true daca id-ul instantei curente esti mai mic decat id-ul
		lui r.
	operator<= -> idem, doar ca inegalitatea nu mai este stricta.
	operator> returneaza true daca punctajul instantei curente este mai mare
		decat punctajul lui r. In cazul in care punctajele doua sunt egale se
		returneaza true daca id-ul instantei curente esti mai mic decat id-ul
		lui r.
	operator>= -> idem, doar ca inegalitatea nu mai este stricta.
	Racer& operator=(const Racer& r) -> copy-assignement
	Racer& operator=(const int x) -> seteaza toate campurile instantei curente
		cu valorea x.
	operator== -> returneaza true daca id-ul instantei curente este egal cu
		id-ul lui r.
	operator<< -> afiseaza id-ul lui r.
*/
class Racer {
 private:
	int id, time, points;
	int printRank, prevRank;

 public:
	Racer();
	void setId(int id);
	void setTime(int time);
	void setPoints(int points);
	void setPrintRank(int printRank);
	void setPrevRank(int prevRank);
	Racer& setHeader(Racer& r);
	int getId();
	int getTime();
	int getPoints();
	int getPrintRank();
	int getPrevRank();
	bool operator<(const Racer& r);
	bool operator<=(const Racer& r);
	bool operator!=(const Racer& r);
	bool operator>(const Racer& r);
	bool operator>=(const Racer& r);
	Racer& operator=(const Racer& r);
	Racer& operator=(const int x);
	bool operator==(const Racer& r);
	friend std::ostream& operator<< (std::ostream& out, const Racer& r);
};

#endif  //  RACER_H_
