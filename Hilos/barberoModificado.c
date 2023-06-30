#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define DORMIDO 1
#define HAY_SILLAS 1
#define CLIENTES_ESPERANDO 0

#define TOTAL_CLIENTES 10

void *barbero( void *s); 
void *cliente( void *s);
void cortarPelo();


sem_t barberoDormido; //Semáforo barberoDormido, 1 el barbero está dormido y 0 el barbero está despierto
sem_t haySillas; // Semáforo haySillas = 1. Cuando sea 1, el número de sillas libres puede 
                 // aumentar o disminuir
sem_t clientes_esperando; // Número de clientes esperando en la sala de espera
int sillasLibres = 4;  // N es el número total de sillas
int value;

int main(){  
  char *nombres[] = {"1", "2", "3","4", "5", "6", "7", "8", "9", "10"};
  pthread_t peluquero;
  pthread_t melenudo[ TOTAL_CLIENTES ];
  
      // barbero inicia dormido
  sem_init( &barberoDormido, 0, DORMIDO );  
      // inicia con sillas de espera disponibles
  sem_init( &haySillas, 0, HAY_SILLAS ); 
      // de inicio, no hay clientes esperando
  sem_init( &clientes_esperando,  0, CLIENTES_ESPERANDO );  

  pthread_create( &peluquero, NULL, barbero, NULL );
  for( int k = 0; k < TOTAL_CLIENTES; k++)
    pthread_create( &melenudo[ k ], NULL, cliente, (void *)nombres[ k ]);

  pthread_join( peluquero, NULL );
  for( int k = 0; k < TOTAL_CLIENTES; k++)
    pthread_join( melenudo[ k ], NULL );
}

void *barbero(void *b){
  while(1){
    sem_wait( &clientes_esperando );  // espera que un cliente lo despierte
    sem_wait( &haySillas ); // ya esta despierto. debe aumentar
    sillasLibres++; // el numero de silla libres.
    // sem_getvalue(&barberoDormido,&value);
    // printf("El valor del semáforo es: %d\n", value);
    sem_post( &haySillas ); // deja que otros modifique sillas libres.
    sem_wait( &barberoDormido ); // está despierto y listo para cortar. le avisa al cliente.
    //cortarPelo();
  }
  pthread_exit( NULL );
}

void *cliente( void *name ){
  sem_wait( &haySillas ); // candado de sillasLibres
  if( sillasLibres > 0){
    sillasLibres--; // disminuye la cantidad de sillas libres.
    sem_post( &clientes_esperando ); // le avisa al barbero que hay un cliente disponible.
    sem_post( &haySillas ); // libera la variable sillasLibres
    // cortarPelo( (char *)name);
    printf("Soy %s y me estan cortando el pelo\n",(char *)name);
    sleep(1);
    printf("\tSoy %s y me termiaron de cortar el pelo\n",(char *)name);
    sem_post( &barberoDormido ); // espera a que el barbero esté listo.
  }
  else{
    printf("%s no encontro sillas libres\n", (char *)name);
    sem_post( &haySillas ); //libera sillasLibres
  }
  pthread_exit( NULL );
}

void cortarPelo(char *s){
  printf("\tcortando el pelo a %s\n", s);
  sleep(1);
  printf("Termino de cortar a %s\n",s);
}