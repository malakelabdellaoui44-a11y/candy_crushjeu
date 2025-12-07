#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grille.h"

void iniPlateau(int plateau[NB_LIGNES][NB_COLONNES]){
	for(int i = 0; i <NB_LIGNES; i++){
		for(int j = 0; j < NB_COLONNES ; j++){
			plateau[i][j] = 0;
		}
	}
}

void lirePlateau(int plateau[NB_LIGNES][NB_COLONNES]) {
    printf("  "); 
	for (int j = 0; j < NB_COLONNES; j++) {
        printf("%d ", j%10);
    }
    printf("\n  ");
	for (int j = 0; j < NB_COLONNES; j++) {
        printf("--");
    }
    printf("\n");
    for (int i = 0; i < NB_LIGNES; i++) {
        printf("%d|", i%10);
        for (int j = 0; j < NB_COLONNES; j++) {
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}

void remplirCasesVides(int grille[NB_LIGNES][NB_COLONNES]){
	srand(time(NULL));
	for (int i = 0; i < NB_LIGNES; i++) {
		for (int j = 0; j < NB_COLONNES; j++) {
			if (grille[i][j] == 0){
				int aleatoire = rand() %7 +1;
				if (aleatoire == JOKER) {
					aleatoire = rand() %8 +1;
				}
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

			bool found = true;
			int ligne = i;
			for (int k=j; k<j+4; k++) {
				if (grille[ligne][k] != case_checker && grille[ligne][k] != JOKER) {
					found = false;
				}
			}

			ligne++;
			if ((grille[ligne][j] != case_checker && grille[ligne][j] != JOKER) ||
				(grille[ligne][j+3] != case_checker && grille[ligne][j+3] != JOKER)) {
				found = false;
			}
			
			ligne++;
			if ((grille[ligne][j] != case_checker && grille[ligne][j] != JOKER) ||
				(grille[ligne][j+3] != case_checker && grille[ligne][j+3] != JOKER)) {
				found = false;
			}

			ligne++;
			for (int k=j; k<j+4; k++) {
				if (grille[ligne][k] != case_checker && grille[ligne][k] != JOKER) {
					found = false;
				}
			}
			
			if (found) {
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

			bool found = true;
			for (int k=j-2; k<=j+2; k++) {
				if (grille[i][k] != case_checker && grille[i][k] != JOKER) {
					found = false;
				}
			}

			for (int k=i-2; k<=i+2; k++) {
				if (grille[k][j] != case_checker && grille[k][j] != JOKER) {
					found = false;
				}
			}
			
			if (found) {
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
int detectersuite6x(int grille[NB_LIGNES][NB_COLONNES], int taille){
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
int detectersuite6y(int grille[NB_LIGNES][NB_COLONNES], int taille){
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

void SuppCombi(int grille[NB_LIGNES][NB_COLONNES], Combinaison combi) {
	for (int i = 0; i<combi.nb;i++) {
		int ligne = combi.item[i].ligne;
		int colonne = combi.item[i].colonne;
		grille[ligne][colonne] = 0;
	}
}

void appliquegravite(int grille[NB_LIGNES][NB_COLONNES]){

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






void suppression(int grille[NB_LIGNES][NB_COLONNES]) {
	while (true) {
    	int case6x = detectersuite6x(grille,6);
    	if (case6x != 0) {
    		effaceValeur(grille, case6x);
	    	appliquegravite(grille);
	        remplirCasesVides(grille);	
    	}

		int case6y = detectersuite6y(grille,6);
    	if (case6y != 0) {
    		effaceValeur(grille, case6y);
	    	appliquegravite(grille);
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
            SuppCombi(grille, croix);
        } else if (carre.nb > 0) {
            SuppCombi(grille, carre);
        } else if (cx.nb > 0) {
            SuppCombi(grille, cx);
        } else{
            SuppCombi(grille, cy);
        }
        
        appliquegravite(grille);
        remplirCasesVides(grille);

	}


}
