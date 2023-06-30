#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	char *argv[] = {"/bin/ls","-l",NULL};
	pid = fork(); 
	/*
	Crea una copia del codigo acual creando un nuevo proceso, devuelve un pid_t donde 
	si es =0 estoy el el proceso hijo y si es !=0 estoy en el proceso padre.
	*/
	if(pid==0){
		// execl("/bin/ls","/bin/ls","-l",NULL);
		// execv("/bin/ls",argv);
		execvp("ls",argv);
		// execlp("ls","ls","-l",NULL); 
		// execvpe("ls",argv); ERROR
	}
	else
		wait(NULL);
	return 0;
}