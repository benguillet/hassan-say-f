/* 
 * File:   structures.h
 * Author: ludovic
 *
 * Created on 11 décembre 2011, 13:43
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#include "dictionary.h"
#include "table2d.h"

typedef enum {
    EO = 1,
    OE = 2
} direction;

typedef struct {
    direction direction;
    dictionary* postes;
    table2d* ressources_banquier;
} train;

#endif	/* STRUCTURES_H */

