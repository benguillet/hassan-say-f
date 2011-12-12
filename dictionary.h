/* 
 * File:   hashtable.h
 * Author: ludovic
 *
 * Created on 9 décembre 2011, 10:53
 */

#ifndef DICTIONARY_H
#define	DICTIONARY_H

typedef struct __element{
    char* key; 
    void* value;
    struct __element* next;
} _element;

typedef struct {
    _element* first;
    _element* last;
} dictionary;

dictionary* dictionary_new();
void dictionary_add(dictionary* dictionary, char* key, void* value);
void* dictionary_get(dictionary* dictionary, char* key);
void dictionary_set(dictionary* dictionary, char* key, void* value, int free);
void dictionary_del(dictionary* t);

void* dictionary_2d_get(dictionary* d, char *key_c, char *key_l);

#endif	/* TABLE_H */

