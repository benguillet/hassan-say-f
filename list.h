/* 
 * File:   list.h
 * Author: ludovic
 *
 * Created on 13 décembre 2011, 00:52
 */

#ifndef LIST_H
#define	LIST_H

typedef struct __list_element {
    void* value;
    struct __list_element* next;
} list_element;

typedef list_element list;

list* liste_new();
void liste_add(list* l, void* v);
void liste_del(list* l);

#endif	/* LIST_H */

