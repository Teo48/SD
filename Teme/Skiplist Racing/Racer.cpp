// Copyright Teodor Matei - 313 CA
#include <climits>
#include "./Racer.h"

Racer::Racer() {
}

void Racer::setId(int id) {
	this->id = id;
}

void Racer::setTime(int time) {
	this->time = time;
}

void Racer::setPoints(int points) {
	this->points = points;
}

void Racer::setPrintRank(int printRank) {
	this->printRank = printRank;
}

void Racer::setPrevRank(int prevRank) {
	this->prevRank = prevRank;
}

Racer& Racer::setHeader(Racer& r) {
	r.setId(INT_MAX);
	r.setTime(INT_MAX);
	r.setPoints(INT_MAX);
	r.setPrevRank(INT_MAX);
	r.setPrintRank(INT_MAX);

	return r;
}

int Racer::getId() {
	return this->id;
}

int Racer::getTime() {
	return this->time;
}

int Racer::getPoints() {
	return this->points;
}

int Racer::getPrintRank() {
	return this->printRank;
}

int Racer::getPrevRank() {
	return this->prevRank;
}

bool Racer::operator<(const Racer& r) {
	if (this->points == r.points) {
		return this->id < r.id;
	}

	return this->points < r.points;
}

bool Racer::operator<=(const Racer& r) {
	if (this->points == r.points) {
		return this->id < r.id;
	}

	return this->points <= r.points;
}

bool Racer::operator!=(const Racer& r) {
	return this->id != r.id;
}

bool Racer::operator>(const Racer& r) {
	if (this->points == r.points) {
		return this->id < r.id;
	}

	return this->points > r.points;
}

bool Racer::operator>=(const Racer& r) {
	if (this->points == r.points) {
		return this->id < r.id;
	}

	return this->points >= r.points;
}

Racer& Racer::operator=(const Racer& r) {
	this->id = r.id;
	this->points = r.points;
	this->time = r.time;
	this->printRank = r.printRank;
	this->prevRank = r.prevRank;
	return *this;
}

Racer& Racer::operator=(const int x) {
	this->id = x;
	this->points = x;
	this->time = x;
	this->printRank = x;
	this->prevRank = x;
	return *this;
}

bool Racer::operator==(const Racer& r) {
	return (this->id == r.id);
}

std::ostream& operator<<(std::ostream& out, const Racer& r) {
	std::cout << r.id;
	return out;
}

