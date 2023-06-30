#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// n = numero de parametos
// argv = cadena que contiene los parametros
// shell se encarga de inicializar tanto n como argv
int main(int n, char *argv[]){
	for(int j=0; j<n; j++){
		fprintf(stdout,"%s ",argv[j]);
	}
	fprintf(stdout,"\n");
	return 0;
}