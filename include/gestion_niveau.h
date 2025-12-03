#ifndef GESTION_NIVEAU_H
#define GESTION_NIVEAU_H

#include "common.h"   // NB_LIGNES, NB_COLONNES, NB_TYPES_ITEM
#include "grille.h"    // pour générer et afficher la grille

// ============================================================================
//  STRUCTURE DU CONTRAT
// ============================================================================
typedef struct {
    int objectif_item[NB_TYPES_ITEM];   // objectifs pour chaque type d’item
    int max_coups;                      // nombre maximum de coups
    int max_temps;                      // temps maximum du niveau
    } Contrat;


// ============================================================================
//  PROTOTYPES DU MODULE GESTION NIVEAU
// ============================================================================

// Charge le contrat associé à un niveau
    void chargerContrat(int niveau, Contrat *c);

// Initialise la grille et le contrat
    void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c);

// Met à jour le contrat après une suppression
    void majContratApresSuppression(int typeFruit,
                                int nb,
                                int *score,
                                Contrat *c,
                                int *coupsRestants);

// Vérifie si tous les objectifs sont atteints
    int testSuccesContrat(Contrat c);

// Vérifie si le niveau est échoué (plus de temps ou coups)
    int testEchecNiveau(int coupsRestants, int tempsRestant, Contrat c);

// Lance la boucle de jeu d’un niveau
    void jouerNiveau(int niveau, int *vies);

#endif
