//
// Created by diana.laurenti on 27.05.2023.
//
#include "bateau_diana.h"

int main() {
	Bateau b1 = voilier("Carlo", 250);
	Bateau b2 = peche("Gigi",100,50);
	Bateau b3 = plaisance("Mary", 100, "Mary Stuard", 60);
	Bateau b4 = voilier("Marina", 80);
	Bateau b5 = peche("Seagull",40,15);
	Bateau b6 = plaisance("Thalasso", 80, "Ariel Marinovic", 60);

	Bateau bateaux[] = {b1,b2,b3, b4, b5, b6};
	afficherBateaux(bateaux,6);
	afficherStatistiques(bateaux, 6);

	return 0;
}
