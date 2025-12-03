#include "../include/gestion_niveau.h"
#include "../include/grille.h"
#include <stdio.h>

void chargerContrat(int niveau, Contrat *c)
    {
    for (int i = 0; i < NB_TYPES_ITEM; i++) {
        c->objectif_item[i] = 0;
     }

    c->max_coups = 0;
    c->max_temps = 0;

    if (niveau == 1) {
        c->objectif_item[0] = 10;
        c->objectif_item[1] = 15;

        c->max_coups = 20;
        c->max_temps = 60;
        }
else if (niveau == 2) {
        c->objectif_item[0] = 5;
        c->objectif_item[2] = 8;

        c->max_coups = 25;
        c->max_temps = 75;
        }
else    {
      
        c->max_coups = 15;
        c->max_temps = 45;
        }
        }
void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c)
        {
    chargerContrat(niveau, c);
    genererGrilleAleatoire(grille);
        }

void majContratApresSuppression(int typeFruit,
                                int nb,
                                int *score,
                                Contrat *c,
                                int *coupsRestants)
        {
    if (typeFruit >= 0 && typeFruit < NB_TYPES_ITEM) {
        c->objectif_item[typeFruit] -= nb;

        if (c->objectif_item[typeFruit] < 0) {
            c->objectif_item[typeFruit] = 0;
        }
        }    

    *score += nb * 10;
    (*coupsRestants)--;
        }
int testSuccesContrat(Contrat c)
        {
    for (int i = 0; i < NB_TYPES_ITEM; i++) {
        if (c.objectif_item[i] > 0) {
            return 0;   
        }
        }
    return 1;         
        }

int testEchecNiveau(int coupsRestants, int tempsRestant, Contrat c)
        {
    if (testSuccesContrat(c)) {
        return 0; // Impossible d'échouer si le contrat est validé
        }

    if (coupsRestants <= 0 || tempsRestant <= 0) {
        return 1; // Conditions d’échec remplies
          }

    return 0;
        }

void jouerNiveau(int niveau, int *vies)
{
    int grille[NB_LIGNES][NB_COLONNES];
    Contrat c;
    int score = 0;
    initNiveau(niveau, grille, &c);

    int coups = c.max_coups;
    int temps = c.max_temps;

    while (!testSuccesContrat(c) && !testEchecNiveau(coups, temps, c)) {

        afficherGrille(grille);

        printf("\nCoups restants : %d | Temps restant : %d | Score : %d\n",
               coups, temps, score);

        int typeFruit, nbSupp;
        simulerSuppression(grille, &typeFruit, &nbSupp);
        majContratApresSuppression(typeFruit, nbSupp, &score, &c, &coups);

        temps--;
    }    
    if (testSuccesContrat(c)) {
        printf("\n🎉 Niveau %d réussi !\n", niveau);
    } else {
        printf("\n❌ Niveau %d échoué !\n", niveau);
        (*vies)--;
    }
        }
        
