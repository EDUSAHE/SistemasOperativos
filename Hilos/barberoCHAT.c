#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_SILLAS 5  // Número de sillas en la sala de espera
#define NUM_CLIENTES 10  // Número total de clientes a atender

sem_t sem_barbero;  // Semáforo para indicar si el barbero está dormido o no
sem_t sem_sillas;  // Semáforo para controlar el acceso a las sillas en la sala de espera
sem_t sem_cliente;  // Semáforo para indicar que un cliente ha llegado y está esperando

int num_sillas_ocupadas = 0;  // Número actual de sillas ocupadas en la sala de espera

void *barbero(void *arg) {
    while (1) {
        printf("El barbero está dormido...\n");
        sem_wait(&sem_barbero);  // Esperar a que un cliente despierte al barbero
        printf("El barbero ha sido despertado y está cortando el cabello de un cliente...\n");
        sleep(3);  // Simular el corte del cabello
        sem_post(&sem_cliente);  // Indicar al cliente que ha terminado su corte
    }
}

void *cliente(void *arg) {
    int id = *(int *) arg;
    printf("El cliente %d ha llegado a la peluquería...\n", id);
    sem_wait(&sem_sillas);  // Intentar sentarse en una silla en la sala de espera
    if (num_sillas_ocupadas < NUM_SILLAS) {
        num_sillas_ocupadas++;
        printf("El cliente %d se ha sentado en una silla en la sala de espera...\n", id);
        sem_post(&sem_barbero);  // Despertar al barbero si está dormido
        sem_post(&sem_sillas);  // Liberar la silla ocupada en la sala de espera
        sem_wait(&sem_cliente);  // Esperar a que el barbero termine el corte de cabello
        printf("El cliente %d ha terminado de cortarse el cabello y se va de la peluquería...\n", id);
    } else {
        printf("No hay sillas disponibles en la sala de espera, el cliente %d se va de la peluquería...\n", id);
        sem_post(&sem_sillas);  // Liberar la silla ocupada en la sala de espera
    }
}

int main() {
    pthread_t barbero_thread;
    pthread_t clientes_threads[NUM_CLIENTES];
    int ids_clientes[NUM_CLIENTES];

    sem_init(&sem_barbero, 0, 0);
    sem_init(&sem_sillas, 0, 1);
    sem_init(&sem_cliente, 0, 0);

    pthread_create(&barbero_thread, NULL, barbero, NULL);

    for (int i = 0; i < NUM_CLIENTES; i++) {
        ids_clientes[i] = i + 1;
        pthread_create(&clientes_threads[i], NULL, cliente, &ids_clientes[i]);
        usleep(500);  // Espaciar la llegada de los clientes
    }

    pthread_join(barbero_thread, NULL);

    for (int i = 0; i < NUM_CLIENTES; i++) {
        pthread_join(clientes_threads[i], NULL);
    }

    sem_destroy(&sem_barbero);
    sem_destroy(&sem_sillas);
    sem_destroy(&sem_cliente);

    return 0;
}

