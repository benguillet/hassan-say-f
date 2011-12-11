#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "postes.h"
#include "structures.h"
#include "table.h"

table* postes_new(void) {
    pthread_mutex_t *voie_A = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *voie_B = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *aiguillage_1 = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *aiguillage_2 = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *ligne_TGV = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *ligne_GL = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *tunnel = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *ligne = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

    sem_t *voie_C = (sem_t*)malloc(sizeof(sem_t)),
            *voie_D = (sem_t*)malloc(sizeof(sem_t)),
            *ligne_M_EO = (sem_t*)malloc(sizeof(sem_t)),
            *ligne_M_OE = (sem_t*)malloc(sizeof(sem_t));

    table *Gare = table_new(),
            *P0 = table_new(),
            *P1 = table_new(),
            *P2 = table_new(),
            *P3 = table_new(),
            *postes_aiguillages = table_new();

    sem_init(voie_C, 0, 2);
    sem_init(voie_D, 0, 2);
    sem_init(ligne_M_EO, 0, 2);
    sem_init(ligne_M_OE, 0, 2);

    pthread_mutex_init(voie_A, NULL);
    pthread_mutex_init(voie_B, NULL);
    pthread_mutex_init(aiguillage_1, NULL);
    pthread_mutex_init(aiguillage_2, NULL);
    pthread_mutex_init(ligne_TGV, NULL);
    pthread_mutex_init(ligne_GL, NULL);
    pthread_mutex_init(tunnel, NULL);
    pthread_mutex_init(ligne, NULL);

    table_add(Gare, "Voie C", (void*)voie_C);
    table_add(Gare, "Voie D", (void*)voie_D);

    table_add(P0, "Voie C", (void*)voie_C);
    table_add(P0, "Voie D", (void*)voie_D);
    table_add(P0, "Aiguillage 2", (void*)aiguillage_2);

    table_add(P1, "Aiguillage 1", (void*)aiguillage_1);
    table_add(P1, "Aiguillage 2", (void*)aiguillage_2);
    table_add(P1, "Ligne TGV", (void*)ligne_TGV);
    table_add(P1, "Ligne GL", (void*)ligne_GL);
    table_add(P1, "Ligne M - EO", (void*)ligne_M_EO);
    table_add(P1, "Ligne M - OE", (void*)ligne_M_OE);
    table_add(P1, "Voie A", (void*)voie_A);
    table_add(P1, "Voie B", (void*)voie_B);

    table_add(P2, "Ligne TGV", (void*)ligne_TGV);
    table_add(P2, "Ligne GL", (void*)ligne_GL);
    table_add(P2, "Ligne M - EO", (void*)ligne_M_EO);
    table_add(P2, "Ligne M - OE", (void*)ligne_M_OE);
    table_add(P2, "Tunnel", (void*)tunnel);

    table_add(P3, "Tunnel", (void*)tunnel);
    table_add(P3, "Ligne", (void*)ligne);

    table_add(postes_aiguillages, "Gare", (void*)Gare);
    table_add(postes_aiguillages, "P0", (void*)P0);
    table_add(postes_aiguillages, "P1", (void*)P1);
    table_add(postes_aiguillages, "P2", (void*)P2);
    table_add(postes_aiguillages, "P3", (void*)P3);

    return postes_aiguillages;
}

void postes_del(table* t) {
    _element *e, *n;
    
    if (t == NULL)
        return;
    
    n = e = t->first;
    
    while (n != NULL) {
        n = e->next;
        table_del((table*)e);
        e = e->next;
    }
    
    table_del(t);
}