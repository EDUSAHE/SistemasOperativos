#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(){
	pid_t pid;
	char *argv[] = {"/bin/ls", "-l", NULL};
	pid=fork();

	if(pid == 0){
		execl("/bin/ls", "/bin/ls", "-l", NULL);
		//execv("/bin/ls", argv);
		//execv("/bin/ls", argv); 
		//execlp("/bin/ls", "/bin/ls", "-l", NULL);
		//execle("/bin/ls", argv, "ls");

	}else{
		//printf("Estamos en el proceso padre.\n");
		wait(NULL);
	}
	return 0;
}