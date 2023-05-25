#include "bateau.h"

unsigned verifierTaxe(Bateau* bateau) {

}

void afficherBateau(Bateau* bateau) {

}

void afficherBateaux(Bateau* port[]) {

}

void afficherStatistiques(Bateau* port[]) {

}

Bateau* creerVoilier(char* nomBateau, uint16_t surfaceVoilureM2) {
   Bateau* temp = calloc(1, sizeof(Bateau));
   temp->nomBateau = nomBateau;
   temp->categorie.voilier.surfaceVoilureM2 = surfaceVoilureM2;
}

Bateau* creerPeche(char* nomBateau, uint16_t puissanceMoteurCV, uint8_t maxTonnesDePoisson) {
   Bateau* temp = calloc(1, sizeof(Bateau));
   temp->nomBateau = nomBateau;
   temp->categorie.moteur.puissanceMoteurCV = puissanceMoteurCV;
   temp->categorie.moteur.sousCategorie.peche.maxTonnesDePoisson = maxTonnesDePoisson;
}

Bateau* creerPlaisance(char* nomBateau, uint16_t puissanceMoteurCV, uint8_t longeurBateauM2, char* nomProprietaire){
   Bateau* temp = calloc(1, sizeof(Bateau));
   temp->nomBateau = nomBateau;
   temp->categorie.moteur.puissanceMoteurCV = puissanceMoteurCV;
   temp->categorie.moteur.sousCategorie.plaisance.longeurBateauM2 = longeurBateauM2;
   temp->categorie.moteur.sousCategorie.plaisance.nomProprietaire = nomProprietaire;
}
