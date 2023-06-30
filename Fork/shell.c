/*
Integrantes del Equipo:
Sánchez Hernández José Eduardo
Santibáñez García Luis Diego
Hernández Rosario Christian de Jesús
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <stdlib.h>


typedef struct {
    char parametro[30];
}Comand;

void cambiarSalida(char archivo[100]){
    int fd = open(archivo, O_WRONLY|O_CREAT|O_TRUNC, 0600);
    dup2(fd, 1);
    close(fd);
    return;
}
void cambiarEntrada(char archivo[100]){
    int fd = open(archivo, O_RDONLY);
    dup2(fd, 0);
    close(fd);
    return;
}

void resetDescriptores(){
    // Cerrar los descriptores de archivo existentes
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Duplicar los descriptores de archivo correspondientes a los descriptores de archivo estándar
    int new_stdin_fd = open("/dev/tty", O_RDONLY); // abrir un archivo de lectura
    int new_stdout_fd = open("/dev/tty", O_WRONLY); // abrir un archivo de escritura
    int new_stderr_fd = open("/dev/tty", O_WRONLY); // abrir un archivo de escritura

    dup2(new_stdin_fd, STDIN_FILENO);
    dup2(new_stdout_fd, STDOUT_FILENO);
    dup2(new_stderr_fd, STDERR_FILENO);
}

int ObtenerNombre(char nombre[100],int index,char comando[100]){
    if(comando[index]==' ')
        index++;
    for(int i=0;index<=strlen(comando);index++,i++){
        if(comando[index]==' ' || comando[index]=='\n' || comando[index]=='<' || comando[index]=='>'){
            if(comando[index]==' ')
                return index;
            else
                return --index;
        }
        else
            nombre[i]=comando[index];
    }
}

int main(){
    pid_t pid;
    Comand params[20]={};
    char comando[100];
    char ArchivoEntrada[100]="";
    char ArchivoSalida[100]="";
    int pipeta=0;
	char *argv[50];
    int fds[20];
    char *username = getlogin();
    char hostname[256];
    char path[1024];
    gethostname(hostname, sizeof(hostname));
    getcwd(path, sizeof(path));
    system("clear");
    while (1){
        printf("\033[1;31m%s$%s\033[0m:\033[1;36m%s\033[0m❥❥❥ ",username,hostname,path);
        for (int f = 0; f < 10; f++)
            pipe(fds + f*2);

        fgets( comando, 100, stdin );

        for(int i=0,j=0,k=0; i<=strlen(comando); i++){
            if(comando[i]=='<' || comando[i]=='>'){
                argv[j]=NULL;
                if(comando[i]=='>'){
                    i = ObtenerNombre(ArchivoSalida,i+1,comando);
                    cambiarSalida(ArchivoSalida);
                }else{
                    i = ObtenerNombre(ArchivoEntrada,i+1,comando);
                    cambiarEntrada(ArchivoEntrada);
                }
            }
            else if (comando[i]=='|'){
                argv[j]=NULL;
                pid = fork();
                if (pid==0){
                    if(pipeta>0){
                        dup2(fds[(pipeta-1)*2],0);
                        dup2(fds[pipeta*2+1],1);
                    }else
                        dup2(fds[1],1);
                    for (int f=0;f<10;f++)
                        close(fds[f]);
                    execvp(argv[0],argv); //cuando tiene exito, NO REGRESA
                    perror("Error al ejecutar comando");
                }
                pipeta++;
                if(comando[i+1]==' ')
                    i++;
                for(int z=0;z<20;z++)
                    memset(params[z].parametro,0,20);
                j=0;        
            }
            else if(comando[i]==' ' || comando[i]=='\n'){
                if(strlen(params[j].parametro)>0){
                    argv[j]=params[j].parametro;
                    j++;
                    k=0;
                }
                if(comando[i]=='\n' && pipeta==0){
                    argv[j]=NULL;
                    pid = fork();
                    if (pid==0){
                        execvp(argv[0],argv);
                        perror("Error al ejecutar comando");
                    }
                    wait(NULL); 
                }
                if(pipeta>0 && comando[i]=='\n'){
                    argv[j]=NULL;
                    pid = fork();
                    if (pid==0){
                        dup2(fds[(pipeta-1)*2],0);
                        for (int f=0;f<10;f++)
                            close(fds[f]);
                        execvp(argv[0],argv);
                        perror("Error al ejecutar comando");
                    }
                    for (int f=0;f<10;f++)
                        close(fds[f]);
                    for (int f=0;f<=pipeta;f++)
                        wait(NULL);
                    pipeta=0;
                }
            }else{
                params[j].parametro[k]=comando[i];
                k++;
            }
        }
        for(int z=0;z<20;z++)
            memset(params[z].parametro,0,20);
        memset(ArchivoEntrada,0,100);
        memset(ArchivoSalida,0,100);
        memset(comando,0,100);
        resetDescriptores();
    } 
    return 0;
}