#include <stdlib.h>
#include "list.h"

list* liste_new(void* v) {
    list_element *l = (list_element*)malloc(sizeof(list_element));
    
    l->value = v;
    l->next = NULL;
    
    return l;
}

void liste_add(list* l, void* v) {
    list_element *e, *p;
    
    e = l;
    p = NULL;
    
    while (e != NULL) {
        p = e;
        e = e->next;
    }
    
    e = (list_element*)malloc(sizeof(list_element));
    e->value = v;
    e->next = NULL;
    
    if (p != NULL)
        p->next = e;
}

void liste_del(list* l) {
    list *e, *n;
    
    if (l== NULL)
        return;
    
    e = l;
    
    while (e != NULL) {
        n = e->next;
        free(e);
        e = n;
    }
    
    l = NULL;
}
