#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

typedef struct list {
    int element;
    struct list* suivant;
} list;

//fonction pour libérer la mémoire
void freeLinkedList(list* head) {
    list* current = head;
    list* next;
    while (current != NULL) {
        next = current->suivant;
        free(current); 
        current = next; 
    }
}

//fonction pour la creation
static void MathCreer(list** tete, char* token, int count) {
    if (*tete != NULL) {
        freeLinkedList(*tete);
        *tete = NULL;
    }
    
    list* current = NULL;

    while (token != NULL && count <= 10) {
        list* newNode = (list*)malloc(sizeof(list));
        newNode->element = atoi(token);
        newNode->suivant = NULL;
        if (*tete == NULL) {
            *tete = newNode; 
        } else {
            current->suivant = newNode; 
        }
        current = newNode; 
        token = strtok(NULL, ",");
        count++;
    }
}

//fonction pour l'addition
static void MathAdd(list** tete, int value, int pos) {
    list* nlist = (list*)malloc(sizeof(list));
    nlist->element = value;
    nlist->suivant = NULL;

    if (pos <= 0) {
        printf("Invalid position.\n");
        free(nlist);
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
//fonction pour la suppression

static void MathSupp(list** tete, int pos) {
    if (pos <= 0) {
        printf("Invalid position.\n");
        return;
    }

    if (pos == 1) {
        list* p = *tete;
        *tete = (*tete)->suivant;
        free(p);
    } else {
        list* p = *tete;
        int count = 1;

        while (count < pos - 1 && p->suivant != NULL) {
            p = p->suivant;
            count++;
        }

        if (p->suivant == NULL) {
            printf("Invalid position.\n");
            return;
        }

        list* q = p->suivant;
        p->suivant = q->suivant;
        free(q);
    }
}


//fonction pour la Recherche
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

//fonction pour le tri
void MathBubbleSort(list **tete) {
    int i;
    bool swapped;
    list *ptr;
    list *last = NULL;

    if (tete == NULL || (*tete)->suivant == NULL) {
        return;
    }

    do {
        swapped = false;
        ptr = *tete;

        while (ptr->suivant != last) {
            if (ptr->element > ptr->suivant->element) {
                int temp = ptr->element;
                ptr->element = ptr->suivant->element;
                ptr->suivant->element = temp;
                swapped = true;
            }
            ptr = ptr->suivant;
        }
        last = ptr;
    } while (swapped);
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
