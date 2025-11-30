// src/gestion_niveau.c
// ... (Vos #includes, Structures, et autres fonctions)
#include <string.h> // Ajouté si vous n'avez pas encore inclus

// --- 4. Implémentation de chargerContrat ---
 chargerContrat(int niveau, Contrat *c) {
    FILE *fichier = NULL;
    int niveauLu;

    // 1. Ouvrir le fichier en mode lecture ("r").
    // Attention au chemin d'accès ! On utilise un chemin relatif.
    fichier = fopen("data/niveaux.txt", "r");

    if (fichier == NULL) {
        printf("Erreur Critique: Le fichier des niveaux (data/niveaux.txt) est introuvable. Verifiez le chemin d'acces.\n");
        // En cas d'erreur, on peut attribuer un contrat vide pour éviter un crash complet.
        c->coupsRestants = 0;
        c->tempsRestant = 0;
        return;
    }

    // 2. Parcourir le fichier ligne par ligne (8 entiers par ligne)
    while (fscanf(fichier, "%d %d %d %d %d %d %d %d",
                  &niveauLu,
                  &c->objectifs[0], &c->objectifs[1],
                  &c->objectifs[2], &c->objectifs[3],
                  &c->objectifs[4],
                  &c->coupsRestants,
                  &c->tempsRestant) == 8) {

        // 3. Tester si le niveau lu correspond
        if (niveauLu == niveau) {
            fclose(fichier); // Fermer le fichier
            return;          // Niveau trouvé, on sort
        }
    }

    // Si la boucle se termine sans trouver le niveau demandé (ex: niveau 10 non défini)
    printf("Avertissement: Le niveau %d n'a pas ete trouve. Reinitialisation du contrat.\n", niveau);
    c->coupsRestants = 0;
    c->tempsRestant = 0;

    // 4. Fermer le fichier
    fclose(fichier);
}
