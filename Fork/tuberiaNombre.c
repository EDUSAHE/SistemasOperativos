#include <stdio.h>
#include <sys/types.h>

int main(){
    FILE *mipipe;
    char buffer[128];
    int i=0;

    if(mkfifo("pipetest",
            S_IWUSR |
            S_IRUSR |
            S_IRGRP |
            S_IROTH 
    )!=0)
        printf("Hubo un problema al crear la pipe\n");
    
    mipipe = fopen("pipetest","w");

    while(i<10){
        
    }
}