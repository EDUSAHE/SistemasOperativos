#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	printf("Hola Mundo\n");
	pid = fork();
	
	if(pid == 0){
		printf("Estamos en el proceso HIJO\n");
	}else{
		printf("Estamos en el proceso PADRE\n");
	}
	
	return 0;
}
