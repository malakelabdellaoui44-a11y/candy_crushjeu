#ifndef GESTION_NIVEAU_H
#define GESTION_NIVEAU_H

#include "common.h"          
#include "grille.h"         
#include "moteur_jeu.h"     
#include "affichage_console.h"
#include "clavier.h"

typedef struct {
    int objectif_item[NB_TYPES_ITEM];  
    int max_coups;                      
    int max_temps;                      
} Contrat;


void chargerContrat(int niveau, Contrat *c);
void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c,
                int *coupsRestants,
                int *tempsRestant,
                int *score);
void majContratApresSuppression(int typeFruit,
                                int nb,
                                int *score,
                                Contrat *c,
                                int *coupsRestants);
int testSuccesContrat(Contrat c);
int testEchecNiveau(int coupsRestants, int tempsRestant, Contrat c);
void jouerNiveau(int niveau, int *vies);

#endif

