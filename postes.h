/* 
 * File:   poste.h
 * Author: ludovic
 *
 * Created on 9 décembre 2011, 00:07
 */

#ifndef POSTES_H
#define	POSTES_H

#include "dictionary.h"

dictionary* postes_new(void);
void postes_del(dictionary* postes_aiguillages);

#endif	/* POSTES_H */

