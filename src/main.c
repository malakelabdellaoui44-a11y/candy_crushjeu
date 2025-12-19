/*******************************************************************************
 *                           CANDY CRUSH - MAIN.C
 * 
 * Fichier principal du jeu Candy Crush.
 * Utilise grille.c pour la détection et suppression des combinaisons.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "grille.h"
#include "Affichage.h"
#include "Clavier.h"
#include "extension.h"
#include "gestion_niveau.h"
/* #include "module7.h" */  /* Fichier non trouvé - commenté */

/* ============================================================================
   CONSTANTES DU JEU
   ============================================================================ */
#define VIES_INITIALES 3
#define NB_NIVEAUX 3

/* ============================================================================
   VARIABLES GLOBALES
   ============================================================================ */
int grille[NB_LIGNES][NB_COLONNES];
int vies = VIES_INITIALES;
int niveauActuel = 1;
int score = 0;
int coupsRestants = 0;
char pseudoJoueur[MAX_PSEUDO];

/* ============================================================================
   PROTOTYPES DES FONCTIONS
   ============================================================================ */
void initialiserJeu(void);
void boucleDeJeu(void);
int  menuPrincipal(void);
void nouvellePartie(void);
void reprendrePartie(void);
void initialiserNiveau(int niveau);
int  effectuerEchange(int x1, int y1, int x2, int y2);
int  estVoisin(int x1, int y1, int x2, int y2);
void echangerItems(int x1, int y1, int x2, int y2);
int  detecterCombinaisons(void);
void attendreTouche(void);


int main(void)
{
    // ON INITIALISE UN PEU TOUT
    system("chcp 65001 > nul");

    srand(time(NULL));

    /* Initialisation de la console Windows */
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cacherCurseur();
    
    int choix;
    do {
        effacerEcran();
        choix = menuPrincipal();
        
        switch (choix) {
            case 1:
                afficherRegle();
                printf("\n\nAppuyez sur une touche pour revenir au menu...\n");
                attendreTouche();
                break;
                
            case 2:
                nouvellePartie();
                break;
                
            case 3:
                reprendrePartie();
                break;
                
            case 4:
                afficherMessageFinPartie();
                break;
                
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 4);
    
    return 0;
}

