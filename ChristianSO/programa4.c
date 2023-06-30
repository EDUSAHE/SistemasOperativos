#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int n, char *argv[]){
	//n representa la cantidad de parametros que recibe el programa, su valor minimo es 1 (nombre del ejecutable)
	//argv contiene los parametros en tipo str
	for (int j=0; j<n ; j++){
		fprintf(stdout, "%s ", argv[j]);
		//la posicion 0 contiene el nombre del ejecutable
		//los demas son los otros parametros
	}
	fprintf(stdout, "\n");
	return 0;
}
