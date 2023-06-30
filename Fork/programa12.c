#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
	pid_t pid;
	pid = fork();

	if (pid==0){
		//fd <- descriptor de archivo
		int fd = open("archivo2.txt", O_WRONLY|O_CREAT|O_TRUNC,0600);

		dup2(fd, 1); //reedirecciona la salida de STDOUT al descriptor de archivo fd
		//duplicar: 

		close(fd);	//liberar el descriptor de archivo

		execl("/bin/ls", "/bin/ls", "-l", NULL);

	}else{
		//quitar else 
	}

	return 0;
}