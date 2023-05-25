#ifndef BATEAU_H
#define BATEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TAX_BASE_VOILIER 50
#define TAX_BASE_MOTEUR 100
#define TAX_SPEC_VOILIER 25
#define TAX_SPEC_VOILIER_LIMITSURFACE 200
#define TAX_SPEC_PECHE 100
#define TAX_SPEC_PECHE_LIMITTONNES 20
#define TAX_SPEC_PLAISANCE 50
#define TAX_SPEC_PLAISANCE_LIMITPUISSANCE 100
#define TAX_SPEC_PLAISANCE_MULTIPLYLONGEUR 15

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
   Categorie categorie;
} Bateau;

unsigned verifierTaxe(Bateau* bateau);
void afficherBateau(Bateau* bateau);
void afficherBateaux(Bateau* port[]);
void afficherStatistiques(Bateau* port[]);

Bateau* creerVoilier(char* nomBateau, uint16_t surfaceVoilureM2);
Bateau* creerPeche(char* nomBateau, uint16_t puissanceMoteurCV, uint8_t maxTonnesDePoisson);
Bateau* creerPlaisance(char* nomBateau, uint16_t puissanceMoteurCV, uint8_t longeurBateauM2, char* nomProprietaire);


#endif