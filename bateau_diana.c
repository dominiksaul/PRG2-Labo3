//
// Created by diana.laurenti on 27.05.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#include "bateau_diana.h"

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
	printf("%-*s: %s\n", ESPACE_AFFICHAGE, "Nom", bateau -> nom);
	printf("%-*s: %s\n", ESPACE_AFFICHAGE, "Categorie", CATEGORIES[bateau -> categorie]);
	if(bateau -> categorie == VOILIER){
		printf("%-*s: %dm\u00b2\n", ESPACE_AFFICHAGE, "Surface", bateau -> specificiteCategorie
			.voilier.surface);
	}
	else{
		printf("%-*s: %dCV\n", ESPACE_AFFICHAGE, "Puissance", bateau -> specificiteCategorie
			.moteur.puissance);
		printf("%-*s: %s\n", ESPACE_AFFICHAGE, "Sous-categorie", SOUS_CATEGORIES[bateau ->
			specificiteCategorie.moteur.sousCategorie]);
		if(bateau->specificiteCategorie.moteur.sousCategorie == PECHE)
			printf("%-*s: %d\n", ESPACE_AFFICHAGE, "Tonnes de poisson",
					 bateau->specificiteCategorie.moteur.specificiteSousCategorie.peche
						 .tonnesPoisson);
		else{
			printf("%-*s: %s\n", ESPACE_AFFICHAGE, "Nom du proprietaire",
					 bateau->specificiteCategorie.moteur.specificiteSousCategorie
						 .plaisance.nomProprietaire);
			printf("%-*s: %dm\n", ESPACE_AFFICHAGE, "Longeur",
					 bateau->specificiteCategorie.moteur.specificiteSousCategorie
						 .plaisance.longeur);
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
	return somme / (double)n;
}

double calculerMediane(const double taxes[], const size_t n){
	return *(taxes + n/2);
}

double calculerEcartType(const double taxes[], const size_t n){
	double sommeDeCarres = 0;
	for(size_t i = 0; i < n; ++i){
		sommeDeCarres += sqrt(*(taxes + i) - (double)n);
	}
	double ecart = n > 1 ? calculerMoyenne(sommeDeCarres, n - 1) : 0;
	return sqrt(ecart);
}

void afficherStatistiquesParType(const char* type, const double* taxes, const
size_t numBateaux){
	double somme = calculerSomme(taxes,numBateaux);
	printf("Taxes annuelles %s :\n", type);
	printf("%-*s: %g\n", ESPACE_AFFICHAGE, "Somme", somme);
	printf("%-*s: %g\n", ESPACE_AFFICHAGE, "Moyenne", calculerMoyenne
		(somme, numBateaux));
	printf("%-*s: %g\n", ESPACE_AFFICHAGE, "Mediane", calculerMediane
		(taxes, numBateaux));
	printf("%-*s: %g\n", ESPACE_AFFICHAGE, "Ecart-type", calculerEcartType
		(taxes, numBateaux));
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
	double* taxesPeches = (double*)malloc(numPeches * sizeof(double));
	double* taxesPlaisances = (double*)malloc(numPlaisances * sizeof(double));

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