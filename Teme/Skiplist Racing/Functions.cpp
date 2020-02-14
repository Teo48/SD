// Copyright Teodor Matei 313 - CA
#include "./Functions.h"
#include "./Racer.h"

bool compareWithTime(Racer r1, Racer r2) {
	if (r1.getTime() == r2.getTime()) {
		return r1.getPrevRank() < r2.getPrevRank();
	}

	return r1.getTime() < r2.getTime();
}

bool compareWithId(Racer r1, Racer r2) {
	return r1.getId() < r2.getId();
}

bool compareWithPoints(Racer r1, Racer r2) {
	if (r1.getPoints() == r2.getPoints()) {
		return r1.getId() < r2.getId();
	}

	return r1.getPoints() > r2.getPoints();
}
