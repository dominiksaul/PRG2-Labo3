#include <stdio.h>
#include "bateau.h"

int main() {
   Bateau port[] = {
      {.nomBateau = "bateau1", .categorie.voilier.surfaceVoilureM2 = 40},
      {},
      {}
   };

   // tester la fonction afficher Bateau
   afficherBateau(&port[0]);

   // tester la fonction afficher Bateaux
   afficherBateaux(&port[0]);

   // tester la fonction afficher Statistiques
   afficherStatistiques(&port[0]);

   // printf("Hello, World!\n");
   return 0;
}
