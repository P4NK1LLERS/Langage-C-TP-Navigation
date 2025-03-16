#include <stdio.h>
#include <stdlib.h> // Remplace <malloc.h>
#include "history.h"


int main(void)
{
    
    // Aloccation de la memoire neccesaire pour chaque structure 
    
    HISTORY *historique = malloc(sizeof(HISTORY));
    historique->sommet = NULL;

    HISTORY *precedent = malloc(sizeof(HISTORY));
    precedent->sommet = NULL;

    HISTORY *suivant = malloc(sizeof(HISTORY));
    suivant->sommet = NULL;

    FILEATTENTE mafile;

    int choixPile;
    int choixFile;

    do
    {
        printf("\033[1;34m====================================\033[0m\n");
        printf("\033[1;36m|      🌟 MAIN MENU 🌟             |\033[0m\n");
        printf("\033[1;34m====================================\033[0m\n");
        printf("\033[1;34m| 1.  Pile de pages                |\033[0m\n");
        printf("\033[1;34m| 2.  File d'attente               |\033[0m\n");
        printf("\033[1;34m|__________________________________|\033[0m\n");

        printf("Votre choix: ");
        scanf("%d", &choixPile);

        switch (choixPile)
        {
        case 1:
            do
            {
                printf("\033[1;34m======================================\033[0m\n");
                printf("\033[1;36m|          📚 MENU PILE 📚           |\033[0m\n");
                printf("\033[1;34m======================================\033[0m\n");
                printf("\033[1;34m| 1.  Initialize history             |\033[0m\n");
                printf("\033[1;34m| 2.  Add a page                     |\033[0m\n");
                printf("\033[1;34m| 3.  Display history                |\033[0m\n");
                printf("\033[1;34m| 4.  Remove the most recent page    |\033[0m\n");
                printf("\033[1;34m| 5.  Save history                   |\033[0m\n");
                printf("\033[1;34m| 6.  Load history                   |\033[0m\n");
                printf("\033[1;34m| 7.  Go back to the previous page   |\033[0m\n");
                printf("\033[1;34m| 8.  Go to the next page            |\033[0m\n");
                printf("\033[1;34m| 9.  Show domain name               |\033[0m\n");
                printf("\033[1;34m| 10. Show the most visited website  |\033[0m\n");
                printf("\033[1;34m| 11. Return to the main menu        |\033[0m\n");
                printf("\033[1;34m|____________________________________|\033[0m\n");
                printf("Your choice:  ");
                scanf("%d", &choixPile);
                printf("\n");

                switch (choixPile)
                {
                case 1:
                    initialiser(historique, precedent);
                    break;
                case 2:
                    empiler(historique);
                    break;
                case 3:
                    afficher_historique(historique);
                    break;
                case 4:
                    depiler(historique);
                    break;
                case 5:
                    sauvegarder_historique(historique, "historique.txt");
                    break;
                case 6:
                    charger_historique(historique, "historique.txt");
                    break;
                case 7:
                    revenir_en_arriere(historique, precedent, suivant);
                    break;
                case 8:
                    aller_en_avant(historique, precedent, suivant);
                    break;
                case 9:
                    afficher_noms_de_domaine("historique.txt");
                    break;
                case 10:
                    afficher_sites_les_plus_visites("historique.txt");
                    break;
                case 11:
                    printf("Retour au menu principal...\n");
                    break;
                default:
                    printf("\033[1;31mChoix invalide, essayez encore.\033[0m\n");
                }
            } while (choixPile != 11);
            break;

        case 2:
            do
            {
                printf("\033[1;34m ======================================\033[0m\n");
                printf("\033[1;36m           📂 MENU FILE 📂            \033[0m\n");
                printf("\033[1;34m ======================================\033[0m\n");
                printf("\033[1;34m | 1. 🛠️ Initialiser la file           |\033[0m\n");
                printf("\033[1;34m | 2. ➕ Ajouter une page à la file   |\033[0m\n");
                printf("\033[1;34m | 3. 📜 Afficher la file             |\033[0m\n");
                printf("\033[1;34m | 4. ❌ Retirer la page récente      |\033[0m\n");
                printf("\033[1;34m | 5. 📭 Vérifier si la file est vide |\033[0m\n");
                printf("\033[1;34m | 6. 🔙 Retour au menu principal     |\033[0m\n");
                printf("\033[1;34m ======================================\033[0m\n");
                printf("Votre choix: ");
                scanf("%d", &choixFile);

                switch (choixFile)
                {
                case 1:
                    initialiserFile(&mafile);
                    break;
                case 2:
                    printf("Entrez l'URL à ajouter: ");
                    char url[100];
                    scanf("%s", url);
                    ajouterFile(&mafile, url);
                    break;
                case 3:
                    afficherFile(&mafile);
                    break;
                case 4:
                    retirerFile(&mafile);
                    break;
                case 5:
                    estVideFile(&mafile);
                    break;
                case 6:
                    printf("Retour au menu principal...\n");
                    break;
                default:
                    printf("\033[1;31mChoix invalide, essayez encore.\033[0m\n");
                }
            } while (choixFile != 6);
            break;

        default:
            printf("\033[1;31mChoix invalide, essayez encore.\033[0m\n");
        }
    } while (choixPile != 2);
    return 0;
}
