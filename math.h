#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

typedef struct list {
    int element;
    struct list* suivant;
} list;



static void add(list** tete, int value, int pos) {
    list* nlist = (list*)malloc(sizeof(list));
    nlist->element = value;
    nlist->suivant = NULL;

    if (pos <= 0) {
        printf("Invalid position.\n");
        free(nlist); // Free the allocated memory for the node
        return;
    }

    if (pos == 1 || *tete == NULL) {
        nlist->suivant = *tete;
        *tete = nlist;
    } else {
        list* p = *tete;
        int count = 1;

        while (count < pos - 1 && p->suivant != NULL) {
            p = p->suivant;
            count++;
        }

        nlist->suivant = p->suivant;
        p->suivant = nlist;
    }
}


static bool MathSearch(list* tete, int value) {
    list* p= tete;
    int i= 0;
    while (p!= NULL) {
        if (p->element == value) {
            return true;
        }
        p= p->suivant;
        i++;
    }
    return false;

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
