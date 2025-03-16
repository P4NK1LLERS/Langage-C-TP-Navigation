// Created by vfalc on 22/02/2025.
//

#ifndef TP_NAVIGATION_HISTORY_H
#define TP_NAVIGATION_HISTORY_H


typedef struct Page {
    char * url; //Url de la page
    struct Page *previous; //L'adresse de la page précédente
} PAGE;

typedef struct History {
    struct Page* sommet;
}HISTORY;

typedef struct FilePage {
    char* url;             // URL de la page
    struct FilePage* next; // Pointeur vers la page suivante
} FILEPAGE;

typedef struct FileAttente{
    FILEPAGE * debut;
    FILEPAGE * fin;
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
void afficher_noms_de_domaine(char*);
void afficher_sites_les_plus_visites(char*);


//############# File ###############

void initialiserFile(FILEATTENTE *f);
void ajouterFile(FILEATTENTE *f, char * );
void retirerFile(FILEATTENTE *f);
void afficherFile(FILEATTENTE *f);
void estVideFile(FILEATTENTE* f);






#endif //TP_NAVIGATION_HISTORY_H


