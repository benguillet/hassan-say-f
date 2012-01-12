#include <stdlib.h>
#include <string.h>
#include "dictionary_char.h"

dictionary_char* dictionary_char_new(char* key, void* value) {
    dictionary_char *d = (dictionary_char*)malloc(sizeof(dictionary_char));

    d->key = key;
    d->value = value;
    d->next = NULL;

    return d;
}

void dictionary_char_add(dictionary_char* dictionary_char, char* key, void* value) {
    dictionary_char_element *e, *last, *new;

    if (dictionary_char == NULL)
        return;

    e = dictionary_char;

    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return;
        }

        e = e->next;
    }

    new = (dictionary_char_element*)malloc(sizeof(dictionary_char_element));
    new->key = strcpy((char*)malloc(sizeof(char) * (strlen(key) + 1)), key);
    new->value = value;
    new->next = NULL;

    e = last = dictionary_char;

    while (e != NULL) {
        last = e;
        e = e->next;
    }

    last->next = new;
}

void* dictionary_char_get(dictionary_char* dictionary_char, char* key) {
    dictionary_char_element *e;

    if (dictionary_char == NULL)
        return NULL;

    e = dictionary_char;

    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }

        e = e->next;
    }

    return NULL;
}

void dictionary_char_set(dictionary_char* d, char* key, void* value, int free_value) {
    dictionary_char_element *e;

    if (d == NULL)
        return;

    e = d;

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
    dictionary_char_element *e, *n;

    if (t == NULL)
        return;

    e = t;

    while (e != NULL) {
        n = e->next;
        free(e);
        e = n;
    }
}

void* dictionary_char_2d_get(dictionary_char* d, char *key_c, char *key_l) {
    return dictionary_char_get(dictionary_char_get(d, key_c), key_l);
}
