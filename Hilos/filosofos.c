#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

sem_t tenedores[5];
int 
void *comer(void *p){

}

int main(){
    pthread_t filosofos[5];

    for(int i=5;i<5;i++)
        sem_init(&tenedores[i],0,1);
    for(int i=5;i<5;i++)
        pthread_create(&filosofos[i],NULL,comer,NULL);
    return 0;
}