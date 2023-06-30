/*
Integrantes del Equipo:
Sánchez Hernández José Eduardo
Santibáñez García Luis Diego
Hernández Rosario Christian de Jesús
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_COLA 4 // tamaño máximo de la cola

// definición de la estructura cola
struct Cola {
    char *elementos[MAX_COLA]; // arreglo para almacenar los elementos de la cola
    int frente, final; // índices del elemento al frente y al final de la cola
};

// función para inicializar la cola
void inicializarCola(struct Cola* cola) {
    cola->frente = 0;
    cola->final = 0;
}

// función para insertar un elemento en la cola
void insertar(struct Cola* cola, char *elemento) {
    if (cola->final < MAX_COLA) { // si la cola no está llena
        cola->elementos[cola->final++] = elemento; // insertar el elemento y actualizar el índice final
    }
}

// función para eliminar un elemento de la cola y recorrer los elementos
int eliminar(struct Cola* cola) {
    if (cola->frente < cola->final) {
        char *elemento = cola->elementos[cola->frente]; 
        for(int i=0;i<MAX_COLA;i++){
          cola->elementos[i]=cola->elementos[i+1];
        }
        cola->final--;
    }
    return -1;
}

#define DORMIDO 0
#define DESOCUPADO 0
#define HAY_SILLAS 1
#define CLIENTES_ESPERANDO 0

#define TOTAL_CLIENTES 10

void *barbero( void *s); 
void *cliente( void *s);
void cortarPelo();


sem_t barberoListo; //Semáforo barberoListo para indicar cuando el barbero esta preparado para cortar el pelo
sem_t barberoDesocupado; //Semáforo baerberoDesocupado para indicar cuando se encuentra cortando el pelo
sem_t haySillas; // Semáforo haySillas. Cuando sea 1, el número de sillas libres puede aumentar o disminuir
sem_t clientes_esperando; // Número de clientes esperando en la sala de espera
sem_t clientes_recibidos;
struct Cola cola;
int num_clientes_recibidos = 0;

int main(){  
  inicializarCola(&cola);
  char *nombres[] = {"Brandon", "Ulises", "Hazel","Cristoff", "Heriberto", "Jonathan", "Ismael", "Leonel", "Andres", "Messi"};
  pthread_t peluquero;
  pthread_t melenudo[ TOTAL_CLIENTES ];
  
  //Barbero inicia dormido
  sem_init( &barberoListo, 0, DORMIDO );
  //Iniciamos semaforo en 0
  sem_init( &barberoDesocupado, 0, DESOCUPADO );  
  //Inicia con sillas de espera disponibles
  sem_init( &haySillas, 0, HAY_SILLAS ); 
  // de inicio, no hay clientes esperando
  sem_init( &clientes_esperando,  0, CLIENTES_ESPERANDO ); 
  // semaforo clinetes recibidos en el local
  sem_init( &clientes_recibidos,  0, 1);  

  pthread_create( &peluquero, NULL, barbero, NULL );
  for( int k = 0; k < TOTAL_CLIENTES; k++){
    pthread_create( &melenudo[ k ], NULL, cliente, (void *)nombres[ k ]);
  }


  pthread_join( peluquero, NULL );
  for( int k = 0; k < TOTAL_CLIENTES; k++)
    pthread_join( melenudo[ k ], NULL );
}

void *barbero(void *b){
  int f = 1;
  while(f){
    sem_wait(&clientes_recibidos);
    if(num_clientes_recibidos==9)
      f = 0;
    sem_post(&clientes_recibidos);
    sem_wait( &clientes_esperando );  // espera que un cliente lo despierte
    sem_wait( &haySillas ); // ya esta despierto. debe aumentar
    eliminar( &cola );
    sem_post( &haySillas ); // deja que otros modifique sillas libres.
    sem_post( &barberoListo ); // esta listo para cortar. le avisa al cliente.
    sem_wait( &barberoDesocupado ); // esta listo para cortar. le avisa al cliente.
  }
  printf("El barbero terminó su dia de trabajo\n");
  pthread_exit( NULL );
}

void *cliente( void *name ){
  sem_wait( &haySillas ); // candado de sillasLibres
  if( cola.final < 4){
    insertar(&cola,(char *)name);
    sem_post( &clientes_esperando ); // le avisa al barbero que hay un cliente disponible.
    sem_post( &haySillas ); // libera la variable sillasLibres
    sem_wait( &barberoListo ); // espera a que el barbero esté listo.
    cortarPelo( (char *)name);
    sem_post(&barberoDesocupado);
  }
  else{
    printf("%s no encontro sillas libres\n", (char *)name);
    sem_post( &haySillas ); //libera sillasLibres
  }
  sem_wait(&clientes_recibidos);
  num_clientes_recibidos++;
  sem_post(&clientes_recibidos);
  pthread_exit( NULL );
}

void cortarPelo(char *s){
  printf("\tSoy %s y me estan cortando el pelo\n", s);
  sleep(1);
  printf("\tSoy %s y me terminaron de cortar el pelo\n", s);
}



