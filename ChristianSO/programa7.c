#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//REEDIRECCIONAMIENTO SALIDA ESTANDAR

int main(){
	//fd <- descriptor de archivo
	int fd = open("archivo.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600);

	dup2(fd, 1); //reedirecciona la salida de STDOUT al descriptor de 				archivo fd
	//duplicar la salida estandar en el descriptor de archivo fd

	close(fd);	//liberar el descriptor de archivo

	//todo lo que va debajo, va al archivo
	printf("Hola Mundo\n");
	return 0;
}

// PROCESO:
// STDOUT  1  salida
// STDIN   0  entrada
// STDERR  2

