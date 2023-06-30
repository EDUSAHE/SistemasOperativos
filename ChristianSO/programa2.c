#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Mensaje 1\n");
	fork();
	printf("Mensaje 2\n");
	fork();
	printf("Mensaje 3\n");
	
	return 0;
}


