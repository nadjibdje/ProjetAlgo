#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

typedef struct list {
    int element;
    struct list* suivant;
} list;



static void add(list** tete, int value,int pos) {
    list* nlist = (list*)malloc(sizeof(list));
    nlist->element = value;
    nlist->suivant = NULL;

    if (*tete == NULL) {
        *tete = nlist;
    } else {
        list* p= *tete;
        while (p->suivant != NULL) {
            p= p->suivant;
        }
        p->suivant = nlist;
    }
}


// fontion pour tester 
void afficherlist(list* tete) {
    list* p= tete;
    while (p!= NULL) {
        g_print("- > %d ", p->element);
        p= p->suivant;
    }
    printf("\n");
}
