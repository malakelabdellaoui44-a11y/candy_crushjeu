#ifndef GESTION_NIVEAU_H
#define GESTION_NIVEAU_H

#include "common.h"     // NB_LIGNES, NB_COLONNES, NB_TYPES_ITEM, Contrat
#include <stdio.h>
#include <stdlib.h>

// --------- PROTOTYPES DU MODULE 4 ---------

void chargerContrat(int niveau, Contrat *c);

void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c,
                int *coupsRestants,
                int *tempsRestant,
                int *score);

void majContratApresSuppression(int typeFruit, int nb, int *score,
                                Contrat *c, int *coupsRestants);

int testSuccesContrat(Contrat c);

int testEchecNiveau(int coupsRestants, int tempsRestant, Contrat c);

void jouerNiveau(int niveau, int *vies);

#endif
