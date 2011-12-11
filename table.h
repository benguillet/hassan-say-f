/* 
 * File:   hashtable.h
 * Author: ludovic
 *
 * Created on 9 décembre 2011, 10:53
 */

#ifndef TABLE_H
#define	TABLE_H

typedef struct __element{
    char* key; 
    void* value;
    struct __element* next;
} _element;

typedef struct {
    _element* first;
    _element* last;
} table;

table* table_new();
void table_add(table* table, char* key, void* value);
void* table_get(table* table, char* key);
void table_set(table* table, char* key, void* value, int free);
void table_del(table* t);


#endif	/* TABLE_H */

