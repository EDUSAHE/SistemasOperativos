#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h> 
#include <semaphore.h>
#include <unistd.h>

#define FILOSOFOS 5

sem_t tenedor[ FILOSOFOS ];

char *filosofos[ ] = {"platon", "descartes", "pitagoras", "kepler", "newton" };

void comer( int i){
   printf("%s esta comiendo\n", filosofos[ i ] );
   fflush( stdout );
   sleep( 1 );
}

void pensar( int i){
   printf("\t%s esta pensando\n", filosofos[ i ] );
   fflush( stdout );
   // sleep(1);
}


void *filosofo( void *pos ){ 
   int *ptr = (int *)pos;
   int i = *ptr;
   while( 1 ){
      pensar( i );      
   
      sem_wait( &tenedor[ i ]); // espera tenedor de la izquierda
      if(sem_getvalue(&tenedor[ ( i + 1 ) % FILOSOFOS]),)
      sem_wait( &tenedor[ ( i + 1 ) % FILOSOFOS] ); // espera tenedor de la derecha
      
      comer( i );// come cuando se apodera de ambos tenedores      
      
      sem_post( &tenedor[ ( i + 1 ) % FILOSOFOS ]); // libera tenedor de la derecha
      sem_post( &tenedor[ i ] ); // libera tenedor de la izquierda
    
   }
   pthread_exit( NULL );
}

int main(){
   int k;
   int pos[]= {0, 1, 2, 3, 4};
   pthread_t hilo[ FILOSOFOS ];
  
   for(k = 0; k < FILOSOFOS; k++ )
      sem_init( &tenedor[ k ], 0, 1); // de inicio, los tenedores 
                                      //estan disponibles                   
   for( k = 0; k < FILOSOFOS; k++ )
      pthread_create( &hilo[ k ], NULL, filosofo,  (void *)&pos[k]);

   for( k = 0; k < FILOSOFOS; k++ )
      pthread_join(hilo[ k ], NULL );
  
   for( k = 0; k < FILOSOFOS; k++)
      sem_destroy( &tenedor[ k ] );
   
   printf("fin hilo principal\n");
   return 0;
}

