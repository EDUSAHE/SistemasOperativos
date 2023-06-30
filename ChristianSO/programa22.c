#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
//programa que ejecute todos los comandos en la carpeta /bin
int main(){
	char path[1024]; //cualquier tamaño grande, puede ser por que es potencia de 2
	char cmd[1024]; 
	pid_t pid;

	while(1){	//ciclo infinito
		strcpy(path, "/bin/"); //copiar el 2do argumento a la primer cadena
		printf("C:> ");
		scanf("%s", cmd);
		
		strcat(path, cmd); //concatenar cadenas y se queda en el 1er argumento
		printf("%s\n", path);	//obtener el path del comando
		
		pid = fork();
		if (pid==0){
			execl(path, cmd, NULL);
			printf("Comando no encontrado\n");
			exit(-1); //abortamos programa
		}
		wait(NULL); //para esperar el hijo
	}	
	return 0;
}