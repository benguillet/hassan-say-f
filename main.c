/*
 * File:   main.c
 * Author: ludovic
 *
 * Created on 8 décembre 2011, 17:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "postes.h"
#include "structures.h"
#include "dictionary.h"
#include "train.h"

int main(int argc, char** argv) {
    train M_1, GL_1, M_2;
    pthread_t M_1_thread, GL_1_thread, M_2_thread;
    dictionary *postes_aiguillages = postes_new();

    // Test d'un M OE
    M_1.nom = "M 1";
    M_1.direction = OE;
    M_1.postes = postes_aiguillages;

    // Test d'un M EO
    M_2.nom = "M 2";
    M_2.direction = EO;
    M_2.postes = postes_aiguillages;

    // Test d'un GL OE
    GL_1.nom = "GL 1";
    GL_1.direction = OE;
    GL_1.postes = postes_aiguillages;

    pthread_create(&M_1_thread, NULL, M_thread_fn, &M_1);
    pthread_create(&M_2_thread, NULL, M_thread_fn, &M_2);
/*
    pthread_create(&GL_1_thread, NULL, GL_thread_fn, &GL_1);
*/
    pthread_join(M_1_thread, NULL);
    pthread_join(M_2_thread, NULL);
/*
    pthread_join(GL_1_thread, NULL);
*/
    
    postes_del(postes_aiguillages);

    return (EXIT_SUCCESS);
}