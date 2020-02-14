// Copyright Teodor Matei 313 - CA
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "Racer.h"

/*
	compareWithTime() -> returneaza true in cazul in care timpul lui r1
		este mai mic decat cel al lui r2. In cazul in care r1 si r2 au
		timpi egali se returneaza true in cazul in care r1 a avut o pozitie
		mai buna in clasamentul cursei anterioare decat r2.

	compareWithId() -> returneaza true daca id-ul lui r1 este mai mic decat
		cel al lui r2.

	compareWithPoints() -> returneaza true daca punctajul lui r1 este mai mare
		decat punctajul lui r2. In cazul in care r1 si r2 au punctaje egale
		se returneaza true daca id-ul lui r1 este mai mic decat id-ul lui r2.
*/

bool compareWithTime(Racer r1, Racer r2);
bool compareWithId(Racer r1, Racer r2);
bool compareWithPoints(Racer r1, Racer r2);

#endif  // FUNCTIONS_H_
