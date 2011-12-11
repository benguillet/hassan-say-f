#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include "train.h"
#include "structures.h"

void* TGV_thread_fn(void* arg) {
    train *TGV = (train*)arg;
    
    switch (TGV->direction) {
        case OE:
            printf("%s - OE - P(Voie C)\n", TGV->nom);
            sem_wait(table_get(table_get(TGV->postes, "Gare"), "Voie C"));
            
            printf("%s - OE - P(Aiguillage 2)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P0"), "Aiguillage 2"));
            
            printf("%s - OE - P(Ligne TGV)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P1"), "Ligne TGV"));
            
            printf("%s - OE - V(Voie C)\n", TGV->nom);
            sem_post(table_get(table_get(TGV->postes, "Gare"), "Voie C"));
            
            printf("%s - OE - V(Aiguillage 2)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P0"), "Aiguillage 2"));
            
            printf("%s - OE - P(Tunnel)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P2"), "Tunnel"));
            
            printf("%s - OE - P(Ligne)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P3"), "Ligne"));
            
            printf("%s - OE - V(Ligne TGV)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P1"), "Ligne TGV"));   
            
            printf("%s - OE - V(Tunnel)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P2"), "Tunnel")); 
            
            printf("%s - OE - V(Ligne)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P3"), "Ligne"));
                        
            break;
        case EO:
            printf("%s - EO - P(Ligne)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P3"), "Ligne"));
            
            printf("%s - EO - P(Tunnel)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P3"), "Tunnel"));
            
            printf("%s - EO - P(Ligne TGV)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P2"), "Ligne TGV"));
            
            printf("%s - EO - V(Ligne)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P3"), "Ligne"));
            
            printf("%s - EO - V(Tunnel)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P3"), "Tunnel"));
            
            printf("%s - EO - P(Aiguillage 2)\n", TGV->nom);
            pthread_mutex_lock(table_get(table_get(TGV->postes, "P1"), "Aiguillage 2"));
                        
            printf("%s - EO - P(Voie D)\n", TGV->nom);
            sem_wait(table_get(table_get(TGV->postes, "P0"), "Voie D"));
            
            printf("%s - EO - V(Ligne TGV)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P1"), "Ligne TGV"));
                                    
            printf("%s - EO - V(Aiguillage 2)\n", TGV->nom);
            pthread_mutex_unlock(table_get(table_get(TGV->postes, "P1"), "Aiguillage 2"));
                                    
            printf("%s - EO - V(Voie D)\n", TGV->nom);
            sem_post(table_get(table_get(TGV->postes, "P0"), "Voie D"));
                        
            break;
        default:
            perror("Erreur : TGV - direction inconnu");
            pthread_exit(NULL);
    }
    
    return NULL;
}

void* GL_thread_fn(void* arg) {
    train *GL = (train*)arg;
    
    switch (GL->direction) {
        case OE:
            printf("%s - OE - P(Voie C)\n", GL->nom);
            sem_wait(table_get(table_get(GL->postes, "Gare"), "Voie C"));
            
            printf("%s - OE - P(Aiguillage 2)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P0"), "Aiguillage 2"));
            
            printf("%s - OE - P(Ligne GL)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P1"), "Ligne GL"));
            
            printf("%s - OE - V(Voie C)\n", GL->nom);
            sem_post(table_get(table_get(GL->postes, "Gare"), "Voie C"));
            
            printf("%s - OE - V(Aiguillage 2)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P0"), "Aiguillage 2"));
            
            printf("%s - OE - P(Tunnel)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P2"), "Tunnel"));
            
            printf("%s - OE - P(Ligne)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P3"), "Ligne"));
            
            printf("%s - OE - V(Ligne GL)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P1"), "Ligne GL"));   
            
            printf("%s - OE - V(Tunnel)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P2"), "Tunnel")); 
            
            printf("%s - OE - V(Ligne)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P3"), "Ligne"));
            
            break;
        case EO:
            printf("%s - EO - P(Ligne)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P3"), "Ligne"));
            
            printf("%s - EO - P(Tunnel)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P3"), "Tunnel"));
            
            printf("%s - EO - P(Ligne GL)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P2"), "Ligne GL"));
            
            printf("%s - EO - V(Ligne)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P3"), "Ligne"));
            
            printf("%s - EO - V(Tunnel)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P3"), "Tunnel"));
            
            printf("%s - EO - P(Aiguillage 2)\n", GL->nom);
            pthread_mutex_lock(table_get(table_get(GL->postes, "P1"), "Aiguillage 2"));
                        
            printf("%s - EO - P(Voie D)\n", GL->nom);
            sem_wait(table_get(table_get(GL->postes, "P0"), "Voie D"));
            
            printf("%s - EO - V(Ligne GL)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P1"), "Ligne GL"));
                                    
            printf("%s - EO - V(Aiguillage 2)\n", GL->nom);
            pthread_mutex_unlock(table_get(table_get(GL->postes, "P1"), "Aiguillage 2"));
                                    
            printf("%s - EO - V(Voie D)\n", GL->nom);
            sem_post(table_get(table_get(GL->postes, "P0"), "Voie D"));
            
            break;
        default:
            perror("Erreur : GL - direction inconnu");
            pthread_exit(NULL);
    }
    
    return NULL;
}

void* M_thread_fn(void* arg) {
    train *M = (train*)arg;
    
    switch (M->direction) {
        case EO:
            break;
        case OE:
            break;
        default:
            perror("Erreur : M - direction inconnu");
            pthread_exit(NULL);
    }
    
    return NULL;
}