#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

int main(){

	int fd[2];
	int fd2[2];
	char *argv[]={"/usr/bin/ps","-fea",NULL};
	char *argv1[]={"/usr/bin/grep","eduardo",NULL};
	char *argv2[]={"/usr/bin/wc",NULL};
	//0 R
	//1 w
	pid_t pid;
	
	pipe(fd); //pipe recibe un apuntador a entero
	pipe(fd2);
	//se construye la tuberia :)
	pid = fork(); //genero hijo 1
	if (pid==0){
		close(fd[0]); //Cierra Entrada(READ) PIPE1
		close(fd2[0]);	//Cierra Entrada(READ) PIPE2
		close(fd2[1]); //Cierra Salida(WRITE) PIPE1	
		dup2(fd[1],1); //Cambia salida(WRITE)
		execvp("ps",argv); //cuando tiene exito, NO REGRESA
		//printf("Hola mundo\n"); //no se ejecuta por que execl nunca regresa si tubo exito
		//se ejecuta el printf si la funcion execl fallo :(
	}//al finalizar, el proceso muere
	pid = fork();
	if (pid==0){
		close(fd[1]);
		close(fd2[0]);	//cerrar entrada estandar
		dup2(fd[0],0);
        dup2(fd2[1],1); //redirecciona salida
		execvp("grep",argv1);
	}
	pid = fork();
	if (pid==0){
		close(fd[0]);
		close(fd[1]);
		close(fd2[1]);
		dup2(fd2[0],0);
		execvp("wc",argv2);
	}
	close(fd[0]);
	close(fd[1]);
	close(fd2[0]);
	close(fd2[1]);
	wait(NULL);
	wait(NULL);
	wait(NULL);
	return 0;
}