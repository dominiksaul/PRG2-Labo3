#include "bateau.h"

#define SIZE 13

unsigned verifierTaxe(Bateau *bateau) {
   unsigned taxe = 0;
   switch (bateau->type) {
      case VOILIER:
         taxe = TAXE_BASE_VOILIER;
         if (TAXE_SPEC_VOILIER_LIMITSURFACE < bateau->surfaceVoilureM2) {
            taxe += TAXE_SPEC_VOILIER;
         }
         break;
      case PECHE:
         taxe = TAXE_BASE_MOTEUR;
         if (TAXE_SPEC_PECHE_LIMITTONNES < bateau->maxTonnesDePoisson) {
            taxe += TAXE_SPEC_PECHE;
         }
         break;
      case PLAISANCE:
         taxe = TAXE_BASE_MOTEUR;
         if (TAXE_SPEC_PLAISANCE_LIMITPUISSANCE > bateau->puissanceMoteurCV) {
            taxe += TAXE_SPEC_PLAISANCE;
         } else {
            taxe += TAXE_SPEC_PLAISANCE_PARLONGEUR * bateau->longeurBateauM2;
         }
         break;
   }
   return taxe;
}

char *verifierBateauTypeName(Bateau *bateau) {
   switch (bateau->type) {
      case VOILIER:
         return "Voilier";
      case PECHE:
         return "Peche";
      case PLAISANCE:
         return "Plaisance";
   }
}

void afficherBateau(Bateau *bateau) {
   printf("%-*s ", SIZE, bateau->nomBateau);
   printf("%*s ", SIZE, verifierBateauTypeName(bateau));
   printf("%*d ", SIZE, verifierTaxe(bateau));
   switch (bateau->type) {
      case VOILIER:
         printf("%*d m2 ", SIZE - 3, bateau->surfaceVoilureM2);
         break;
      case PECHE:
         printf("%*s ", SIZE, "");
         printf("%*d CV ", SIZE - 3, bateau->puissanceMoteurCV);
         printf("%*d T ", SIZE - 2, bateau->maxTonnesDePoisson);
         break;
      case PLAISANCE:
         printf("%*s ", SIZE, "");
         printf("%*d CV ", SIZE - 3, bateau->puissanceMoteurCV);
         printf("%*s ", SIZE, "");
         printf("%*d m ", SIZE - 3, bateau->longeurBateauM2);
         printf("%*s ", SIZE, bateau->nomProprietaire);
         break;
   }
   printf("\n");
}

void afficherBateaux(Bateau *port[], size_t taille) {
   printf("%-*s ", SIZE, "Nom");
   printf("%*s ", SIZE, "Type");
   printf("%*s ", SIZE, "Taxe");
   printf("%*s ", SIZE, "Voilure");
   printf("%*s ", SIZE, "Moteur");
   printf("%*s ", SIZE, "Max Poisson");
   printf("%*s ", SIZE, "Longeur");
   printf("%*s ", SIZE, "Proprietaire");
   printf("\n");
   for (size_t i = 0; i <= taille; ++i) {
      if (port[i] == NULL) continue;
      afficherBateau(port[i]);
   }
}

void afficherStatistiques(Bateau *port[]) {

}

Bateau *creerVoilier(char *nomBateau, uint16_t surfaceVoilureM2) {
   Bateau *temp = (Bateau *) calloc(1, sizeof(Bateau));
   temp->nomBateau = nomBateau;
   temp->type = VOILIER;
   temp->surfaceVoilureM2 = surfaceVoilureM2;
}

Bateau *creerPeche(char *nomBateau, uint16_t puissanceMoteurCV, uint8_t maxTonnesDePoisson) {
   Bateau *temp = (Bateau *) calloc(1, sizeof(Bateau));
   temp->nomBateau = nomBateau;
   temp->type = PECHE;
   temp->puissanceMoteurCV = puissanceMoteurCV;
   temp->maxTonnesDePoisson = maxTonnesDePoisson;
}

Bateau *creerPlaisance(char *nomBateau, uint16_t puissanceMoteurCV, uint8_t longeurBateauM2, char *nomProprietaire) {
   Bateau *temp = (Bateau *) calloc(1, sizeof(Bateau));
   temp->nomBateau = nomBateau;
   temp->type = PLAISANCE;
   temp->puissanceMoteurCV = puissanceMoteurCV;
   temp->longeurBateauM2 = longeurBateauM2;
   temp->nomProprietaire = nomProprietaire;
}
