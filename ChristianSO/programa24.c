//https://man7.org/linux/man-pages/man7/signal.7.html

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//programa que le envie una señal a otro proceso

int main(){

   kill(2619,SIGKILL);
   
   return 0;
}

//Una señal es una interrupcion que el S0 envia a un proceso.