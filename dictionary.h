/*
 * File:   dictionary.h
 * Author: ludovic
 *
 * Created on 16 décembre 2011, 10:21
 */

#ifndef DICTIONARY_H
#define	DICTIONARY_H

typedef struct __dictionary_element{
    void* key;
    void* value;
    struct __dictionary_element* next;
} dictionary_element;

typedef dictionary_element dictionary;

dictionary* dictionary_new(void* key, void* value);
void dictionary_add(dictionary* dictionary, void* key, void* value);
void* dictionary_get(dictionary* dictionary, void* key);
void dictionary_destroy(dictionary* self);

#endif	/* DICTIONARY_H */

