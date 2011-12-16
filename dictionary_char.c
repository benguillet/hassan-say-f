#include <stdlib.h>
#include <string.h>
#include "dictionary_char.h"

dictionary_char* dictionary_char_new() {
    return (dictionary_char*)malloc(sizeof(dictionary_char));
}

void dictionary_char_add(dictionary_char* dictionary_char, char* key, void* value) {    
    __dictionary_char_element *e, *new;
    
    if (dictionary_char == NULL)
        return;
    
    e = dictionary_char->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return;
        }
        
        e = e->next;
    }
    
    new = (__dictionary_char_element*)malloc(sizeof(__dictionary_char_element));
    new->key = strcpy((char*)malloc(sizeof(char) * (strlen(key) + 1)), key);
    new->value = value;
    
    if (dictionary_char->first == NULL) {
        dictionary_char->first = new;
    }
    
    if (dictionary_char->last != NULL) {
        dictionary_char->last->next = new;
    }
    
    dictionary_char->last = new;
}

void* dictionary_char_get(dictionary_char* dictionary_char, char* key) {
    __dictionary_char_element *e;
    
    if (dictionary_char == NULL)
        return;
    
    e = dictionary_char->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        
        e = e->next;
    }
    
    return NULL;
}

void dictionary_char_set(dictionary_char* d, char* key, void* value, int free_value) {
    __dictionary_char_element *e, *p, *n;
    
    if (d == NULL)
        return;
    
    e = d->first;
    
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            if (free_value == 1) 
                free(e->value);
            
            e->value = value;
            
            return;
        }
    }
}

void dictionary_char_del(dictionary_char* t) {
    __dictionary_char_element *e, *n;
    
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

void* dictionary_char_2d_get(dictionary_char* d, char *key_c, char *key_l) {
    return dictionary_char_get(dictionary_char_get(d, key_c), key_l);
}