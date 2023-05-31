/*
 -----------------------------------------------------------------------------------
 Nom du fichier : bateau.h
 Auteur(s)      : Diana Laurenti, Glodi Domingos, Dominik Saul
 Date creation  : 25.05.2023
 Description    : Librairie permettant la gestion des bateaux dans un port
 Remarque(s)    : -
 Compilateur    : build-essential gcc 11.3.0
 -----------------------------------------------------------------------------------
*/

#ifndef PRG2_LABO3_BATEAU_H
#define PRG2_LABO3_BATEAU_H

#include <inttypes.h>

#define TAXE_BASE_VOILIER 50
#define TAX_BASE_MOTEUR 100

#define DEFAULT_TAXE_VOILIER 0
#define LIMIT_SURFACE_VOILIER 200
#define SURPLUS_TAXE_VOILIER 25

#define DEFAULT_TAXE_PECHE 0
#define LIMIT_TONNAGE_PECHE 20
#define SURPLUS_TAXE_PECHE 100

#define DEFAULT_TAXE_PLAISANCE 50
#define LIMIT_PUISSANCE_PLAISANCE 50
#define SURPLUS_TAXE_PLAISANCE 15 //à multiplier par longeur

#define ESPACE_AFFICHAGE 20

typedef enum {
   VOILIER, MOTEUR
} Categorie;
typedef enum {
   PECHE, PLAISANCE
} SousCategorie;
typedef char *Nom;

typedef struct {
   uint8_t tonnesPoisson;
} Peche;

typedef struct {
   const Nom nomProprietaire;
   uint8_t longeur; //[m]
} Plaisance;

typedef union {
   Peche peche;
   Plaisance plaisance;
} SpecificiteSousCategorie;

typedef struct {
   uint16_t puissance; //[CV]
   SousCategorie sousCategorie;
   SpecificiteSousCategorie specificiteSousCategorie;
} Moteur;

typedef struct {
   uint16_t surface; //[m^2]
} Voilier;

typedef union {
   Voilier voilier;
   Moteur moteur;
} SpecificiteCategorie;

typedef struct {
   const Nom nom;
   Categorie categorie;
   SpecificiteCategorie specificiteCategorie;
} Bateau;

Bateau voilier(const Nom nom, uint16_t surface);

Bateau peche(const Nom nom, uint16_t puissance, uint8_t tonnesPoisson);

Bateau plaisance(const Nom nom, uint16_t puissance, const Nom nomProprietaire,
                 uint8_t longeur);

double taxeAnnuelle(const Bateau *bateau);

void afficherBateau(const Bateau *bateau);

void afficherBateaux(const Bateau bateaux[], const size_t n);

void afficherStatistiques(const Bateau bateaux[], const size_t n);

#endif //PRG2_LABO3_BATEAU_H
