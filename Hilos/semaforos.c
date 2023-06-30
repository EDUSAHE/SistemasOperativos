#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

sem_t semaforo,semaforo2;
int hilo = 0;


void *mesa(void *p){
    sem_wait(&semaforo);
    sem_wait(&semaforo2);
    printf("Hay %d hilos en la mesa\n",++hilo);
    sem_post(&semaforo2);
    sleep(5);
    sem_wait(&semaforo2);
    printf("Hay %d hilos en la mesa\n",--hilo);
    sem_post(&semaforo2);
    sem_post(&semaforo);
    pthread_exit(NULL);
}

int main(){
    sem_init(&semaforo,0,3);
    sem_init(&semaforo2,0,1);
    int k=25;
    pthread_t hilos[5];
    for(int i=0;i<5;i++)
        pthread_create(&hilos[i],NULL,mesa,NULL);
    for(int i=0;i<5;i++)
        pthread_join(hilos[i],NULL);
    return 0;
}