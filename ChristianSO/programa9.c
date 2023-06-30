#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//cambiar la entrada estandar
int main(){

	int val;
	//fd <- descriptor de archivo
	int fd = open("entrada.dat", O_RDONLY);
	//PD. el archico debe estar creado y el primer caracter debe ser un digito

	dup2(fd, 0); //reedirecciona la salida de STDOUT al descriptor de archivo fd

	close(fd);	//liberar el descriptor de archivo
	
	scanf("%d", &val);

	printf("val = %d\n",val);

	return 0;
}