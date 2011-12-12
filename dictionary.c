#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

dictionary* dictionary_new() {
    return (dictionary*)calloc(1, sizeof(_element));
}

void dictionary_add(dictionary* dictionary, char* key, void* value) {    
    _element *e, *new;
    
    if (dictionary == NULL)
        return;
    
    e = dictionary->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return;
        }
        
        e = e->next;
    }
    
    new = (_element*)malloc(sizeof(_element));
    new->key = strcpy((char*)malloc(sizeof(char) * (strlen(key) + 1)), key);
    new->value = value;
    
    if (dictionary->first == NULL) {
        dictionary->first = new;
    }
    
    if (dictionary->last != NULL) {
        dictionary->last->next = new;
    }
    
    dictionary->last = new;
}

void* dictionary_get(dictionary* dictionary, char* key) {
    _element *e;
    
    if (dictionary == NULL)
        return;
    
    e = dictionary->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        
        e = e->next;
    }
    
    return NULL;
}

void dictionary_set(dictionary* dictionary, char* key, void* value, int free_value) {
    _element *e, *p, *n;
    
    if (dictionary == NULL)
        return;
    
    e = dictionary->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            if (free_value == 1) 
                free(e->value);
            
            e->value = value;
            
            return;
        }
    }
}

void dictionary_del(dictionary* t) {
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

void* dictionary_2d_get(dictionary* d, char *key_c, char *key_l) {
    return dictionary_get(dictionary_get(d, key_c), key_l);
}