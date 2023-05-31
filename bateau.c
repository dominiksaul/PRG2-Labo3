/*
 -----------------------------------------------------------------------------------
 Nom du fichier : bateau.c
 Auteur(s)      : Diana Laurenti, Glodi Domingos, Dominik Saul
 Date creation  : 25.05.2023
 Description    : Librairie permettant la gestion des bateaux dans un port
 Remarque(s)    : -
 Compilateur    : build-essential gcc 11.3.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "bateau.h"
#define FORMAT(SPECIFIER) "%-*s: " SPECIFIER "\n"
#define afficher_texte(categorie, valeur) do {             \
printf(FORMAT("%s"), ESPACE_AFFICHAGE, categorie, valeur); \
} while (0)
#define afficher_mesure(categorie, valeur, unite) do {             \
printf(FORMAT("%d%s"), ESPACE_AFFICHAGE, categorie, valeur, unite); \
} while (0)
#define afficher_stats(categorie, valeur) do {             \
printf(FORMAT("%g"), ESPACE_AFFICHAGE, categorie, valeur); \
} while (0)

const char* CATEGORIES[] = {"Voilier", "Moteur"};
const char* SOUS_CATEGORIES[] = {"Peche", "Plaisance"};

Bateau voilier(const Nom nom, uint16_t surface) {
    return (Bateau) {
            nom,
            VOILIER,
            {{surface}}
    };
}

Bateau peche(const Nom nom, uint16_t puissance, uint8_t tonnesPoisson) {
    return (Bateau) {
            nom,
            MOTEUR,
            {.moteur = {
                    puissance,
                    PECHE,
                    {{tonnesPoisson}}}}
    };
}

Bateau plaisance(const Nom nom, uint16_t puissance, const Nom nomProprietaire,
                 uint8_t longeur) {
    return (Bateau) {
            nom,
            MOTEUR,
            {.moteur = {
                    puissance,
                    PLAISANCE,
                    {.plaisance = {
                            nomProprietaire,
                            longeur}}}}
    };
}

double taxeBase(Categorie categorie) {
    if (categorie == VOILIER)
        return TAXE_BASE_VOILIER;
    else
        return TAX_BASE_MOTEUR;
}

double taxeSpecifique(const Bateau *bateau) {
    double taxe = 0;
    switch (bateau->categorie) {
        case VOILIER :
            taxe =
                    bateau->specificiteCategorie.voilier.surface < LIMIT_SURFACE_VOILIER ?
                    DEFAULT_TAXE_VOILIER : SURPLUS_TAXE_VOILIER;
            break;
        case MOTEUR : {
            switch (bateau->specificiteCategorie.moteur.sousCategorie) {
                case PECHE :
                    taxe = bateau->specificiteCategorie.moteur
                                   .specificiteSousCategorie.peche.tonnesPoisson <
                           LIMIT_TONNAGE_PECHE ?
                           DEFAULT_TAXE_PECHE : SURPLUS_TAXE_PECHE;
                    break;
                case PLAISANCE:
                    taxe = bateau->specificiteCategorie.moteur.puissance
                           < LIMIT_PUISSANCE_PLAISANCE ? DEFAULT_TAXE_PLAISANCE :
                           bateau->specificiteCategorie.moteur.specificiteSousCategorie
                                   .plaisance.longeur * SURPLUS_TAXE_PLAISANCE;
                    break;
            }
        }
    }
    return taxe;
}

double taxeAnnuelle(const Bateau *bateau) {
    return taxeBase(bateau->categorie) + taxeSpecifique(bateau);
}

void afficherBateau(const Bateau* bateau){
    afficher_texte("Nom", bateau -> nom);
    afficher_texte("Categorie", CATEGORIES[bateau -> categorie]);
    if(bateau -> categorie == VOILIER){
        afficher_mesure("Surface", bateau -> specificiteCategorie.voilier.surface, "m\u00b2");
    }
    else{
        afficher_mesure("Puissance", bateau -> specificiteCategorie.moteur.puissance, "CV");
        afficher_texte("Sous-categorie", SOUS_CATEGORIES[bateau ->
                specificiteCategorie.moteur.sousCategorie]);
        if(bateau->specificiteCategorie.moteur.sousCategorie == PECHE)
            afficher_mesure("Tonnes de poisson",
                            bateau->specificiteCategorie.moteur.specificiteSousCategorie.peche.tonnesPoisson,
                            "");
        else{
            afficher_texte("Nom du proprietaire",
                           bateau->specificiteCategorie.moteur.specificiteSousCategorie
                                   .plaisance.nomProprietaire);
            afficher_mesure("Longeur",
                           bateau->specificiteCategorie.moteur.specificiteSousCategorie.plaisance.longeur,
                           "m");
        }
    }
    printf("%-*s: %.2f€\n", ESPACE_AFFICHAGE, "Taxe annuelle due", taxeAnnuelle(bateau));
    printf("\n");
}

int comparerBateaux(const void* bGauche, const void* bDroite){
    if(taxeAnnuelle(bGauche) < taxeAnnuelle(bDroite))
        return 1;
    if(taxeAnnuelle(bGauche) > taxeAnnuelle(bDroite))
        return -1;
    return 0;
}

void ordonnerBateaux(const Bateau bateaux[], const size_t n){
    qsort((void *) bateaux, n, sizeof(Bateau), comparerBateaux);
}

void afficherBateaux(const Bateau bateaux[], const size_t n){
    printf("Bateaux dans le port :\n");
    ordonnerBateaux(bateaux, n);
    for(size_t i = 0; i < n; ++i){
        afficherBateau(bateaux + i);
    }
}

void compterBateauxParType(const Bateau bateaux[], const size_t n, size_t* numVoiliers,
                           size_t* numPeches, size_t* numPlaisances){
    for(size_t i = 0; i < n; ++i) {
        if((bateaux + i) -> categorie == VOILIER)
            ++*numVoiliers;
        else if((bateaux + i) -> specificiteCategorie.moteur.sousCategorie == PECHE)
            ++*numPeches;
        else
            ++*numPlaisances;
    }
}

double calculerSomme(const double taxes[], const size_t n){
    double somme = 0;
    for(size_t i = 0; i < n; ++i){
        somme += *(taxes + i);
    }
    return somme;
}

double calculerMoyenne(const double somme, const size_t n){
    assert(n > 1);
    return somme / (double)n;
}

double calculerMediane(const double taxes[], const size_t n){
    return *(taxes + n/2);
}

double calculerEcartType(const double taxes[], const size_t n){
    assert(n > 1);
    double sommeDeCarres = 0;
    double moyenne = calculerMoyenne(calculerSomme(taxes, n),n);
    for(size_t i = 0; i < n; ++i){
        sommeDeCarres += pow((*(taxes + i) - moyenne),2);
    }
    double ecart = sommeDeCarres / 2;
    return sqrt(ecart);
}

void afficherStatistiquesParType(const char* type, const double* taxes, const
size_t numBateaux){
    double somme = calculerSomme(taxes,numBateaux);
    printf("Taxes annuelles %s :\n", type);
    afficher_stats("Somme", somme);
    afficher_stats("Moyenne", calculerMoyenne(somme, numBateaux));
    afficher_stats("Mediane", calculerMediane(taxes, numBateaux));
    afficher_stats("Ecart-type", calculerEcartType(taxes, numBateaux));
    printf("\n");
}

void afficherStatistiques(const Bateau bateaux[], const size_t n){
    size_t numVoiliers = 0;
    size_t numPeches = 0;
    size_t numPlaisances = 0;

    compterBateauxParType(bateaux, n, &numVoiliers, &numPeches,
                          &numPlaisances);
    ordonnerBateaux(bateaux, n);

    // creer des tableaux pour stocker les taxes annuelles par type de bateau, pour
    // effectuer les calcules après
    double* taxesVoiliers = (double*)malloc(numVoiliers * sizeof(double));
    assert(taxesVoiliers != NULL);
    double* taxesPeches = (double*)malloc(numPeches * sizeof(double));
    assert(taxesPeches != NULL);
    double* taxesPlaisances = (double*)malloc(numPlaisances * sizeof(double));
    assert(taxesPlaisances != NULL);

    size_t indexVoiliers = 0;
    size_t indexPeches = 0;
    size_t indexPlaisances = 0;
    for(size_t i = 0; i < n; ++i){
        if((bateaux + i) -> categorie == VOILIER){
            *(taxesVoiliers + indexVoiliers) = taxeAnnuelle(bateaux + i);
            ++indexVoiliers;
        }
        else if((bateaux + i) -> specificiteCategorie.moteur.sousCategorie == PECHE){
            *(taxesPeches + indexPeches) = taxeAnnuelle(bateaux + i);
            ++indexPeches;
        }
        if((bateaux + i) -> specificiteCategorie.moteur.sousCategorie == PLAISANCE){
            *(taxesPlaisances + indexPlaisances) = taxeAnnuelle(bateaux + i);
            ++indexPlaisances;
        }
    }
    afficherStatistiquesParType("voiliers", taxesVoiliers, numVoiliers);
    afficherStatistiquesParType("bateaux de peche", taxesPeches, numVoiliers);
    afficherStatistiquesParType("bateau de plaisance", taxesPlaisances, numVoiliers);

    free(taxesVoiliers);
    free(taxesPeches);
    free(taxesPlaisances);
}
