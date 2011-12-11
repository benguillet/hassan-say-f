/* 
 * File:   structures.h
 * Author: ludovic
 *
 * Created on 11 décembre 2011, 13:43
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#include "table.h"

typedef enum {
    EO = 1,
    OE = 2
} direction;

typedef struct {
    char* nom;
    direction direction;
    table* postes;
} train;

#endif	/* STRUCTURES_H */

