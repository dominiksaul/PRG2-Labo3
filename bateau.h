#ifndef BATEAU_H
#define BATEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TAXE_BASE_VOILIER 50
#define TAXE_BASE_MOTEUR 100
#define TAXE_SPEC_VOILIER 25
#define TAXE_SPEC_VOILIER_LIMITSURFACE 200
#define TAXE_SPEC_PECHE 100
#define TAXE_SPEC_PECHE_LIMITTONNES 20
#define TAXE_SPEC_PLAISANCE 50
#define TAXE_SPEC_PLAISANCE_LIMITPUISSANCE 100
#define TAXE_SPEC_PLAISANCE_PARLONGEUR 15

typedef enum {
   VOILIER, PECHE, PLAISANCE
} BateauType;

typedef struct Peche {
   uint8_t maxTonnesDePoisson;
} Peche;

typedef struct Plaisance {
   uint8_t longeurBateauM2;
   char* nomProprietaire;
} Plaisance;

typedef union SousCategorie {
   Peche peche;
   Plaisance plaisance;
} SousCategorie;

typedef struct Voilier {
   uint16_t surfaceVoilureM2;
} Voilier;

typedef struct Moteur {
   uint16_t puissanceMoteurCV;
   SousCategorie sousCategorie;
} Moteur;

typedef union Categorie {
   Voilier voilier;
   Moteur moteur;
} Categorie;

typedef struct Bateau {
   char* nomBateau;
   BateauType type;
   Categorie categorie;
} Bateau;

// Fonction pour vérifier la taxe d'un bateau
unsigned verifierTaxe(Bateau* bateau);
// Fonction pour afficher un seul bateau
void afficherBateau(Bateau* bateau);
// Fonction pour afficher les bateaux
void afficherBateaux(Bateau* port[], size_t taille);
// Fonction pour afficher les statistiques
void afficherStatistiques(Bateau* port[]);

// Fonctions pour créer les bateaux
Bateau* creerVoilier(char* nomBateau, uint16_t surfaceVoilureM2);
Bateau* creerPeche(char* nomBateau, uint16_t puissanceMoteurCV, uint8_t maxTonnesDePoisson);
Bateau* creerPlaisance(char* nomBateau, uint16_t puissanceMoteurCV, uint8_t longeurBateauM2, char* nomProprietaire);


#endif