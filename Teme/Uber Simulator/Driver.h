// Copyright Teodor Matei 313 CA - 2019
#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>

class Driver{
 private:
	float rating;
	int distance;
	int nr_races;
	bool status;
	int position;
	std::string name;

 public:
 	/*
		Constructor default, copy-assignement, getteri si setteri aferenti.
		bool operator< -> intoarce true daca rating-ul instantei curente este
		mai mic decat ratingul lui d, daca rating-ul este egal intoarce true
		daca numele instantei curente este mai mic d.p.v lexico-grafic decat
		cel al lui d.

		Analog bool operator > cu conditia ca rating-ul instantei curente sa 
		fie mai mare decat ratingul lui d.
 	*/
	Driver();
	Driver& operator=(const Driver& d);
	void setRating(float rating);
	void setDistance(int distance);
	void setNrRaces(int nr_races);
	void setStatus(bool status);
	void setPosition(int position);
	void setName(std::string name);
	float getRating();
	int getDistance();
	int getNrRaces();
	int getStatus();
	int getPosition();
	std::string getName();
	bool operator>(const Driver& d);
	bool operator<(const Driver& d);
};

#endif  // DRIVER_H_
