#ifndef STRUCTURES_H
#define	STRUCTURES_H

#include "dictionary_char.h"
#include "banquier.h"

typedef enum {
    EO = 1,
    OE = 2
} direction;

typedef struct {
    char* nom;
    direction direction;
    dictionary_char* postes;
    banquier* banquier;
} train;

#endif	/* STRUCTURES_H */

