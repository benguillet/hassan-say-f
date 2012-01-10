#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include "train.h"
#include "structures.h"
#include "list.h"

void* TGV_thread_fn(void* arg) {
    train *TGV = (train*) arg;
    list *l;

    switch (TGV->direction) {
        case OE:
            l = liste_new(dictionary_char_2d_get(TGV->postes, "Gare", "Voie C"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P0", "Aiguillage 2"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P1", "Ligne TGV"));

            printf("%p - %s - OE - locking : Voie C, Aiguillage 2, Ligne TGV\n", (void*) (pthread_self()), TGV->nom);

            banquier_lock(TGV->banquier, l);

            printf("%p - %s - OE - locked : Voie C, Aiguillage 2, Ligne TGV\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(TGV->postes, "Gare", "Voie C"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P0", "Aiguillage 2"));

            printf("%p - %s - OE - releasing : Voie C, Aiguillage 2\n", (void*) (pthread_self()), TGV->nom);

            banquier_unlock(TGV->banquier, l);

            printf("%p - %s - OE - released : Voie C, Aiguillage 2\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(TGV->postes, "P2", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P3", "Ligne"));

            printf("%p - %s - OE - locking : Tunnel, Ligne\n", (void*) (pthread_self()), TGV->nom);

            banquier_lock(TGV->banquier, l);

            printf("%p - %s - OE - locked : Tunnel, Ligne\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(TGV->postes, "P1", "Ligne TGV"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P2", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P3", "Ligne"));

            printf("%p - %s - OE - releasing : Ligne TGV, Tunnel, Ligne\n", (void*) (pthread_self()), TGV->nom);

            banquier_unlock(TGV->banquier, l);

            printf("%p - %s - OE - released : Ligne TGV, Tunnel, Ligne\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            break;
        case EO:
            l = liste_new(dictionary_char_2d_get(TGV->postes, "P3", "Ligne"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P3", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P2", "Ligne TGV"));

            printf("%p - %s - EO - locking : Ligne, Tunnel, Ligne TGV\n", (void*) (pthread_self()), TGV->nom);

            banquier_lock(TGV->banquier, l);

            printf("%p - %s - EO - locked : Ligne, Tunnel, Ligne TGV\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(TGV->postes, "P3", "Ligne"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P3", "Tunnel"));

            printf("%p - %s - EO - releasing : Ligne, Tunnel\n", (void*) (pthread_self()), TGV->nom);

            banquier_unlock(TGV->banquier, l);

            printf("%p - %s - EO - released : Ligne, Tunnel\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(TGV->postes, "P1", "Aiguillage 2"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P0", "Voie D"));

            printf("%p - %s - EO - locking : Aiguillage 2, Voie D\n", (void*) (pthread_self()), TGV->nom);

            banquier_lock(TGV->banquier, l);

            printf("%p - %s - EO - locked : Aiguillage 2, Voie D\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(TGV->postes, "P2", "Ligne TGV"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P1", "Aiguillage 2"));
            liste_add(l, dictionary_char_2d_get(TGV->postes, "P0", "Voie D"));

            printf("%p - %s - EO - releasing : Ligne TGV, Aiguillage 2, Voie D\n", (void*) (pthread_self()), TGV->nom);

            banquier_unlock(TGV->banquier, l);

            printf("%p - %s - EO - released : Ligne TGV, Aiguillage 2, Voie D\n", (void*) (pthread_self()), TGV->nom);

            liste_del(l);

            break;
        default:
            perror("Erreur : TGV - direction inconnu");
            pthread_exit(NULL);
    }

    printf("%p - %s - %s - ARRIVE ------------------------------------------\n", (void*) (pthread_self()), TGV->nom, TGV->direction == OE ? "OE" : "EO");

    return NULL;
}

void* GL_thread_fn(void* arg) {
    train *GL = (train*) arg;
    list *l;

    switch (GL->direction) {
        case OE:
            l = liste_new(dictionary_char_2d_get(GL->postes, "Gare", "Voie C"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P0", "Aiguillage 2"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P1", "Ligne GL"));

            printf("%p - %s - OE - locking : Voie C, Aiguillage 2, Ligne GL\n", (void*) (pthread_self()), GL->nom);

            banquier_lock(GL->banquier, l);

            printf("%p - %s - OE - locked : Voie C, Aiguillage 2, Ligne GL\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(GL->postes, "Gare", "Voie C"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P0", "Aiguillage 2"));

            printf("%p - %s - OE - releasing : Voie C, Aiguillage 2\n", (void*) (pthread_self()), GL->nom);

            banquier_unlock(GL->banquier, l);

            printf("%p - %s - OE - released : Voie C, Aiguillage 2\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(GL->postes, "P2", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P3", "Ligne"));

            printf("%p - %s - OE - locking : Tunnel, Ligne\n", (void*) (pthread_self()), GL->nom);

            banquier_lock(GL->banquier, l);

            printf("%p - %s - OE - locked : Tunnel, Ligne\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(GL->postes, "P1", "Ligne GL"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P2", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P3", "Ligne"));

            printf("%p - %s - OE - releasing : Ligne GL, Tunnel, Ligne\n", (void*) (pthread_self()), GL->nom);

            banquier_unlock(GL->banquier, l);

            printf("%p - %s - OE - released : Ligne GL, Tunnel, Ligne\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            break;
        case EO:
            l = liste_new(dictionary_char_2d_get(GL->postes, "P3", "Ligne"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P3", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P2", "Ligne GL"));

            printf("%p - %s - EO - locking : Ligne, Tunnel, Ligne GL\n", (void*) (pthread_self()), GL->nom);

            banquier_lock(GL->banquier, l);

            printf("%p - %s - EO - locked : Ligne, Tunnel, Ligne GL\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(GL->postes, "P3", "Ligne"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P3", "Tunnel"));

            printf("%p - %s - EO - releasing : Ligne, Tunnel\n", (void*) (pthread_self()), GL->nom);

            banquier_unlock(GL->banquier, l);

            printf("%p - %s - EO - released : Ligne, Tunnel\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(GL->postes, "P1", "Aiguillage 2"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P0", "Voie D"));

            printf("%p - %s - EO - locking : Aiguillage 2, Voie D\n", (void*) (pthread_self()), GL->nom);

            banquier_lock(GL->banquier, l);

            printf("%p - %s - EO - locked : Aiguillage 2, Voie D\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(GL->postes, "P2", "Ligne GL"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P1", "Aiguillage 2"));
            liste_add(l, dictionary_char_2d_get(GL->postes, "P0", "Voie D"));

            printf("%p - %s - EO - releasing : Ligne GL, Aiguillage 2, Voie D\n", (void*) (pthread_self()), GL->nom);

            banquier_unlock(GL->banquier, l);

            printf("%p - %s - EO - released : Ligne GL, Aiguillage 2, Voie D\n", (void*) (pthread_self()), GL->nom);

            liste_del(l);

            break;
        default:
            perror("Erreur : GL - direction inconnu");
            pthread_exit(NULL);
    }

    printf("%p - %s - %s - ARRIVE ------------------------------------------\n", (void*) (pthread_self()), GL->nom, GL->direction == OE ? "OE" : "EO");

    return NULL;
}

void* M_thread_fn(void* arg) {
    train *M = (train*) arg;
    list* l;

    switch (M->direction) {
        case OE:
            l = liste_new(dictionary_char_2d_get(M->postes, "P1", "Voie A"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P1", "Aiguillage 1"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P1", "Ligne M - OE"));

            printf("%p - %s - OE - locking : Voie A, Aiguillage 1, Ligne M - OE\n", (void*) (pthread_self()), M->nom);

            banquier_lock(M->banquier, l);

            printf("%p - %s - OE - locked : Voie A, Aiguillage 1, Ligne M - OE\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(M->postes, "P1", "Voie A"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P1", "Aiguillage 1"));

            printf("%p - %s - OE - releasing : Voie A, Aiguillage 1\n", (void*) (pthread_self()), M->nom);

            banquier_unlock(M->banquier, l);

            printf("%p - %s - OE - released : Voie A, Aiguillage 1\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(M->postes, "P2", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P3", "Ligne"));

            printf("%p - %s - OE - locking : Tunnel, Ligne\n", (void*) (pthread_self()), M->nom);

            banquier_lock(M->banquier, l);

            printf("%p - %s - OE - locked : Tunnel, Ligne\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(M->postes, "P1", "Ligne M - OE"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P2", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P3", "Ligne"));

            printf("%p - %s - OE - releasing : Ligne M - OE, Tunnel, Ligne\n", (void*) (pthread_self()), M->nom);

            banquier_unlock(M->banquier, l);

            printf("%p - %s - OE - released : Ligne M - OE, Tunnel, Ligne\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            break;
        case EO:
            l = liste_new(dictionary_char_2d_get(M->postes, "P3", "Ligne"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P3", "Tunnel"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P2", "Ligne M - EO"));

            printf("%p - %s - EO - locking : Ligne, Tunnel, Ligne M - EO\n", (void*) (pthread_self()), M->nom);

            banquier_lock(M->banquier, l);

            printf("%p - %s - EO - locked : Ligne, Tunnel, Ligne M - EO\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(M->postes, "P3", "Ligne"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P3", "Tunnel"));

            printf("%p - %s - EO - releasing : Ligne, Tunnel\n", (void*) (pthread_self()), M->nom);

            banquier_unlock(M->banquier, l);

            printf("%p - %s - EO - released : Ligne, Tunnel\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(M->postes, "P1", "Aiguillage 1"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P1", "Voie B"));

            printf("%p - %s - EO - locking : Aiguillage 1, Voie B\n", (void*) (pthread_self()), M->nom);

            banquier_lock(M->banquier, l);

            printf("%p - %s - EO - locked : Aiguillage 1, Voie B\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            l = liste_new(dictionary_char_2d_get(M->postes, "P2", "Ligne M - EO"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P1", "Aiguillage 1"));
            liste_add(l, dictionary_char_2d_get(M->postes, "P1", "Voie B"));

            printf("%p - %s - EO - releasing : Ligne M - EO, Aiguillage 1, Voie B\n", (void*) (pthread_self()), M->nom);

            banquier_unlock(M->banquier, l);

            printf("%p - %s - EO - released : Ligne M - EO, Aiguillage 1, Voie B\n", (void*) (pthread_self()), M->nom);

            liste_del(l);

            break;
        default:
            perror("Erreur : M - direction inconnu");
            pthread_exit(NULL);
    }

    printf("%p - %s - %s - ARRIVE ------------------------------------------\n", (void*) (pthread_self()), M->nom, M->direction == OE ? "OE" : "EO");

    return NULL;
}
