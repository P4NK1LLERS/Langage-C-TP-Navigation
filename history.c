//
// Created by vfalc on 22/02/2025.
//

#include <stdio.h>
#include "history.h"
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialiser(HISTORY * h , HISTORY *precedent){
    h ->sommet=  NULL ;
    int n;
    printf("How many page do you want to add ? : ");
    scanf("%d",&n);

    for (int i= 1 ; i < n+1;i++){
        PAGE * new = malloc(sizeof(PAGE));
        new -> previous = NULL ;
        char * valeur = malloc(sizeof(char)*50);
        printf("##### Page [%d] #####\n",i);
        printf("Enter the page URL: ");
        scanf("%s",valeur);
        new -> url = valeur;
        if(h-> sommet != NULL){
            PAGE * newp = malloc(sizeof(PAGE));
            newp -> previous = NULL;
            newp -> url = h -> sommet -> url ;
            if(precedent -> sommet != NULL)
                newp -> previous = precedent -> sommet;
            precedent -> sommet = newp;
            new -> previous = h->sommet;

        }
        h -> sommet = new;

    }
}

void afficher_historique(HISTORY * h){
    printf("\n######### List of pages #########\n");

    if (h->sommet == NULL) {
        printf("The history is empty.");
    } else {
        PAGE *temp = h->sommet;
        while (temp != NULL) {
            printf("%s\n", temp->url);
            temp = temp->previous;
        }
    }

    printf("\n#################################\n");
}

void empiler(HISTORY *h){
    char * valeur = malloc(sizeof(char)*50);
    PAGE * new = malloc(sizeof(PAGE));
    new -> previous = NULL ;
    printf("Wich new page do you want to visit ? ");
    scanf("%s",valeur);
    new -> url = valeur;
    if(h-> sommet != NULL){
        new -> previous = h->sommet;
    }
    h -> sommet = new;

}

void depiler(HISTORY *h){
    if(h-> sommet != NULL){
        PAGE * temp = h ->sommet;
        h-> sommet = h-> sommet -> previous;
        free(temp);
        printf("#### Recent page has been succesfully deleted ####");
    }
}

void sauvegarder_historique(HISTORY * h,char * historique){
    FILE *file = fopen("historique.txt", "w+");

    if(file == NULL){
        printf("Erreur lors de l'ouverture du fichier.");
        return;
    }
    PAGE *temp = h->sommet;
    while(temp != NULL){
        fprintf(file, "%s\n", temp-> url );
        temp = temp->previous;
    }
    fclose(file);
    printf("History has been succesfully saved.");
}

void charger_historique(HISTORY *h, char *historique) {
    FILE *file = fopen("historique.txt", "r");
    if (file == NULL) return;

    HISTORY *tempPile = malloc(sizeof(HISTORY));
    tempPile->sommet = NULL;

    while (!feof(file)) {
        char *ligne = malloc(sizeof(char) * 50);
        if (fgets(ligne, 50, file) != NULL) {
            ligne[strcspn(ligne, "\n")] = '\0';
            PAGE *new = malloc(sizeof(PAGE));
            new->url = ligne;
            new->previous = tempPile->sommet;
            tempPile->sommet = new;
        }
    }
    fclose(file);

    while (tempPile->sommet != NULL) {
        PAGE *new = malloc(sizeof(PAGE));
        new->url = tempPile->sommet->url;
        new->previous = h->sommet;
        h->sommet = new;

        PAGE *toFree = tempPile->sommet;
        tempPile->sommet = tempPile->sommet->previous;
        free(toFree);
    }

    free(tempPile);
}

void revenir_en_arriere(HISTORY *h, HISTORY *precedent , HISTORY *suivant) {
    if (h->sommet == NULL || h->sommet->previous == NULL) {
        printf("Impossible de revenir en arrière.\n");
        return;
    }
    PAGE * newpr = malloc(sizeof(PAGE));

    newpr -> previous = NULL;
    newpr -> url = h -> sommet -> url ;
    if(suivant -> sommet != NULL){
        newpr -> previous = suivant -> sommet ;
    }

    suivant -> sommet = newpr;

    PAGE * current = precedent -> sommet;
    precedent -> sommet = precedent -> sommet -> previous ;
    current -> previous = h -> sommet;
    h -> sommet = current;

    printf("Retour a la page : %s\n", h->sommet->url);
}

void aller_en_avant(HISTORY *h, HISTORY *precedent , HISTORY *suivant) {
    if (h->sommet == NULL || h->sommet->previous == NULL) {
        printf("Impossible d aller a la page suivante .\n");
        return;
    }
    PAGE * newpr = malloc(sizeof(PAGE));

    newpr -> previous = NULL;
    newpr -> url = h -> sommet -> url ;
    if(precedent -> sommet != NULL){
        newpr -> previous = precedent -> sommet ;
    }

    precedent -> sommet = newpr;

    PAGE * current = suivant -> sommet;
    suivant -> sommet = suivant -> sommet -> previous ;
    current -> previous = h -> sommet;
    h -> sommet = current;

    printf("Retour a la page : %s\n", h->sommet->url);
}


// ----------------------- File FIFO ------------------------------

void initialisiserFile(FILEATTENTE *f){
    f->debut = NULL;
    f->fin = NULL;

    if (f->debut == NULL && f->fin == NULL) {
        printf("La file a bien été initialisée.\n");
    } else {
        printf("Erreur d'initialisation de la file.\n");
    }
}