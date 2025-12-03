#ifndef GESTION_NIVEAU_H
#define GESTION_NIVEAU_H

#include "common.h"   // NB_LIGNES, NB_COLONNES, Contrat
#include <stdio.h>
#include <stdlib.h>

// -------- PROTOTYPES DU MODULE 4 --------

// 1. charger un contrat depuis le fichier
void chargerContrat(int niveau, Contrat *c);

// 2. initialiser le niveau
void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c,
                int *coupsRestants,
                int *tempsRestant,
                int *score);

// 3. mettre à jour le contrat après suppression
void majContratApresSuppression(int typeFruit,
                                int nb,
                                Contrat *c,
                                int *coupsRestants);

// 4. tester si le contrat est réussi
int testSuccesContrat(Contrat *c);

// 5. tester si le niveau est échoué
int testEchecNiveau(int coupsRestants,
                    int tempsRestant,
                    Contrat c);

// 6. jouer un niveau entier
void jouerNiveau(int niveau, int *vies);

#endif
