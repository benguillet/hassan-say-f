/*
 * File:   hashtable.h
 * Author: ludovic
 *
 * Created on 9 décembre 2011, 10:53
 */

#ifndef DICTIONARY_CHAR_H
#define	DICTIONARY_CHAR_H

typedef struct __dictionary_char_element{
    char* key;
    void* value;
    struct __dictionary_char_element* next;
} dictionary_char_element;

typedef dictionary_char_element dictionary_char;

dictionary_char* dictionary_char_new(char* key, void* value);
void dictionary_char_add(dictionary_char* dictionary_char, char* key, void* value);
void* dictionary_char_get(dictionary_char* dictionary_char, char* key);
void dictionary_char_set(dictionary_char* dictionary_char, char* key, void* value, int free);
void dictionary_char_del(dictionary_char* t);

void* dictionary_char_2d_get(dictionary_char* d, char *key_c, char *key_l);

#endif	/* DICTIONARY_CHAR_H */

