#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
//Programa que emula el comando: ls -l | wc
int main(){

	int fd[2];
	pid_t pid;

	pipe(fd); //pipe recibe un apuntador a entero
	//se construye la tuberia :)

	pid = fork(); //genero hijo 1
	if (pid==0){
		close(fd[0]);	//cerrar entrada estandar
						//cerrar parte baja de la tuberia
		dup2(fd[1],1); //duplicar salida estandar
		close(fd[1]);
		execl("/bin/ls","/bin/ls","-l",NULL); //cuando tiene exito, NO REGRESA
		//printf("Hola mundo\n"); //no se ejecuta por que execl nunca regresa si tubo exito
		//se ejecuta el printf si la funcion execl fallo :(
	}//al finalizar, el proceso muere

	pid = fork();
	if (pid==0){
		close(fd[1]);
		dup2(fd[0],0);
		close(fd[0]);
		execl("/usr/bin/wc","/usr/bin/wc",NULL);
	}
	wait(NULL);
	return 0;
}