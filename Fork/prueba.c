#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int i;
	printf("%d\n",argc);
    int pipefds[2 * (argc - 2)];
    pid_t pid;

    // Crear los pipes
    for (i = 0; i < argc - 2; i++) {
        if (pipe(pipefds + i*2) == -1) {
            perror("Error en la creación del pipe.");
            exit(EXIT_FAILURE);
        }
    }

    // Bifurcación de procesos
    for (i = 0; i < argc - 1; i++) {
        pid = fork();

        if (pid == 0) {
            if (i == 0) {
                // Primer comando
                dup2(pipefds[1], STDOUT_FILENO);
            } else if (i == argc - 2) {
                // Último comando
                dup2(pipefds[(i-1)*2], STDIN_FILENO);
            } else {
                // Comando intermedio
                dup2(pipefds[(i-1)*2], STDIN_FILENO);
                dup2(pipefds[i*2+1], STDOUT_FILENO);
            }

            // Cerrar todos los pipes
            int j;
            for (j = 0; j < 2*(argc-2); j++) {
                close(pipefds[j]);
            }

            // Ejecutar el comando correspondiente
            execlp(argv[i+1], argv[i+1], NULL);

            // Si llegamos aquí, es porque hubo un error al ejecutar el comando
            perror("Error al ejecutar el comando.");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Error al crear proceso hijo.");
            exit(EXIT_FAILURE);
        }
    }

    // Cerrar todos los pipes en el proceso padre
    for (i = 0; i < 2*(argc-2); i++) {
        close(pipefds[i]);
    }

    // Esperar a que terminen todos los procesos hijos
    for (i = 0; i < argc - 1; i++) {
        wait(NULL);
    }

    return 0;
}
