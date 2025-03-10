#include <stdio.h>
#include <malloc.h>
#include "history.h"

int main(void) {
    HISTORY *historique = malloc(sizeof(HISTORY));
    historique->sommet = NULL;
    HISTORY *precedent = malloc(sizeof(HISTORY));
    precedent->sommet = NULL;
    HISTORY *suivant = malloc(sizeof(HISTORY));
    suivant->sommet = NULL;
    int choix;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Initialize the history\n");
        printf("2. Add a page\n");
        printf("3. Display the history\n");
        printf("4. Delete the recent page \n");
        printf("5. Save the history\n");
        printf("6. Load the history\n");
        printf("7. Last page \n");
        printf("8. Next page \n");
        printf("9. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                initialiser(historique,precedent);
                break;
            case 2 :
                empiler(historique);
                break;
            case 3:
                printf("-----Pile Historique-----");
                afficher_historique(historique);
                //printf("-----Pile Precedent-----");
                //afficher_historique(precedent);
                //printf("-----Pile suivant-----");
                //afficher_historique(suivant);

                break;
            case 4:
                depiler(historique);
                break;
            case 5:
                sauvegarder_historique(historique,"historique.txt");
                break;
            case 6:
                charger_historique(historique,"historique.txt");
                break;
            case 7:
                revenir_en_arriere(historique,precedent,suivant);
                break;
            case 8:
                aller_en_avant(historique,precedent,suivant);
                break;
            case 10:
                initialiser_file(mafile);
                break;
            case 9:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, essayez encore. \n");
        }
    }while (choix != 9);

    return 0;
}
