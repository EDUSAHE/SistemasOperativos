#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid == 0){
		execl("/bin/ls", "/bin/ls", "-l", NULL);
		//execl toma el primer parametro como el nombre del comando, es decir, va a esa ruta y busca el comando ls
		//el contenido de esa carptera lo carga a memoria.
		//es importante que el 1er parametro sea escrito correctamente
		
		//el segundo parametro es el nombre del mismo archivo, por eso se pone 2 veces /bin/ls
		//se toma como cadena, asi que no es muy importante que sean iguales
	}else{
		//printf("Estamos en el proceso padre.\n");
		wait(NULL);
	}
	return 0;
}

