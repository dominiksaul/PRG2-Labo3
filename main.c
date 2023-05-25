#include "bateau.h"

int main() {
   Bateau* port[] = {
      creerVoilier("Aterix", 40),
      creerVoilier("Bart", 250),
      creerPeche("Maggie", 15, 20),
      creerPeche("Obelix", 56, 45),
      creerPlaisance("Homer", 50, 30, "Marge"),
      creerPlaisance("Apu", 120, 50, "Femme Apu")
   };
   size_t taille = sizeof(port) / sizeof(Bateau*);

   afficherBateaux(port, taille);

   //afficherStatistiques(port, taille);

   return 0;
}
