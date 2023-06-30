#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	printf("Hola Mundo \n");
	fork(); //Crea una copia del codigo acual creando un nuevo proceso, devuelve un pid_t donde si es =0 estoy el el proceso hijo y si es !=0 estoy en el proceso padre.
	printf("Buenas Tardes \n");
	fork();
	printf("Buenas Noches \n");
	return 0;
}