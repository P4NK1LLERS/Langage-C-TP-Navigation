#ifndef HISTORY_H
#define HISTORY_H

#define MAX 10

typedef struct {
    char* historique[MAX];
    int top;
} HISTORY;

typedef struct {
    char* historique[MAX];
    int front, rear;
} FILEATTENTE;

// Fonction pile
void initialiserPile(HISTORY* h);
void empiler(HISTORY* h, char* url);
void depiler(HISTORY* h);
void afficherPile(HISTORY* h);
int estVidePile(HISTORY* h);

// Fonction file
void initialiserFile(FILEATTENTE* f);
void enfiler(FILEATTENTE* f, char* url);
void defiler(FILEATTENTE* f);
void afficherFile(FILEATTENTE* f);
int estVideFile(FILEATTENTE* f);

#endif
