//https://man7.org/linux/man-pages/man7/signal.7.html

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//programa quu se pausa al captura la señal STOP cada vez que la reciba
void rutinaServicio(int signalNumber){
   printf("la notificacion recibida tiene el numero: %d\n", signalNumber);
}

int main(){
   signal(SIGSTOP, &rutinaServicio);
   
   while( 1 ){
      printf("durmiendo\n");
      sleep(2);   //lo duerme por 2 segundos y continua
   }   
   return 0;
}

//Una señal es una interrupcion que el S0 envia a un proceso.