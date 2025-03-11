// 
// Created by vfalc on 22/02/2025.
// Stylisé avec des emojis pour une meilleure lisibilité et organisation
//

#include <stdio.h>
#include "history.h"
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"

// ----------📜 Initialisation de l'historique ----------

void initialiser(HISTORY *h, HISTORY *precedent) {
    h->sommet = NULL;
    int n;
    printf("📚 Combien de pages voulez-vous ajouter ? : ");
    scanf("%d", &n);

    for (int i = 1; i < n + 1; i++) {
        PAGE *new = malloc(sizeof(PAGE));
        new->previous = NULL;
        char *valeur = malloc(sizeof(char) * 50);
        printf("##### Page [%d] #####\n", i);
        printf("🔗 Entrez l'URL de la page : ");
        scanf("%s", valeur);
        new->url = valeur;
        if (h->sommet != NULL) {
            PAGE *newp = malloc(sizeof(PAGE));
            newp->previous = NULL;
            newp->url = h->sommet->url;
            if (precedent->sommet != NULL)
                newp->previous = precedent->sommet;
            precedent->sommet = newp;
            new->previous = h->sommet;
        }
        h->sommet = new;
    }
}

// ----------📖 Affichage de l'historique ----------

void afficher_historique(HISTORY *h) {
    printf("\n######### 📜 Liste des pages visitées 📜 #########\n");

    if (h->sommet == NULL) {
        printf("❌ L'historique est vide.");
    } else {
        PAGE *temp = h->sommet;
        while (temp != NULL) {
            printf("🔗 %s\n", temp->url);
            temp = temp->previous;
        }
    }

    printf("\n###############################################\n");
}

// ----------📥 Empiler une nouvelle page ----------

void empiler(HISTORY *h) {
    char *valeur = malloc(sizeof(char) * 50);
    PAGE *new = malloc(sizeof(PAGE));
    new->previous = NULL;
    printf("🌐 Quelle nouvelle page souhaitez-vous visiter ? ");
    scanf("%s", valeur);
    new->url = valeur;
    if (h->sommet != NULL) {
        new->previous = h->sommet;
    }
    h->sommet = new;
}

// ----------📤 Dépiler une page ----------

void depiler(HISTORY *h) {
    if (h->sommet != NULL) {
        PAGE *temp = h->sommet;
        h->sommet = h->sommet->previous;
        free(temp);
        printf("✅ La page récente a été supprimée avec succès.\n");
    }
}

// ----------💾 Sauvegarder l'historique ----------

void sauvegarder_historique(HISTORY *h, char *historique) {
    FILE *file = fopen("historique.txt", "w+");

    if (file == NULL) {
        printf("❌ Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    PAGE *temp = h->sommet;
    while (temp != NULL) {
        fprintf(file, "%s\n", temp->url);
        temp = temp->previous;
    }
    fclose(file);
    printf("💾 L'historique a été sauvegardé avec succès.\n");
}

// ----------📂 Charger l'historique ----------

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
    printf("📂 L'historique a été chargé avec succès.\n");
}

// ----------🔙 Revenir en arrière ----------

void revenir_en_arriere(HISTORY *h, HISTORY *precedent, HISTORY *suivant) {
    if (h->sommet == NULL || h->sommet->previous == NULL) {
        printf("❌ Impossible de revenir en arrière.\n");
        return;
    }
    PAGE *newpr = malloc(sizeof(PAGE));

    newpr->previous = NULL;
    newpr->url = h->sommet->url;
    if (suivant->sommet != NULL) {
        newpr->previous = suivant->sommet;
    }

    suivant->sommet = newpr;

    PAGE *current = precedent->sommet;
    precedent->sommet = precedent->sommet->previous;
    current->previous = h->sommet;
    h->sommet = current;

    printf("↩ Retour à la page : %s\n", h->sommet->url);
}

// ----------🔜 Aller en avant ----------

void aller_en_avant(HISTORY *h, HISTORY *precedent, HISTORY *suivant) {
    if (h->sommet == NULL || h->sommet->previous == NULL) {
        printf("❌ Impossible d'aller à la page suivante.\n");
        return;
    }
    PAGE *newpr = malloc(sizeof(PAGE));

    newpr->previous = NULL;
    newpr->url = h->sommet->url;
    if (precedent->sommet != NULL) {
        newpr->previous = precedent->sommet;
    }

    precedent->sommet = newpr;

    PAGE *current = suivant->sommet;
    suivant->sommet = suivant->sommet->previous;
    current->previous = h->sommet;
    h->sommet = current;

    printf("🔜 Retour à la page : %s\n", h->sommet->url);
}

// ----------------------- 📋 File FIFO ------------------------------

void initialiserFile(FILEATTENTE *f) {
    f->debut = NULL;
    f->fin = NULL;
}

void ajouterFile(FILEATTENTE *f, char *url) {
    FILEPAGE *nouvellePage = malloc(sizeof(FILEPAGE));

    nouvellePage->url = malloc(strlen(url) + 1);
    strcpy(nouvellePage->url, url);

    nouvellePage->next = NULL;

    if (f->fin == NULL) {
        f->debut = nouvellePage;
        f->fin = nouvellePage;
    } else {
        f->fin->next = nouvellePage;
        f->fin = nouvellePage;
    }

    printf("📑 Page ajoutée à la file : %s\n", url);
}

void retirerFile(FILEATTENTE *f) {
    if (f->debut != NULL) {
        FILEPAGE *temp = f->debut;
        f->debut = f->debut->next;

        if (f->debut == NULL) {
            f->fin = NULL;
        }

        free(temp);
        printf("❌ La première page a été retirée de la file.\n");
    }
}

void afficherFile(FILEATTENTE *f) {
    FILEPAGE *courant = f->debut;
    while (courant != NULL) {
        printf("%s -> ", courant->url);
        courant = courant->next;
    }
    printf("NULL\n");
}

void estVideFile(FILEATTENTE *f) {
    if (f->debut == NULL) {
        printf("✅ La file est vide.\n");
    } else {
        printf("❌ La file contient des éléments.\n");
    }
}
