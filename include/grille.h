#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>

/* Constantes */
#define NB_LIGNES 25
#define NB_COLONNES 28

#define JOKER 7
#define BOMBE 8

#define CARRE 1000
#define CROIX 2000

/* Structures */
typedef struct {
    int ligne;
    int colonne;
    int type;
} Item;

typedef struct {
    int nb;
    Item item[NB_LIGNES * NB_COLONNES];
} Combinaison;

/* Fonctions plateau / affichage */
void iniPlateau(int plateau[NB_LIGNES][NB_COLONNES]);
void lirePlateau(int plateau[NB_LIGNES][NB_COLONNES]);
void remplirCasesVides(int grille[NB_LIGNES][NB_COLONNES]);

/* Détection combinaisons */
Combinaison detecterSuiteX(int grille[NB_LIGNES][NB_COLONNES], int taille);
Combinaison detecterSuiteY(int grille[NB_LIGNES][NB_COLONNES], int taille);
Combinaison detecterCarre(int grille[NB_LIGNES][NB_COLONNES]);
Combinaison detecterCroix(int grille[NB_LIGNES][NB_COLONNES]);

/* Suites de 6 (effacement par valeur) */
int detectersuite6x(int grille[NB_LIGNES][NB_COLONNES], int taille);
int detectersuite6y(int grille[NB_LIGNES][NB_COLONNES], int taille);

/* Suppression / gravité */
void SuppCombi(int grille[NB_LIGNES][NB_COLONNES], Combinaison combi);
void appliquegravite(int grille[NB_LIGNES][NB_COLONNES]);
void effaceValeur(int grille[NB_LIGNES][NB_COLONNES], int val_case);

/* Debug / tests */
void traiterCombinaisons(int grille[NB_LIGNES][NB_COLONNES]);

/* Boucle principale de suppression */
void suppression(int grille[NB_LIGNES][NB_COLONNES]);

#endif 