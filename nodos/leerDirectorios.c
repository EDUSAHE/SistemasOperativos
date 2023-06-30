#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    DIR *directorio;
    struct dirent *direntp;

    directorio = opendir("."); //Abre el directorio o carpeta

    if(directorio==NULL){
        printf("Error: No se puede abrir el directorio\n");
        exit(2);
    }
    while((direntp = readdir(directorio))!= NULL){ 
        printf("%ld\t%-20s",direntp->d_ino, direntp->d_name);
        switch (direntp->d_type){
            case DT_DIR:
                printf("Directorio\n");
                break;
            case DT_REG:
                printf("Archivo regular\n");
                break;
            case DT_BLK:
                printf("Dispositivo de bloque\n");
                break;
            case DT_CHR:
                printf("Dispositivo de caracteres\n");
                break;
            case DT_FIFO:
                printf("Tuberia con nombre\n");
                break;
            case DT_SOCK:
                printf("Socket\n");
                break;
            case DT_LNK:
                printf("Liga");
            default:
                printf("\n");
        }
    }
    closedir(directorio);
}