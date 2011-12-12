#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "postes.h"
#include "structures.h"
#include "dictionary.h"

dictionary* postes_new(void) {
    pthread_mutex_t *aiguillage_1 = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *aiguillage_2 = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *ligne_TGV = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *ligne_GL = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *tunnel = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)),
            *ligne = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

    sem_t *voie_A = (sem_t*)malloc(sizeof(sem_t)),
            *voie_B = (sem_t*)malloc(sizeof(sem_t)),
            *voie_C = (sem_t*)malloc(sizeof(sem_t)),
            *voie_D = (sem_t*)malloc(sizeof(sem_t)),
            *ligne_M_EO = (sem_t*)malloc(sizeof(sem_t)),
            *ligne_M_OE = (sem_t*)malloc(sizeof(sem_t));

    dictionary *Gare = dictionary_new(),
            *P0 = dictionary_new(),
            *P1 = dictionary_new(),
            *P2 = dictionary_new(),
            *P3 = dictionary_new(),
            *postes_aiguillages = dictionary_new();

    sem_init(voie_A, 0, 2);
    sem_init(voie_B, 0, 2);
    sem_init(voie_C, 0, 2);
    sem_init(voie_D, 0, 2);
    sem_init(ligne_M_EO, 0, 2);
    sem_init(ligne_M_OE, 0, 2);
    
    pthread_mutex_init(aiguillage_1, NULL);
    pthread_mutex_init(aiguillage_2, NULL);
    pthread_mutex_init(ligne_TGV, NULL);
    pthread_mutex_init(ligne_GL, NULL);
    pthread_mutex_init(tunnel, NULL);
    pthread_mutex_init(ligne, NULL);

    dictionary_add(Gare, "Voie C", (void*)voie_C);
    dictionary_add(Gare, "Voie D", (void*)voie_D);

    dictionary_add(P0, "Voie C", (void*)voie_C);
    dictionary_add(P0, "Voie D", (void*)voie_D);
    dictionary_add(P0, "Aiguillage 2", (void*)aiguillage_2);

    dictionary_add(P1, "Aiguillage 1", (void*)aiguillage_1);
    dictionary_add(P1, "Aiguillage 2", (void*)aiguillage_2);
    dictionary_add(P1, "Ligne TGV", (void*)ligne_TGV);
    dictionary_add(P1, "Ligne GL", (void*)ligne_GL);
    dictionary_add(P1, "Ligne M - EO", (void*)ligne_M_EO);
    dictionary_add(P1, "Ligne M - OE", (void*)ligne_M_OE);
    dictionary_add(P1, "Voie A", (void*)voie_A);
    dictionary_add(P1, "Voie B", (void*)voie_B);

    dictionary_add(P2, "Ligne TGV", (void*)ligne_TGV);
    dictionary_add(P2, "Ligne GL", (void*)ligne_GL);
    dictionary_add(P2, "Ligne M - EO", (void*)ligne_M_EO);
    dictionary_add(P2, "Ligne M - OE", (void*)ligne_M_OE);
    dictionary_add(P2, "Tunnel", (void*)tunnel);

    dictionary_add(P3, "Tunnel", (void*)tunnel);
    dictionary_add(P3, "Ligne", (void*)ligne);

    dictionary_add(postes_aiguillages, "Gare", (void*)Gare);
    dictionary_add(postes_aiguillages, "P0", (void*)P0);
    dictionary_add(postes_aiguillages, "P1", (void*)P1);
    dictionary_add(postes_aiguillages, "P2", (void*)P2);
    dictionary_add(postes_aiguillages, "P3", (void*)P3);

    return postes_aiguillages;
}

void postes_del(dictionary* t) {
    _element *e, *n;
    
    if (t == NULL)
        return;
    
    n = e = t->first;
    
    while (n != NULL) {
        n = e->next;
        dictionary_del((dictionary*)e);
        e = e->next;
    }
    
    dictionary_del(t);
}