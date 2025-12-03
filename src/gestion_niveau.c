#include "../include/gestion_niveau.h"
#include "../include/moteur_jeu.h"
#include "../include/affichage_console.h"
#include "../include/clavier.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


// ============================================================================
//  CHARGER LE CONTRAT
// ============================================================================
/*
 * Initialise les objectifs, coups max et temps max selon le niveau choisi.
 * Version simple pour le projet.
 */
void chargerContrat(int niveau, Contrat *c)
{
    // Remise à zéro des objectifs
    for (int i = 0; i < NB_TYPES_ITEM; i++)
        c->objectif_item[i] = 0;

    if (niveau == 1)
    {
        c->objectif_item[0] = 10;
        c->objectif_item[1] = 15;

        c->max_coups = 20;
        c->max_temps = 60;
    }
    else if (niveau == 2)
    {
        c->objectif_item[0] = 20;
        c->objectif_item[2] = 10;
        c->objectif_item[4] = 10;

        c->max_coups = 30;
        c->max_temps = 90;
    }
    else // Niveau 3
    {
        c->objectif_item[1] = 20;
        c->objectif_item[2] = 15;
        c->objectif_item[3] = 20;

        c->max_coups = 35;
        c->max_temps = 120;
    }
}



// ============================================================================
//  INITIALISATION DU NIVEAU
// ============================================================================
/*
 * Prépare le niveau :
 *  - charge le contrat
 *  - initialise coups / temps / score
 *  - génère la grille aléatoire
 *  - stabilise la grille pour un départ jouable
 */
void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c,
                int *coupsRestants,
                int *tempsRestant,
                int *score)
{
    chargerContrat(niveau, c);

    *coupsRestants = c->max_coups;
    *tempsRestant  = c->max_temps;
    *score         = 0;

    srand(time(NULL));

    // Génération aléatoire
    for (int i = 0; i < NB_LIGNES; i++)
        for (int j = 0; j < NB_COLONNES; j++)
            grille[i][j] = rand() % NB_TYPES_ITEM;

    // Stabilisation pour éliminer les combinaisons automatiques
    stabiliserPlateau(grille);
}



// ============================================================================
//  MISE À JOUR DU CONTRAT APRÈS SUPPRESSION
// ============================================================================
/*
 * Après suppression :
 *  - diminue objectifs si fruit demandé
 *  - score + bonus
 *  - sinon = pénalité (-1 coup)
 */
void majContratApresSuppression(int typeFruit, int nb, int *score,
                                Contrat *c, int *coupsRestants)
{
    if (typeFruit < 0 || typeFruit >= NB_TYPES_ITEM)
        return;

    if (c->objectif_item[typeFruit] > 0)
    {
        c->objectif_item[typeFruit] -= nb;
        if (c->objectif_item[typeFruit] < 0)
            c->objectif_item[typeFruit] = 0;

        *score += nb * 10; // bonus
    }
    else
    {
        (*coupsRestants)--; // pénalité
    }
}



// ============================================================================
//  TEST SUCCÈS DU CONTRAT
// ============================================================================
int testSuccesContrat(Contrat c)
{
    for (int i = 0; i < NB_TYPES_ITEM; i++)
        if (c.objectif_item[i] > 0)
            return 0;

    return 1; // tous les objectifs atteints
}



// ============================================================================
//  TEST ÉCHEC DU NIVEAU
// ============================================================================
int testEchecNiveau(int coupsRestants, int tempsRestant, Contrat c)
{
    if ((coupsRestants <= 0 || tempsRestant <= 0) &&
        !testSuccesContrat(c))
        return 1; // perdu

    return 0;
}



// ============================================================================
//  JOUER UN NIVEAU COMPLET
// ============================================================================
/*
 * Boucle principale d’un niveau :
 *  - affichage
 *  - sélection 2 cases
 *  - échange
 *  - vérification
 *  - stabilisation
 *  - mise à jour contrat / score
 *  - test victoire/défaite
 */
void jouerNiveau(int niveau, int *vies)
{
    int grille[NB_LIGNES][NB_COLONNES];
    Contrat c;

    int coupsRestants;
    int tempsRestant;
    int score;

    initNiveau(niveau, grille, &c,
               &coupsRestants, &tempsRestant, &score);

    while (1)
    {
        afficherPlateau(grille);

        printf("\nNiveau %d | Vies : %d | Coups : %d | Temps : %d | Score : %d\n",
               niveau, *vies, coupsRestants, tempsRestant, score);

        int x1, y1, x2, y2;

        // Choix des 2 cases
        deplacementCurseur(&x1, &y1);
        deplacementCurseur(&x2, &y2);

        if (!estVoisin(x1, y1, x2, y2))
            continue;

        echangerItems(grille, x1, y1, x2, y2);

        if (!mouvementValide(grille, x1, y1, x2, y2))
        {
            echangerItems(grille, x1, y1, x2, y2);
            continue;
        }

        int typeRemoved = grille[x2][y2];
        int nbRemoved = 1;

        stabiliserPlateau(grille);

        majContratApresSuppression(typeRemoved, nbRemoved,
                                   &score, &c, &coupsRestants);

        if (testSuccesContrat(c))
        {
            printf("\n*** Niveau réussi ***\n");
            return;
        }

        if (testEchecNiveau(coupsRestants, tempsRestant, c))
        {
            printf("\n*** Niveau perdu ***\n");
            (*vies)--;
            return;
        }

        tempsRestant--;
    }
}
