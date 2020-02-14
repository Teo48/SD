// Copyright Teodor Matei 313 CA - 2019
#include <string>
#include "./Driver.h"

Driver::Driver() {
	this->rating = 0;
	this->distance = 0;
	this->nr_races = 0;
	this->status = true;
}

Driver& Driver::operator=(const Driver& d) {
	this->rating = d.rating;
	this->distance = d.distance;
	this->nr_races = d.nr_races;
	this->status = d.status;
	this->position = d.position;
	this->name = d.name;

	return *this;
}

void Driver::setRating(float rating) {
	this->rating = rating;
}

void Driver::setDistance(int distance) {
	this->distance = distance;
}

void Driver::setNrRaces(int nr_races) {
	this->nr_races = nr_races;
}

void Driver::setStatus(bool status) {
	this->status = status;
}

void Driver::setPosition(int position) {
	this->position = position;
}

void Driver::setName(std::string name) {
	this->name = name;
}

float Driver::getRating() {
	return this->rating;
}

int Driver::getDistance() {
	return this->distance;
}

int Driver::getNrRaces() {
	return this->nr_races;
}

int Driver::getStatus() {
	return this->status;
}

int Driver::getPosition() {
	return this->position;
}

std::string Driver::getName() {
	return this->name;
}

bool Driver::operator>(const Driver& d) {
	if (this->rating > d.rating) {
		return true;
	} else if (this->rating == d.rating) {
		if (this->name < d.name) {
		return true;
		}
	}
	return false;
}

bool Driver::operator<(const Driver& d) {
	if (this->rating > d.rating) {
		return true;
	} else if (this->rating == d.rating) {
		return this->name < d.name;
	}
	return false;
}
