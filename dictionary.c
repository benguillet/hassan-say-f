#include <stdlib.h>
#include "dictionary.h"

dictionary* dictionary_new(void* key, void* value) {
    dictionary_element *e = (dictionary*)malloc(sizeof(dictionary));

    e->key = key;
    e->value = value;
    e->next = NULL;

    return e;
}

void dictionary_add(dictionary* dictionary, void* key, void* value) {
    dictionary_element *e, *last, *new;

    if (dictionary == NULL)
        return;

    e = dictionary;

    while (e != NULL) {
        if (e->key == key) {
            return;
        }

        e = e->next;
    }

    new = (dictionary_element*)malloc(sizeof(dictionary_element));
    new->key = key;
    new->value = value;
    new->next = NULL;

    e = last = dictionary;

    while (e != NULL) {
        last = e;
        e = e->next;
    }

    last->next = new;
}

void* dictionary_get(dictionary* d, void* key) {
    dictionary_element *e;

    if (d == NULL)
        return NULL;

    e = d;

    while (e != NULL) {
        if (e->key == key) {
            return e->value;
        }

        e = e->next;
    }

    return NULL;
}

void dictionary_destroy(dictionary* self) {
    dictionary_element *e, *n;
    
    if (self == NULL)
        return;
        
    e = self;
    
    while (e != NULL) {
        n = e->next;
        free(e);
        e = n;
    }
}
