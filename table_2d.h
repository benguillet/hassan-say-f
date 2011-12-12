/* 
 * File:   table_2d.h
 * Author: ludovic
 *
 * Created on 12 décembre 2011, 12:21
 */

#ifndef TABLE_2D_H
#define	TABLE_2D_H

typedef struct _element {
    void* column;
    void* line;
    void* value;
    struct _element* next;
} element;

typedef struct {
    element* values;
} table_2d;

table_2d* table_2d_new();
void table_2d_add(table_2d* t, void* c, void* l, void* v);
void* table_2d_get(table_2d* t, void* c, void* l);
void table_2d_set(table_2d* t, void* c, void* l, void* v);
void table_2d_del(table_2d* t);

#endif	/* TABLE_2D_H */

