#include <stdio.h>
#include <stdlib.h>
#include "history.h"

// Pile - Historique
void initialiserPile(HISTORY* h) {
    h->top = -1;
}

void empiler(HISTORY* h, char* url) {
    if (h->top < MAX - 1) {
        h->top++;
        h->historique[h->top] = url;
        printf("Page added to history: %s\n", url);
    } else {
        printf("Stack is full\n");
    }
}

void depiler(HISTORY* h) {
    if (h->top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Deleted page: %s\n", h->historique[h->top]);
        h->top--;
    }
}

void afficherPile(HISTORY* h) {
    if (h->top == -1) {
        printf("No pages in history\n");
    } else {
        printf("History:\n");
        for (int i = h->top; i >= 0; i--) {
            printf("%s\n", h->historique[i]);
        }
    }
}

int estVidePile(HISTORY* h) {
    return (h->top == -1);
}

// File - Historique
void initialiserFile(FILEATTENTE* f) {
    f->front = f->rear = -1;
}

void enfiler(FILEATTENTE* f, char* url) {
    if (f->rear == MAX - 1) {
        printf("Queue is full\n");
    } else {
        if (f->front == -1) f->front = 0;
        f->rear++;
        f->historique[f->rear] = url;
        printf("Page added to history: %s\n", url);
    }
}

void defiler(FILEATTENTE* f) {
    if (f->front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Deleted page: %s\n", f->historique[f->front]);
        f->front++;
        if (f->front > f->rear) {
            f->front = f->rear = -1;
        }
    }
}

void afficherFile(FILEATTENTE* f) {
    if (f->front == -1) {
        printf("No pages in history\n");
    } else {
        printf("History:\n");
        for (int i = f->front; i <= f->rear; i++) {
            printf("%s\n", f->historique[i]);
        }
    }
}

int estVideFile(FILEATTENTE* f) {
    return (f->front == -1);
}
