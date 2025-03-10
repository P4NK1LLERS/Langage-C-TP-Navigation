//
// Created by vfalc on 22/02/2025.
//

#ifndef TP_NAVIGATION_HISTORY_H
#define TP_NAVIGATION_HISTORY_H


typedef struct Page {
    char *  url; //Url de la page
    struct Page *previous; //L'adresse de la page précédente
} PAGE;

typedef struct History {
    struct Page* sommet;
}HISTORY;

typedef struct Noeud {
    char url[256];
    struct Noeud* suivant;
} NOEUD;


typedef struct FileAttente{
    NOEUD * debut;
    NOEUD * fin;
} FILEATTENTE;

void initialiser(HISTORY *h,HISTORY *precedent);
void afficher_historique(HISTORY *h);
void empiler(HISTORY *h);
void depiler(HISTORY *h);
void sauvegarder_historique(HISTORY * h, char*);
void charger_historique(HISTORY * h , char * );
void revenir_en_arriere(HISTORY * h , HISTORY *precedent, HISTORY *suivant);
void aller_en_avant(HISTORY *h , HISTORY *precedent, HISTORY *suivant );
void initialiser_file(FILEATTENTE *f);

#endif //TP_NAVIGATION_HISTORY_H
