#include <stdlib.h>
#include "table2d.h"

table2d* table2d_new() {
    table2d* t = (table2d*)malloc(sizeof(table2d));
    
    t->values = NULL;
    
    return t;
}

void table2d_add(table2d* t, void* c, void* l, void* v) {
    element *e, *p;
    
    if (t == NULL)
        return;
    
    p = NULL;
    e = t->values;
    
    while (e != NULL) {
        if (e->column == c && e->line == l) {
            return;
        }
        
        p = e;
        e = e->next;
    }
    
    e = (element*)malloc(sizeof(element));
    e->column = c;
    e->line = l;
    e->value = v;
    e->next = NULL;

    if (p != NULL) {
        p->next = e;
    } else {
        t->values = e;
    }
}

void* table2d_get(table2d* t, void* c, void* l) {
    element *e;
    
    if (t == NULL)
        return;
    
    e = t->values;
    
    while (e != NULL) {
        if (e->column == c && e->line == l) {
            return e->value;
        }
        
        e = e->next;
    }
    
    return NULL;
}

void table2d_set(table2d* t, void* c, void* l, void* v) {
    element *e;
    
    if (t == NULL)
        return;
    
    e = t->values;
    
    while (e != NULL) {
        if (e->column == c && e->line == l) {
            e->value = v;
            return;
        }
        
        e = e->next;
    }
}

void table2d_del(table2d* t) {
    
}

