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

   // tester la fonction afficher Bateau
   afficherBateau(port[0]);

   // tester la fonction afficher Bateaux
   afficherBateaux(port);

   // tester la fonction afficher Statistiques
   afficherStatistiques(port);

   // printf("Hello, World!\n");
   return 0;
}
