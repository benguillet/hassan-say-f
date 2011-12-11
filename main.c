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
#include "table.h"
#include "train.h"

int main(int argc, char** argv) {
    train TGV_1, TGV_2, TGV_3;
    pthread_t TGV_1_thread, TGV_2_thread, TGV_3_thread;
    table *postes_aiguillages = postes_new();

    // Test d'un TGV OE
    TGV_1.nom = "TGV 1";
    TGV_1.direction = OE;
    TGV_1.postes = postes_aiguillages;

    // Test d'un TGV EO
    TGV_2.nom = "TGV 2";
    TGV_2.direction = EO;
    TGV_2.postes = postes_aiguillages;

    // Test d'un TGV OE (2)
    TGV_3.nom = "TGV 3";
    TGV_3.direction = OE;
    TGV_3.postes = postes_aiguillages;

    pthread_create(&TGV_1_thread, NULL, TGV_thread_fn, &TGV_1);
    pthread_create(&TGV_2_thread, NULL, TGV_thread_fn, &TGV_2);
    pthread_create(&TGV_3_thread, NULL, TGV_thread_fn, &TGV_3);
    pthread_join(TGV_1_thread, NULL);
    pthread_join(TGV_2_thread, NULL);
    pthread_join(TGV_3_thread, NULL);
    
    postes_del(postes_aiguillages);

    return (EXIT_SUCCESS);
}