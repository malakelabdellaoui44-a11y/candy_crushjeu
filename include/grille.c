#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grille.h"

/* Variable globale définie dans main.c */
extern int grille[NB_LIGNES][NB_COLONNES];
void iniPlateau(int plateau[NB_LIGNES][NB_COLONNES]){
	for(int i = 0; i <NB_LIGNES; i++){
		for(int j = 0; j < NB_COLONNES ; j++){
			plateau[i][j] = 0;
		}
	}
}
//int grille 2 pour allocation memoire
void copierGrille(int grille[NB_LIGNES][NB_COLONNES], int grille2[NB_LIGNES][NB_COLONNES]){
	for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            grille2[i][j] = grille[i][j];
        }
    }
}

void remplirCasesVides(int grille[NB_LIGNES][NB_COLONNES]){
	srand(time(NULL));
	for (int i = 0; i < NB_LIGNES; i++) {
		for (int j = 0; j < NB_COLONNES; j++) {
			if (grille[i][j] == 0){
				int aleatoire = rand() %7 +1;
//				if (aleatoire == JOKER) {
//					aleatoire = rand() %8 +1;
//				}
		    	grille[i][j] = aleatoire;
			}
		}
	}
}

/////// DETECTION SUITE 4 
Combinaison detecterSuiteX(int grille[NB_LIGNES][NB_COLONNES],int taille)
{
	Combinaison combi; //va cree ma structure vide
	combi.nb = 0;

	//on cherche les suite horizontales
	for (int i=0; i<NB_LIGNES; i++){
		int j = 0;
		while (j<NB_COLONNES) {
			int case_checker = grille[i][j];
			int case_suivante = j+1;
			while (case_suivante < NB_COLONNES && (grille[i][case_suivante] == case_checker || grille[i][case_suivante] == JOKER)) {
				case_suivante++;
			}
			int longeur_de_suite = case_suivante-j;
			if (longeur_de_suite >= taille) {
				for (int c = j; c < case_suivante; c++) {
			        combi.item[combi.nb].ligne = i;
                    combi.item[combi.nb].colonne = c;
                    combi.item[combi.nb].type = taille;  
                    combi.nb++;
	            }
	            return combi;
			}
		
			j = case_suivante; // on detecte pas 2 fois la meme suite
		}
	}
	return combi;
}

// detetction de Double suite X pour la bombe 
// ========================================================================================================================================
Combinaison detecterDoubleSuiteX(int grille[NB_LIGNES][NB_COLONNES],int taille)
{
	Combinaison combi; //va cree ma structure vide
	combi.nb = 0;
	int compteur = 0;
	//on cherche les suite horizontales
	for (int i=0; i<NB_LIGNES; i++){
		int j = 0;

		while (j<NB_COLONNES) {
			int case_checker = grille[i][j];
			int case_suivante = j+1;
			while (case_suivante < NB_COLONNES && (grille[i][case_suivante] == case_checker || grille[i][case_suivante] == JOKER)) {
				case_suivante++;
			}
			int longeur_de_suite = case_suivante-j;
			if (longeur_de_suite >= taille) {
				for (int c = j; c < case_suivante; c++) {
			        combi.item[combi.nb].ligne = i;
                    combi.item[combi.nb].colonne = c;
                    combi.item[combi.nb].type = taille;  
                    combi.nb++;
	            }
	            compteur ++;
			}
			j = case_suivante; 
		}
	}
	if(compteur <2){
		combi.nb = 0;
	}
	return combi;
}

Combinaison detecterDoubleSuiteY(int grille[NB_LIGNES][NB_COLONNES], int taille)
{
	Combinaison combi; //va cree ma structure vide
	combi.nb = 0;
	int compteur = 0;
	//on cherche les suite horizontales
	for(int i =0; i<NB_COLONNES;i++){
		int j = 0;
		while (j<NB_LIGNES) {
			int case_checker = grille[j][i];
			int case_suivante = j+1;
			while (case_suivante <NB_LIGNES && grille[case_suivante][i] == case_checker) {
				case_suivante += 1;
			}
			int longeur_de_suite = case_suivante-j;
			if (longeur_de_suite >= taille){
				for (int pos = j; pos < case_suivante; pos++){
			        combi.item[combi.nb].ligne = pos;
                    combi.item[combi.nb].colonne = i;
                    combi.item[combi.nb].type = taille;
                    combi.nb++;
			    }
				compteur ++;
			}
			j = case_suivante; // on detecte pas 2 fois la meme suite
		}
	}
	if(compteur <2){
		combi.nb =0;
	}
	return combi;
}
// FIN DETECTION DE 2 SUITE 
// ========================================================================================================================================

Combinaison detecterSuiteY(int grille[NB_LIGNES][NB_COLONNES], int taille)
{
	Combinaison combi; //va cree ma structure vide
	combi.nb = 0;

	//on cherche les suite horizontales
	for(int i =0; i<NB_COLONNES;i++){
		int j = 0;
		while (j<NB_LIGNES) {
			int case_checker = grille[j][i];
			int case_suivante = j+1;
			while (case_suivante <NB_LIGNES && (grille[case_suivante][i] == case_checker || grille[case_suivante][i] == JOKER)) {
				case_suivante += 1;
			}
			int longeur_de_suite = case_suivante-j;
			if (longeur_de_suite >= taille){
				for (int pos = j; pos < case_suivante; pos++){
			        combi.item[combi.nb].ligne = pos;
                    combi.item[combi.nb].colonne = i;
                    combi.item[combi.nb].type = taille;
                    combi.nb++;
			    }
			    return combi;
			}
			j = case_suivante; // on detecte pas 2 fois la meme suite
		}
	}
	return combi;
}


Combinaison detecterCarre(int grille[NB_LIGNES][NB_COLONNES])
{
	Combinaison combi; //va cree ma structure vide
	combi.nb = 0;

	for (int i=0; i<NB_LIGNES-4; i++) {
		for (int j=0; j<NB_COLONNES-4; j++) {
			int case_checker = grille[i][j];

			bool trouve = true;
			int ligne = i;
			for (int k=j; k<j+4; k++) {
				if (grille[ligne][k] != case_checker && grille[ligne][k] != JOKER) {
					trouve = false;
				}
			}

			ligne++;
			if ((grille[ligne][j] != case_checker && grille[ligne][j] != JOKER) ||
				(grille[ligne][j+3] != case_checker && grille[ligne][j+3] != JOKER)) {
				trouve = false;
			}
			
			ligne++;
			if ((grille[ligne][j] != case_checker && grille[ligne][j] != JOKER) ||
				(grille[ligne][j+3] != case_checker && grille[ligne][j+3] != JOKER)) {
				trouve = false;
			}

			ligne++;
			for (int k=j; k<j+4; k++) {
				if (grille[ligne][k] != case_checker && grille[ligne][k] != JOKER) {
					trouve = false;
				}
			}
			
			if (trouve) {
				for (int k=j; k<j+4; k++) {
				    combi.item[combi.nb].ligne = i;
                    combi.item[combi.nb].colonne = k;
                    combi.item[combi.nb].type = CARRE;  
                    combi.nb++;
				    combi.item[combi.nb].ligne = i+3;
                    combi.item[combi.nb].colonne = k;
                    combi.item[combi.nb].type = CARRE;  
                    combi.nb++;
				}
			    combi.item[combi.nb].ligne = i+1;
                combi.item[combi.nb].colonne = j;
                combi.item[combi.nb].type = CARRE;  
                combi.nb++;
			    combi.item[combi.nb].ligne = i+2;
                combi.item[combi.nb].colonne = j;
                combi.item[combi.nb].type = CARRE;  
                combi.nb++;
			    combi.item[combi.nb].ligne = i+1;
                combi.item[combi.nb].colonne = j+3;
                combi.item[combi.nb].type = CARRE;  
                combi.nb++;
			    combi.item[combi.nb].ligne = i+2;
                combi.item[combi.nb].colonne = j+3;
                combi.item[combi.nb].type = CARRE;  
                combi.nb++;
                return combi;
			}
		}
	}
	return combi;
}


Combinaison detecterCroix(int grille[NB_LIGNES][NB_COLONNES])
{
	Combinaison combi; //va cree ma structure vide
	combi.nb = 0;

	for (int i=2; i<NB_LIGNES-2; i++){
		int j = 0;
		for (int j=2; j<NB_COLONNES-2; j++) {
			int case_checker = grille[i][j];

			bool trouve = true;
			for (int k=j-2; k<=j+2; k++) {
				if (grille[i][k] != case_checker && grille[i][k] != JOKER) {
					trouve = false;
				}
			}

			for (int k=i-2; k<=i+2; k++) {
				if (grille[k][j] != case_checker && grille[k][j] != JOKER) {
					trouve = false;
				}
			}
			
			if (trouve) {
				for (int k=j-2; k<=j+2; k++) {
				    combi.item[combi.nb].ligne = i;
                    combi.item[combi.nb].colonne = k;
                    combi.item[combi.nb].type = CROIX;  
                    combi.nb++;
				}
				for (int k=i-2; k<=i+2; k++) {
					if (k==i) {
						continue;
					}
				    combi.item[combi.nb].ligne = k;
                    combi.item[combi.nb].colonne = j;
                    combi.item[combi.nb].type = CROIX;  
                    combi.nb++;
				}
				return combi;
			}
		}
	}
	return combi;
}
//detection suite de 6 et suppression des elements qui sont present dans la ligne et dans la grille 
int detectersuite6x(int grille[NB_LIGNES][NB_COLONNES]){
	    Combinaison combi = detecterSuiteX(grille, 6);
	    if (combi.nb > 0){
	    	int val_case = JOKER;
	    	for(int i = 0; i< combi.nb; i++){
			    int ligne = combi.item[i].ligne;
				int colonne = combi.item[i].colonne;
				if (grille[ligne][colonne] != JOKER) {
					val_case = grille[ligne][colonne];
				}
			}
			return val_case;
	    }
	    return 0;
}
int detectersuite6y(int grille[NB_LIGNES][NB_COLONNES]){
	    Combinaison combi = detecterSuiteY(grille, 6);
	    if (combi.nb > 0){
	    	int val_case = JOKER;
	    	for(int i = 0; i< combi.nb; i++){
			    int ligne = combi.item[i].ligne;
				int colonne = combi.item[i].colonne;
				if (grille[ligne][colonne] != JOKER) {
					val_case = grille[ligne][colonne];
				}
			} 
			return val_case;
	    }
	    return 0;
}

void supprimeCombi(int grille[NB_LIGNES][NB_COLONNES], Combinaison combi) {
	for (int i = 0; i<combi.nb;i++) {
		int ligne = combi.item[i].ligne;
		int colonne = combi.item[i].colonne;
		grille[ligne][colonne] = 0;
	}
}



void appliqueGravite(int grille[NB_LIGNES][NB_COLONNES]){

		for(int i = NB_LIGNES -1; i>=0; i--){
			for( int j = 0; j < NB_COLONNES; j++){
				if(grille[i][j] == 0){
				
					for (int k = i -1; k >= 0; k--){
						if(grille[k][j] != 0){
							grille[i][j] = grille[k][j];
							grille[k][j] = 0;
							break;

						}

				}
/*				if(grille[i][j] == 0 && grille[i-1][j] != 0){
					grille[i][j] = grille[i-1][j];
					grille[i-1][j] = 0;
				}*/
			}
		}
	}
}
void effaceValeur(int grille[NB_LIGNES][NB_COLONNES], int val_case){
	for(int i = 0; i< NB_LIGNES; i++){
		for( int j = 0; j<NB_COLONNES; j++){
			if(grille[i][j] == val_case){
				grille[i][j] = 0;
			}
		}
	}
}
void supprimeSuite6(int grille[NB_LIGNES][NB_COLONNES], Combinaison combi){
	if(combi.nb >0){
		int resultat = JOKER;
		for (int i = 0; i< combi.nb;i++){
			if( grille[combi.item[i].ligne][combi.item[i].colonne] != JOKER){ //chercher le premier caractère qui n'est pas un joker dans la combinaison
				resultat = grille[combi.item[i].ligne][combi.item[i].colonne];
			}
		}
	}
}

void suppression(int grille[NB_LIGNES][NB_COLONNES]) {
	while (true) {
    	int case6x = detectersuite6x(grille);
    	if (case6x != 0) {
    		effaceValeur(grille, case6x);
	    	appliqueGravite(grille);
	        remplirCasesVides(grille);	
    	}

		int case6y = detectersuite6y(grille);
    	if (case6y != 0) {
    		effaceValeur(grille, case6y);
	    	appliqueGravite(grille);
	        remplirCasesVides(grille);	
    	}


    	Combinaison cx = detecterSuiteX(grille, 4);
        Combinaison cy = detecterSuiteY(grille, 4);
        Combinaison carre = detecterCarre(grille);
        Combinaison croix = detecterCroix(grille);
        

        if (cx.nb == 0 && cy.nb == 0 && carre.nb == 0 && croix.nb == 0) {
            break;
        }
        if (croix.nb > 0) {
            supprimeCombi(grille, croix);
        } else if (carre.nb > 0) {
            supprimeCombi(grille, carre);
        } else if (cx.nb > 0) {
            supprimeCombi(grille, cx);
        } else{
            supprimeCombi(grille, cy);
        }
        
        appliqueGravite(grille);
        remplirCasesVides(grille);

	}

}

void stabilisePlateau(int grille[NB_LIGNES][NB_COLONNES]){
	int a_supprimer;
	do{
		a_supprimer = 0;
		//effecer la suite de 6 et toute les valeur du meme type de la suite
		int supper6 = detectersuite6x(grille);
		if (supper6 == 0){
			supper6 = detectersuite6y(grille);
		}
		if (supper6 != 0) {
            effaceValeur(grille, supper6);
            a_supprimer = 1;
        }
		else{
			//si on la pas detecter on supprime Croix, carre, suite4x, 4y
			Combinaison combi;
			combi.nb = 0;

			combi = detecterCroix(grille);
			if(combi.nb == 0){
				combi = detecterCarre(grille);
			}
            if (combi.nb == 0) {
                combi = detecterSuiteX(grille, 4);
			}
			if (combi.nb == 0) {
				combi = detecterSuiteY(grille, 4);
			}

			if(combi.nb >= 4 && combi.item[0].type == 4){
				combi.nb = 4;
			}
			if (combi.nb > 0) {
                supprimeCombi(grille, combi);
                a_supprimer = 1;
            }
		}
		if(a_supprimer == 1){
			appliqueGravite(grille);
			remplirCasesVides(grille);
		}
	}while(a_supprimer);
}
// On lance la detection des combinaisons
int detecterCombinaisons()
{
    int suite6x = detectersuite6x(grille);
    if (suite6x != 0) return 1;
    
    int suite6y = detectersuite6y(grille);
    if (suite6y != 0) return 1;
    
    Combinaison croix = detecterCroix(grille);
    if (croix.nb > 0) return 1;
    
    Combinaison carre = detecterCarre(grille);
    if (carre.nb > 0) return 1;
    
    Combinaison suiteX = detecterSuiteX(grille, 4);
    if (suiteX.nb > 0) return 1;
    
    Combinaison suiteY = detecterSuiteY(grille, 4);
    if (suiteY.nb > 0) return 1;
    
    return 0;
}


void echangerItems(int x1, int y1, int x2, int y2)
{
    int temp = grille[y1][x1];
    grille[y1][x1] = grille[y2][x2];
    grille[y2][x2] = temp;
}

int mouvementValide(int grille[NB_LIGNES][NB_COLONNES], int x1, int y1, int x2, int y2)
{
    /* Étape 1 : Vérifier si les deux cases sont voisines */
    if (!estVoisin(x1, y1, x2, y2))
    {
        return 0;
    }

    /* Étape 2 : Effectuer l'échange temporaire */
    echangerItems(x1, y1, x2, y2);

    /* Étape 3 : Détecter les combinaisons après l'échange */
    int combinaisonTrouvee = detecterCombinaisons();

    /* Étape 4 : Si aucune combinaison, annuler l'échange */
    if (!combinaisonTrouvee)
    {
        echangerItems(x1, y1, x2, y2);  /* Annuler l'échange */
        return 0;
    }

    /* Étape 5 : Mouvement valide - laisser l'échange en place */
    return 1;
}