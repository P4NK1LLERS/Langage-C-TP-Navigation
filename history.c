//
// Created by vfalc on 22/02/2025.
//

//  formule de compilation : gcc -o main main.c history.c
// Utilisation de l'IA pour la gestion des couleurs du texte et du curseur


// ---------- Inclusion des bibliothèques ----------

#include <stdio.h>
#include "history.h"
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"

// ---------- Initialisation de l'historique ----------

void initialiser(HISTORY *h, HISTORY *precedent)
{
    h->sommet = NULL;
    int n;

    printf("\033[1;35mCombien de page voulez-vous ajouter ? : \033[0m\033[1;35m");
    fflush(stdout); // S'assurer que le texte est affiché avant la saisie
    scanf("%d", &n);
    printf("\n");

    for (int i = 1; i < n + 1; i++) // Ajouter n pages
    {
        PAGE *new = malloc(sizeof(PAGE));
        new->previous = NULL;
        char *valeur = malloc(sizeof(char) * 50);

        printf("\033[1;35m|===================== Page n° %d ======================|\033[0m\n", i);
        printf("\033[1;35m|Entrez l'url de la page : \033[0m\033[1;35m");
        scanf("%s", valeur);

        
        // Fait avec Chat Gpt //
        printf("\033[A");               // Remonter d'une ligne
        printf("\033[%dC", 55);         // Déplacer le curseur à la colonne correcte
        printf("\033[1;35m|\033[0m\n"); // Afficher la barre et revenir à la ligne
        // /////////////// //

        new->url = valeur;
        if (h->sommet != NULL) // Boucle pour gérer l'ajout de page dans l'historique
        {
            // Allouer memoire , initialiser et ajouter la page , gestion des sommet et precedent.   
            PAGE *newp = malloc(sizeof(PAGE)); 
            newp->previous = NULL; //
            newp->url = h->sommet->url;
            if (precedent->sommet != NULL)
                newp->previous = precedent->sommet;
            precedent->sommet = newp;
            new->previous = h->sommet;
        }
        h->sommet = new;
    }
    printf("\033[1;35m|______________________________________________________|\033[0m\n");
}

// ---------- Affichage de l'historique ----------

void afficher_historique(HISTORY *h)
{

    if (h->sommet == NULL) // Si la tête est null alors l'historique est vide
    {
        printf("\033[1;31m❌ L'historique est vide.\033[0m\n");
    }
    else
    {
        printf("\033[0;32m======================================\033[0m\n");
        printf("\033[1;32m|       Liste des pages visitées     |\033[0m\n");
        printf("\033[0;32m======================================\033[0m\n");
        PAGE *temp = h->sommet; 
        while (temp != NULL)
        {

            printf("\033[1;32m| %s\n", temp->url);
            
            // Fait avec Chat Gpt //
            printf("\033[%dC", 37); // Déplacer le curseur à la colonne correcte
            printf("\033[A");       // Remonter d'une ligne
            printf("\033[1;32m|\n");
            // /////////////// //

            temp = temp->previous;
        }
        printf("\033[1;32m|____________________________________|\033[0m\n");
    }
}

// ---------- Empiler une nouvelle page ----------

void empiler(HISTORY *h)
{
    char *valeur = malloc(sizeof(char) * 50);
    PAGE *new = malloc(sizeof(PAGE));
    new->previous = NULL;
    printf("\033[1;33mQuelle nouvelle page souhaitez-vous visiter ? : \033[0m\033[1;33m");
    scanf("%s", valeur);
    new->url = valeur;
    //ajoute en tête de la liste  et le relie au precedent 
    if (h->sommet != NULL) 
    {
        new->previous = h->sommet; //
    }
    h->sommet = new;
}

// ---------- Dépiler une page ----------

void depiler(HISTORY *h)
{
    if (h->sommet != NULL) // verifier que l'historique n'est pas vide
    {
        // sauvegarder la page actuelle dans une variable temporaire
        PAGE *temp = h->sommet;
        //maj du sommet pour pointer sur le precedent 
        h->sommet = h->sommet->previous;
        free(temp);
        printf("\033[1;33m✅ La page récente a été supprimée avec succès.\033[0m\033[1;33m\n");
    }
    else
    {
        printf("\033[1;31m❌ Impossible de supprimer car l'historique est vide.\033[0m\n");
    }
}

// ---------- Sauvegarder l'historique ----------

void sauvegarder_historique(HISTORY *h, char *historique)
{
    if (h->sommet == NULL) // verifier si l'historique est vide
    {
        printf("\033[1;31m❌ Impossible de sauvegarder car l'historique est vide.\033[0m\n");
        return;
    }

    FILE *file = fopen("historique.txt", "w+"); // ouvrir le fichier en mode écriture

    if (file == NULL) // verifier si le fichier s'est ouvert correctement
    {
        printf("\033[1;31m❌ Erreur lors de l'ouverture du fichier.\033[0m\n");
        return;
    }

    PAGE *temp = h->sommet;
    while (temp != NULL) // parcourir le fichier et pour récuperer les urls
    {
        fprintf(file, "%s\n", temp->url);
        temp = temp->previous;
    }

    fclose(file); 
    printf("\033[1;32m💾 L'historique a été sauvegardé avec succès.\033[0m\n");
}

// ---------- Charger l'historique ----------

void charger_historique(HISTORY *h, char *historique)
{
    FILE *file = fopen("historique.txt", "r");
    if (file == NULL)
        return;

    HISTORY *tempPile = malloc(sizeof(HISTORY));
    tempPile->sommet = NULL;

    while (!feof(file))
    {
        char *ligne = malloc(sizeof(char) * 50);
        if (fgets(ligne, 50, file) != NULL)
        {
            ligne[strcspn(ligne, "\n")] = '\0'; // supprimer le caractere de saut de ligne
            PAGE *new = malloc(sizeof(PAGE));
            new->url = ligne;
            new->previous = tempPile->sommet; // lier a l'element precedent
            tempPile->sommet = new; // maj le sommet de la pile temporaire
        }
    }
    fclose(file);

    while (tempPile->sommet != NULL)
    {
        PAGE *new = malloc(sizeof(PAGE));
        new->url = tempPile->sommet->url;
        new->previous = h->sommet; // lier a l'element precedent
        h->sommet = new; // mmaj le sommet de la pile principal

        PAGE *toFree = tempPile->sommet;
        tempPile->sommet = tempPile->sommet->previous; // passer a l'element suivant
        free(toFree); // liberer l'element precedent
    }

    free(tempPile); 
    printf("\033[1;33m📂 l'historique a ete charge avec succes.\033[0m\n");
}

// ---------- Revenir en arrière ----------

void revenir_en_arriere(HISTORY *h, HISTORY *precedent, HISTORY *suivant)
{
    if (h->sommet == NULL)
    {
        printf("\033[1;31m❌ L'historique est vide.\033[0m\n");
        return;
    }
    if (h->sommet->previous == NULL)
    {
        printf("\033[1;31m❌ Impossible de revenir en arrière.\033[0m\n");
        return;
    }

    PAGE *newpr = malloc(sizeof(PAGE));
    newpr->previous = NULL;
    newpr->url = h->sommet->url;
    if (suivant->sommet != NULL)
    {
        newpr->previous = suivant->sommet;
    }

    suivant->sommet = newpr;

    PAGE *current = precedent->sommet;
    precedent->sommet = precedent->sommet->previous;
    current->previous = h->sommet;
    h->sommet = current;

    printf("\033[1;33mRetour à la page : %s\033[0m\n", h->sommet->url);
}

// ---------- Aller en avant ----------

void aller_en_avant(HISTORY *h, HISTORY *precedent, HISTORY *suivant)
{
    if (h->sommet == NULL || h->sommet->previous == NULL)
    {
        printf("\033[1;31m❌ Impossible d'aller à la page suivante.\033[0m\n");
        return;
    }
    PAGE *newpr = malloc(sizeof(PAGE));

    newpr->previous = NULL;
    newpr->url = h->sommet->url;
    if (precedent->sommet != NULL)
    {
        newpr->previous = precedent->sommet;
    }

    precedent->sommet = newpr;

    PAGE *current = suivant->sommet;
    suivant->sommet = suivant->sommet->previous;
    current->previous = h->sommet;
    h->sommet = current;

    printf("\033[1;33mRetour à la page : %s\033[0m\n", h->sommet->url);
}

// ----------------------- File FIFO ------------------------------

void initialiserFile(FILEATTENTE *f)
{
    f->debut = NULL;
    f->fin = NULL;
}

void ajouterFile(FILEATTENTE *f, char *url)
{
    FILEPAGE *nouvellePage = malloc(sizeof(FILEPAGE));

    nouvellePage->url = malloc(strlen(url) + 1);
    strcpy(nouvellePage->url, url);

    nouvellePage->next = NULL;

    if (f->fin == NULL)
    {
        f->debut = nouvellePage;
        f->fin = nouvellePage;
    }
    else
    {
        f->fin->next = nouvellePage;
        f->fin = nouvellePage;
    }

    printf("Page ajoutée à la file : %s\n", url);
}

void retirerFile(FILEATTENTE *f)
{
    if (f->debut != NULL)
    {
        FILEPAGE *temp = f->debut;
        f->debut = f->debut->next;

        if (f->debut == NULL)
        {
            f->fin = NULL;
        }

        free(temp);
        printf("\033[1;31m❌ La première page a été retirée de la file.\033[0m\n");
    }
}

void afficherFile(FILEATTENTE *f)
{
    FILEPAGE *courant = f->debut;
    while (courant != NULL)
    {
        printf("%s -> ", courant->url);
        courant = courant->next;
    }
    printf("NULL\n");
}

void estVideFile(FILEATTENTE *f)
{
    if (f->debut == NULL)
    {
        printf("✅ La file est vide.\n");
    }
    else
    {
        printf("\033[1;31m❌ La file contient des éléments.\033[0m\n");
    }
}

// ----------------------- Partie 5  - 1 ------------------------------

void afficher_noms_de_domaine(char *nom_fichier)
{
    FILE *file = fopen(nom_fichier, "r");
    if (file == NULL)
    {
        printf("\033[1;31m❌ Erreur : impossible d'ouvrir le fichier %s\033[0m\n", nom_fichier);
        return;
    }

    printf("\033[1;33m======================================\033[0m\n");
    printf("\033[1;33m|     Liste des noms de domaine      |\033[0m\n");
    printf("\033[1;33m======================================\033[0m\n");

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), file))
    {
        ligne[strcspn(ligne, "\n")] = '\0'; // Supprimer le saut de ligne

        // Trouver "://" pour ignorer le protocole
        char *debut = strstr(ligne, "://");
        debut = (debut) ? debut + 3 : ligne;

        // Copier le domaine jusqu'au prochain "/"
        char *slash = strchr(debut, '/');
        int len = (slash) ? slash - debut : strlen(debut);

        char domaine[256];
        strncpy(domaine, debut, len);
        domaine[len] = '\0';

        // Supprimer "www." si présent
        if (strncmp(domaine, "www.", 4) == 0)
        {
            printf("\033[1;33m| %s\033[0m\n", domaine + 4);
            // Fait avec Chat Gpt //
            printf("\033[%dC", 37); // Déplacer le curseur à la colonne correcte
            printf("\033[A");       // Remonter d'une ligne
            printf("\033[1;33m|\n");
            // /////////////// //
        }
        else
        {
            printf("\033[1;33m| %s\033[0m\n", domaine);
            // Fait avec Chat Gpt //
            rintf("\033[%dC", 37); // Déplacer le curseur à la colonne correcte
            printf("\033[A");       // Remonter d'une ligne
            printf("\033[1;33m|\n");
            // /////////////// //
        }
    }

    fclose(file);
    printf("\033[1;33m|____________________________________|\033[0m\n");
}

// ----------------------- Partie 5 - 2  ------------------------------

void afficher_sites_les_plus_visites(char *nom_fichier)
{
    FILE *file = fopen(nom_fichier, "r");
    if (file == NULL)
    {
        printf("\033[1;31m❌ Erreur : impossible d'ouvrir le fichier %s\033[0m\n", nom_fichier);
        return;
    }

    HISTORY *historique = malloc(sizeof(HISTORY));
    historique->sommet = NULL;

    while (!feof(file))
    {
        char *ligne = malloc(sizeof(char) * 50);
        if (fgets(ligne, 50, file) != NULL)
        {
            ligne[strcspn(ligne, "\n")] = '\0';
            PAGE *new = malloc(sizeof(PAGE));
            new->url = ligne;
            new->previous = historique->sommet;
            historique->sommet = new;
        }
    }

    fclose(file);

    // ---------- Trier et afficher les sites les plus visités ----------

    // Compter les occurrences des URLs
    typedef struct URLCount
    {
        char *url;
        int count;
        struct URLCount *next;
    } URLCount;

    URLCount *head = NULL;

    PAGE *current = historique->sommet;
    while (current != NULL)
    {
        URLCount *uc = head;
        while (uc != NULL && strcmp(uc->url, current->url) != 0)
        {
            uc = uc->next;
        }
        if (uc == NULL)
        {
            uc = malloc(sizeof(URLCount));
            uc->url = current->url;
            uc->count = 1;
            uc->next = head;
            head = uc;
        }
        else
        {
            uc->count++;
        }
        current = current->previous;
    }

    // Trier les URLs par nombre de visites (tri par insertion)
    URLCount *sorted = NULL;
    URLCount *uc = head;
    while (uc != NULL)
    {
        URLCount *next = uc->next;
        if (sorted == NULL || sorted->count < uc->count)
        {
            uc->next = sorted;
            sorted = uc;
        }
        else
        {
            URLCount *current = sorted;
            while (current->next != NULL && current->next->count >= uc->count)
            {
                current = current->next;
            }
            uc->next = current->next;
            current->next = uc;
        }
        uc = next;
    }

    printf("\033[1;35m=========================================\033[0m\n");
    printf("\033[1;35m|          MOST VISITED WEBSITE         |\033[0m\n");
    printf("\033[1;35m=========================================\033[0m\n");
    uc = sorted;
    while (uc != NULL)
    {
        if (uc->count == 1)
        {
            printf("\033[1;35m| %s - %d visite\033[0m\n", uc->url, uc->count);
            // Fait avec Chat Gpt //
            printf("\033[%dC", 40); // Déplacer le curseur à la colonne correcte
            printf("\033[A");       // Remonter d'une ligne
            printf("\033[1;35m|\n");
            // /////////////// //
        }
        else
        {
            printf("\033[1;35m| %s - %d visites\033[0m\n", uc->url, uc->count);
            // Fait avec Chat Gpt //
            printf("\033[%dC", 40); // Déplacer le curseur à la colonne correcte
            printf("\033[A");       // Remonter d'une ligne
            printf("\033[1;35m|\n");
            // /////////////// //
        }
        uc = uc->next;
    }
    printf("\033[1;35m|_______________________________________|\033[0m\n");

    // Libérer la mémoire
    while (sorted != NULL)
    {
        URLCount *temp = sorted;
        sorted = sorted->next;
        free(temp);
    }
}
