#include <stdlib.h>
#include "table_2d.h"

table_2d* table_2d_new() {
    table_2d* t = (table_2d*)malloc(sizeof(table_2d));
    
    t->values = NULL;
    
    return t;
}

void table_2d_add(table_2d* t, void* c, void* l, void* v) {
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

void* table_2d_get(table_2d* t, void* c, void* l) {
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

void table_2d_set(table_2d* t, void* c, void* l, void* v) {
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

void table_2d_del(table_2d* t) {
    
}

