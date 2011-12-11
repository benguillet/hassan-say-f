#include <stdlib.h>
#include <string.h>
#include "table.h"

table* table_new() {
    return (table*)calloc(1, sizeof(_element));
}

void table_add(table* table, char* key, void* value) {    
    _element *e, *new;
    
    if (table == NULL)
        return;
    
    e = table->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return;
        }
        
        e = e->next;
    }
    
    new = (_element*)malloc(sizeof(_element));
    new->key = strcpy((char*)malloc(sizeof(char) * (strlen(key) + 1)), key);
    new->value = value;
    
    if (table->first == NULL) {
        table->first = new;
    }
    
    if (table->last != NULL) {
        table->last->next = new;
    }
    
    table->last = new;
}

void* table_get(table* table, char* key) {
    _element *e;
    
    if (table == NULL)
        return;
    
    e = table->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        
        e = e->next;
    }
    
    return NULL;
}

void table_set(table* table, char* key, void* value, int free_value) {
    _element *e, *p, *n;
    
    if (table == NULL)
        return;
    
    e = table->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            if (free_value == 1) 
                free(e->value);
            
            e->value = value;
            
            return;
        }
    }
}

void table_del(table* t) {
    _element *e, *n;
    
    if (t == NULL)
        return;
    
    n = e = t->first;
    
    while (n != NULL) {
        n = e->next;        
        free(e);        
        e = e->next;
    }
    
    free(t);
}