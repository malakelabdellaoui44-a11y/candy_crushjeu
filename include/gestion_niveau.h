#include "../include/gestion_niveau.h"
#include "../include/grille.h"
#include <stdio.h>

// ============================================================================
//  CHARGER LE CONTRAT DU NIVEAU
// ============================================================================
void chargerContrat(int niveau, Contrat *c)
{
    // Réinitialiser tous les objectifs à 0
    for (int i = 0; i < NB_TYPES_ITEM; i++) {
        c->objectif_item[i] = 0;
    }

    c->max_coups = 0;
    c->max_temps = 0;

    // Exemple simple — valeurs à adapter selon les niveaux
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
    else {
        // Niveau non défini : valeurs par défaut
        c->max_coups = 15;
        c->max_temps = 45;
    }
}



// ============================================================================
//  INITIALISATION DU NIVEAU
// ============================================================================
void initNiveau(int niveau,
                int grille[NB_LIGNES][NB_COLONNES],
                Contrat *c)
{
    // Charger les objectifs du contrat
    chargerContrat(niveau, c);

    // Générer une grille jouable (module grille)
    genererGrilleAleatoire(grille);
}



// ============================================================================
//  MISE À JOUR APRÈS SUPPRESSION
// ============================================================================
void majContratApresSuppression(int typeFruit,
                                int nb,
                                int *score,
                                Contrat *c,
                                int *coupsRestants)
{
    // Mettre à jour l'objectif si le fruit supprimé est demandé
    if (typeFruit >= 0 && typeFruit < NB_TYPES_ITEM) {
        c->objectif_item[typeFruit] -= nb;

        if (c->objectif_item[typeFruit] < 0) {
            c->objectif_item[typeFruit] = 0;
        }
    }

    // Score : +10 points par item supprimé
    *score += nb * 10;

    // On consomme 1 coup
    (*coupsRestants)--;
}



// ============================================================================
//  TEST SUCCÈS DU CONTRAT
// ============================================================================
int testSuccesContrat(Contrat c)
{
    for (int i = 0; i < NB_TYPES_ITEM; i++) {
        if (c.objectif_item[i] > 0) {
            return 0;   // Objectifs NON atteints
        }
    }
    return 1;           // Objectifs atteints 🎉
}



// ============================================================================
//  TEST ÉCHEC DU NIVEAU
// ============================================================================
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



// ============================================================================
//  JOUER UN NIVEAU COMPLET
// ============================================================================
void jouerNiveau(int niveau, int *vies)
{
    int grille[NB_LIGNES][NB_COLONNES];
    Contrat c;
    int score = 0;

    // Initialisation du niveau
    initNiveau(niveau, grille, &c);

    int coups = c.max_coups;
    int temps = c.max_temps;

    // Boucle principale du niveau
    while (!testSuccesContrat(c) && !testEchecNiveau(coups, temps, c)) {

        afficherGrille(grille);

        printf("\nCoups restants : %d | Temps restant : %d | Score : %d\n",
               coups, temps, score);

        int typeFruit, nbSupp;

        // Appel à la simulation d’une suppression (module grille)
        simulerSuppression(grille, &typeFruit, &nbSupp);

        // Mise à jour du contrat après suppression
        majContratApresSuppression(typeFruit, nbSupp, &score, &c, &coups);

        temps--;
    }

    // Résultat final du niveau
    if (testSuccesContrat(c)) {
        printf("\n🎉 Niveau %d réussi !\n", niveau);
    } else {
        printf("\n❌ Niveau %d échoué !\n", niveau);
        (*vies)--;
    }
}
