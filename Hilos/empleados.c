#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int jefePresente = 0;
pthread_mutex_t candado = PTHREAD_MUTEX_INITIALIZER;
char *nombres = {"Luis","Paola","Paco","Emma","Diego"};
llegada = -1;
void *saludo(void *s){
    pthread_mutex_lock(&candado);
    ++llegada;
    if(jefePresente==1){
        printf("Soy %s disculpe por el retardo Jefe \n",nombres[llegada]);
    }
    else {
        printf("Buenos dias \n");
    }
    pthread_mutex_unlock(&candado);
    pthread_exit(NULL);
}
void *saludoJefe(void *s){ 
    pthread_mutex_lock(&candado);
    jefePresente = 1;
    pthread_mutex_unlock(&candado);
    printf("Buenos dias soy el Jefe \n");
    pthread_exit(NULL);
}

int main(){
    pthread_t trabajadores[6];
    for(int i=0;i<6;i++){
        if(i==3)
            pthread_create(&trabajadores[i],NULL,saludoJefe,NULL);
        else
            pthread_create(&trabajadores[i],NULL,saludo,NULL);
    }
    for(int i=0;i<6;i++)
        pthread_join(trabajadores[i],NULL);
    return 0;
}
