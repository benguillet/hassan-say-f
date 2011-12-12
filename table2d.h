/* 
 * File:   table_2d.h
 * Author: ludovic
 *
 * Created on 12 décembre 2011, 12:21
 */

#ifndef TABLE2D_H
#define	TABLE2D_H

typedef struct _element {
    void* column;
    void* line;
    void* value;
    struct _element* next;
} element;

typedef struct {
    element* values;
} table2d;

table2d* table2d_new();
void table2d_add(table2d* t, void* c, void* l, void* v);
void* table2d_get(table2d* t, void* c, void* l);
void table2d_set(table2d* t, void* c, void* l, void* v);
void table2d_del(table2d* t);

#endif	/* TABLE2D_H */

