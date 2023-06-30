#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid;
	printf("Hola Mundo \n");
	pid = fork(); //Crea una copia del codigo acual creando un nuevo proceso, devuelve un pid_t donde si es =0 estoy el el proceso hijo y si es !=0 estoy en el proceso padre.
	if(pid==0)
		printf("Estamos en el proceso hijo \n");	
	else
		printf("Estamos en el proceso padre \n");
	return 0;
}