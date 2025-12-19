#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>
#include "Affichage.h"

/* Alias pour compatibilité avec le code existant */
#define NB_LIGNES   LIGNE
#define NB_COLONNES COLONNE

/* =========================
   Constantes (types d'items)
   ========================= */
#define JOKER 7
#define BOMBE 8   

#define CARRE 1000
#define CROIX 2000

/* =========================
   Structures
   ========================= */
typedef struct {
    int ligne;
    int colonne;
    int type;      /* ex: 4 (suite), 6, CARRE, CROIX... */
} Item;

typedef struct {
    int nb;        /* nombre de cases dans la combinaison */
    Item item[NB_LIGNES * NB_COLONNES];
} Combinaison;

/* =========================
   Plateau / utilitaires
   ========================= */
void iniPlateau(int plateau[NB_LIGNES][NB_COLONNES]);
void copierGrille(int grille[NB_LIGNES][NB_COLONNES],int grille2[NB_LIGNES][NB_COLONNES]);
void lirePlateau(int plateau[NB_LIGNES][NB_COLONNES]);
void remplirCasesVides(int grille[NB_LIGNES][NB_COLONNES]);

/* =========================
   Détection de combinaisons
   ========================= */
Combinaison detecterSuiteX(int grille[NB_LIGNES][NB_COLONNES], int taille);
Combinaison detecterSuiteY(int grille[NB_LIGNES][NB_COLONNES], int taille);

Combinaison detecterDoubleSuiteX(int grille[NB_LIGNES][NB_COLONNES], int taille);
Combinaison detecterDoubleSuiteY(int grille[NB_LIGNES][NB_COLONNES], int taille);

Combinaison detecterCarre(int grille[NB_LIGNES][NB_COLONNES]);
Combinaison detecterCroix(int grille[NB_LIGNES][NB_COLONNES]);

/* =========================
   Suites de 6 (effacement global)
   =========================
   Retourne 0 si aucune suite6,
   sinon retourne la valeur à effacer (non-joker si possible).
*/
int detectersuite6x(int grille[NB_LIGNES][NB_COLONNES]);
int detectersuite6y(int grille[NB_LIGNES][NB_COLONNES]);

/* =========================
   Suppression / gravité
   ========================= */
void supprimeCombi(int grille[NB_LIGNES][NB_COLONNES], Combinaison combi);
void appliqueGravite(int grille[NB_LIGNES][NB_COLONNES]);
void effaceValeur(int grille[NB_LIGNES][NB_COLONNES], int val_case);

/* =========================
   Boucles de stabilisation
   ========================= */
void suppression(int grille[NB_LIGNES][NB_COLONNES]);
void stabilisePlateau(int grille[NB_LIGNES][NB_COLONNES]);

/* =========================
   Coups du joueur
   ========================= */
int detecterCombinaisons(void);
void echangerItems(int x1, int y1, int x2, int y2);
int estVoisin(int x1, int y1, int x2, int y2);
int mouvementValide(int grille[NB_LIGNES][NB_COLONNES], int x1, int y1, int x2, int y2);

#endif /* GRILLE_H */
