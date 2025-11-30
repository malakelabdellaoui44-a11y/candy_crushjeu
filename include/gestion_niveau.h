// include/gestion_niveau.h

#ifndef GESTION_NIVEAU_H
#define GESTION_NIVEAU_H

// --- 1. Définitions et Structures ---
// Constantes définies dans votre analyse [cite: 476, 477]
#define LIGNES 25
#define COLONNES 45
#define NB_TYPES_ITEMS 5 // 5 types d'items de base (bonbons/fruits)

// Structure pour stocker les objectifs du contrat du niveau [cite: 140, 142, 144, 147]
typedef struct {
    int objectifs[NB_TYPES_ITEMS]; // Quantité de chaque item à éliminer (contrat[5])
    int coupsRestants;             // Nombre de coups maximum [cite: 145]
    int tempsRestant;              // Timer du niveau (en secondes) [cite: 142]
} Contrat;


// --- 2. Prototypes du Module 4 (Gestion Niveau) ---
// Fonctions d'initialisation et de jeu
void chargerContrat(int niveau, Contrat *c);
void initNiveau(int niveau, int grille[LIGNES][COLONNES], Contrat *c);
void jouerNiveau(int niveau, int *vies);

// Fonctions de logique du niveau
void majContratApresSuppression(int typeFruit, int nb, int *score, Contrat *c);

// Fonctions de test (déjà détaillées aux étapes 3 et 4)
int testSuccesContrat(Contrat c);
int testEchecNiveau (int coups, int temps, Contrat c);


#endif // GESTION_NIVEAU_H
