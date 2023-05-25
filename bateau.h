#ifndef BATEAU_H
#define BATEAU_H

#include <stdio.h>
#include <stdint.h>

#define TAX_BASE_VOILIER 50
#define TAX_BASE_MOTEUR 100
#define TAX_SPEC_VOILIER 25
#define TAX_SPEC_VOILIER_LIMIT 200
#define TAX_SPEC_PECHE 100
#define TAX_SPEC_PECHE_LIMIT 20
#define TAX_SPEC_PLAISANCE 50
#define TAX_SPEC_PLAISANCE_LIMIT 100
#define TAX_SPEC_PLAISANCE_MULTIPLY 15

typedef enum {
   VOILIER, PECHE, PLAISANCE
} BateauType;

typedef struct Peche {
   uint8_t maxTonnesDePoisson;
} Peche;

typedef struct Plaisance {
   uint8_t longeurBateauM2;
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
   char nom[50];
   Categorie categorie;
} Bateau;

Bateau* nouveauBateau()

int getTaxe(Bateau* bateau);
int getTaxeBase(Bateau* bateau);
int getTaxeSpecifique(Bateau* bateau);

#endif