#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "dictionary_char.h"
#include "train.h"
#include "banquier.h"

#define NB_TRAINS 100

dictionary_char* projet_postes_new(void);
void projet_postes_del(dictionary_char* postes_aiguillages);

banquier* projet_banquier_new(dictionary_char* postes);

int main(int argc, char* argv[]) {
    int i, nb_trains = (argc > 1 ? atoi(argv[1]) : NB_TRAINS); /* nb trains définis en paramètre ou via la constante */
    char* nom;

    train* trains = (train*) malloc(sizeof (train) * nb_trains);
    pthread_t* trains_threads = (pthread_t*) malloc(sizeof (pthread_t) * nb_trains);

    /* Création d'un ensemble de postes d'aiguillages spécifique à notre réseau ferroviaire (projet) */
    dictionary_char *postes_aiguillages = projet_postes_new();

    /* Création d'un banquier spécifique à notre réseau ferroviaire (projet) */
    banquier *banquier = projet_banquier_new(postes_aiguillages);

    srand(time(NULL));

    for (i = 0; i < nb_trains; ++i) {
        nom = malloc(sizeof(char) * 15);

        switch (rand() % 3) {
            case 0: /* TGV */
                sprintf(nom, "TGV %d", i);

                trains[i].nom = nom;
                trains[i].postes = postes_aiguillages;
                trains[i].banquier = banquier;

                switch (rand() % 2) {
                    case 0:
                        trains[i].direction = OE;
                        break;
                    case 1:
                        trains[i].direction = EO;
                        break;
                }

                pthread_create(&(trains_threads[i]), NULL, TGV_thread_fn, &(trains[i]));
                pthread_setschedprio(trains_threads[i], 16);

                break;
            case 1: /* GL */
                sprintf(nom, "GL  %d", i);

                trains[i].nom = nom;
                trains[i].postes = postes_aiguillages;
                trains[i].banquier = banquier;

                switch (rand() % 2) {
                    case 0:
                        trains[i].direction = OE;
                        break;
                    case 1:
                        trains[i].direction = EO;
                        break;
                }

                pthread_create(&(trains_threads[i]), NULL, GL_thread_fn, &(trains[i]));
                pthread_setschedprio(trains_threads[i], 4);

                break;
            case 2: /* M */
                sprintf(nom, "M   %d", i);

                trains[i].nom = nom;
                trains[i].postes = postes_aiguillages;
                trains[i].banquier = banquier;

                switch (rand() % 2) {
                    case 0:
                        trains[i].direction = OE;
                        break;
                    case 1:
                        trains[i].direction = EO;
                        break;
                }

                pthread_create(&(trains_threads[i]), NULL, M_thread_fn, &(trains[i]));
                pthread_setschedprio(trains_threads[i], 1);

                break;
        }

    }

    for (i = 0; i < nb_trains; ++i) {
        pthread_join(trains_threads[i], NULL);
    }

    banquier_destroy(banquier);

    return (EXIT_SUCCESS);
}

dictionary_char* projet_postes_new(void) {
    sem_t *voie_A = (sem_t*) malloc(sizeof (sem_t)),
            *voie_B = (sem_t*) malloc(sizeof (sem_t)),
            *voie_C = (sem_t*) malloc(sizeof (sem_t)),
            *voie_D = (sem_t*) malloc(sizeof (sem_t)),
            *ligne_M_EO = (sem_t*) malloc(sizeof (sem_t)),
            *ligne_M_OE = (sem_t*) malloc(sizeof (sem_t)),
            *aiguillage_1 = (sem_t*) malloc(sizeof (sem_t)),
            *aiguillage_2 = (sem_t*) malloc(sizeof (sem_t)),
            *ligne_TGV = (sem_t*) malloc(sizeof (sem_t)),
            *ligne_GL = (sem_t*) malloc(sizeof (sem_t)),
            *tunnel = (sem_t*) malloc(sizeof (sem_t)),
            *ligne = (sem_t*) malloc(sizeof (sem_t));

    dictionary_char *Gare, *P0, *P1, *P2, *P3, *postes_aiguillages;

    sem_init(voie_A, 0, 2);
    sem_init(voie_B, 0, 2);
    sem_init(voie_C, 0, 2);
    sem_init(voie_D, 0, 2);
    sem_init(ligne_M_EO, 0, 2);
    sem_init(ligne_M_OE, 0, 2);

    sem_init(aiguillage_1, 0, 1);
    sem_init(aiguillage_2, 0, 1);
    sem_init(ligne_TGV, 0, 1);
    sem_init(ligne_GL, 0, 1);
    sem_init(tunnel, 0, 1);
    sem_init(ligne, 0, 1);

    Gare = dictionary_char_new("Voie C", (void*) voie_C);
    dictionary_char_add(Gare, "Voie D", (void*) voie_D);

    P0 = dictionary_char_new("Voie C", (void*) voie_C);
    dictionary_char_add(P0, "Voie D", (void*) voie_D);
    dictionary_char_add(P0, "Aiguillage 2", (void*) aiguillage_2);

    P1 = dictionary_char_new("Aiguillage 1", (void*) aiguillage_1);
    dictionary_char_add(P1, "Aiguillage 2", (void*) aiguillage_2);
    dictionary_char_add(P1, "Ligne TGV", (void*) ligne_TGV);
    dictionary_char_add(P1, "Ligne GL", (void*) ligne_GL);
    dictionary_char_add(P1, "Ligne M - EO", (void*) ligne_M_EO);
    dictionary_char_add(P1, "Ligne M - OE", (void*) ligne_M_OE);
    dictionary_char_add(P1, "Voie A", (void*) voie_A);
    dictionary_char_add(P1, "Voie B", (void*) voie_B);

    P2 = dictionary_char_new("Ligne TGV", (void*) ligne_TGV);
    dictionary_char_add(P2, "Ligne GL", (void*) ligne_GL);
    dictionary_char_add(P2, "Ligne M - EO", (void*) ligne_M_EO);
    dictionary_char_add(P2, "Ligne M - OE", (void*) ligne_M_OE);
    dictionary_char_add(P2, "Tunnel", (void*) tunnel);

    P3 = dictionary_char_new("Tunnel", (void*) tunnel);
    dictionary_char_add(P3, "Ligne", (void*) ligne);

    postes_aiguillages = dictionary_char_new("Gare", (void*) Gare);
    dictionary_char_add(postes_aiguillages, "P0", (void*) P0);
    dictionary_char_add(postes_aiguillages, "P1", (void*) P1);
    dictionary_char_add(postes_aiguillages, "P2", (void*) P2);
    dictionary_char_add(postes_aiguillages, "P3", (void*) P3);

    return postes_aiguillages;
}

void projet_postes_del(dictionary_char* self) {
    dictionary_char_element *e, *n;

    if (self == NULL)
        return;

    e = self;

    while (e != NULL) {
        n = e->next;
        dictionary_char_del(e);
        e = n;
    }

    dictionary_char_del(self);
}


/**
 * Création d'un banquier spécifique à notre réseau ferroviaire
 * @param postes
 * @return banquier*
 */
banquier* projet_banquier_new(dictionary_char* postes) {
    dictionary *p;

    int *voie_A = (int*) malloc(sizeof (int)),
            *voie_B = (int*) malloc(sizeof (int)),
            *voie_C = (int*) malloc(sizeof (int)),
            *voie_D = (int*) malloc(sizeof (int)),
            *ligne_M_EO = (int*) malloc(sizeof (int)),
            *ligne_M_OE = (int*) malloc(sizeof (int)),
            *aiguillage_1 = (int*) malloc(sizeof (int)),
            *aiguillage_2 = (int*) malloc(sizeof (int)),
            *ligne_TGV = (int*) malloc(sizeof (int)),
            *ligne_GL = (int*) malloc(sizeof (int)),
            *tunnel = (int*) malloc(sizeof (int)),
            *ligne = (int*) malloc(sizeof (int));

    *voie_A = *voie_B = *voie_C = *voie_D = *ligne_M_EO = *ligne_M_OE = 2;
    *aiguillage_1 = *aiguillage_2 = *ligne_TGV = *ligne_GL = *tunnel = *ligne = 1;

    p = dictionary_new(dictionary_char_2d_get(postes, "P1", "Voie A"), voie_A);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Voie B"), voie_B);
    dictionary_add(p, dictionary_char_2d_get(postes, "Gare", "Voie C"), voie_C);
    dictionary_add(p, dictionary_char_2d_get(postes, "Gare", "Voie D"), voie_D);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Aiguillage 1"), aiguillage_1);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Aiguillage 2"), aiguillage_2);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Ligne TGV"), ligne_TGV);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Ligne M - EO"), ligne_M_EO);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Ligne M - OE"), ligne_M_OE);
    dictionary_add(p, dictionary_char_2d_get(postes, "P1", "Ligne GL"), ligne_GL);
    dictionary_add(p, dictionary_char_2d_get(postes, "P2", "Tunnel"), tunnel);
    dictionary_add(p, dictionary_char_2d_get(postes, "P3", "Ligne"), ligne);

    return banquier_new(p);
}
