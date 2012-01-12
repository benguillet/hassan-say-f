#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "banquier.h"
#include "list.h"

banquier* banquier_new(dictionary *ressources_disponibles) {
    banquier *b = (banquier*) malloc(sizeof (banquier));

    b->disponibilites = ressources_disponibles;

    pthread_mutex_init(&b->mutex_modification, NULL);

    return b;
}

void banquier_lock(banquier* self, list* semaphores) {
    short is_dispo;
    list_element *l;
    dictionary_element *d;

    if (semaphores == NULL || self->disponibilites == NULL)
        return;

    do {
        pthread_mutex_lock(&self->mutex_modification);

        d = self->disponibilites;
        is_dispo = 1;

        while (d != NULL && is_dispo == 1) {
            l = semaphores;

            while (l != NULL && is_dispo == 1) {
                if (l->value == d->key && *(int*) (d->value) == 0) {
                    is_dispo = 0 && is_dispo;
                }

                l = l->next;
            }

            d = d->next;
        }

        if (is_dispo == 1) {
            d = self->disponibilites;

            while (d != NULL) {
                l = semaphores;

                while (l != NULL) {
                    if (l->value == d->key)
                        *(int*) (d->value) -= 1;

                    l = l->next;
                }

                d = d->next;
            }

            l = semaphores;

            while (l != NULL) {
                sem_wait((sem_t*) (l->value));

                l = l->next;
            }
        }

        pthread_mutex_unlock(&self->mutex_modification);
    } while (is_dispo == 0);
}

void banquier_unlock(banquier* self, list* l) {
    list_element *e;
    dictionary_element* d;

    if (l == NULL || self->disponibilites == NULL)
        return;

    pthread_mutex_lock(&self->mutex_modification);

    d = self->disponibilites;

    while (d != NULL) {
        e = l;

        while (e != NULL) {
            if (e->value == d->key) {
                *(int*) (d->value) += 1;
            }

            e = e->next;
        }

        d = d->next;
    }

    e = l;

    while (e != NULL) {
        sem_post((sem_t*) (e->value));

        e = e->next;
    }

    pthread_mutex_unlock(&self->mutex_modification);
}

char* banquier_disponibilites_tostring(banquier* self) {
    dictionary_element *e;
    char *str = calloc(1000, sizeof (char)), *tmp = calloc(1000, sizeof (char));

    if (self->disponibilites == NULL)
        return "";

    sprintf(tmp, "%p\n", (void*) (pthread_self()));
    strcat(str, tmp);

    e = self->disponibilites;

    while (e != NULL) {
        if (e->next != NULL)
            sprintf(tmp, "%p\t", e->key);
        else
            sprintf(tmp, "%p\n", e->key);

        strcat(str, tmp);

        e = e->next;
    }

    e = self->disponibilites;

    while (e != NULL) {
        if (e->next != NULL)
            sprintf(tmp, "%d\t\t", *(int*) (e->value));
        else
            sprintf(tmp, "%d\n", *(int*) (e->value));

        strcat(str, tmp);

        e = e->next;
    }

    return str;
}

void banquier_destroy(banquier* self) {
    pthread_mutex_destroy(&(self->mutex_modification));
    dictionary_destroy(self->disponibilites);
}
