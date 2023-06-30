/*
Integrantes del Equipo:
Sánchez Hernández José Eduardo
Santibáñez García Luis Diego
Hernández Rosario Christian de Jesús
*/
#include <stdio.h>

#define NUMERO_PROCESOS 4
#define TIPOS_RECURSOS 3

int todosCeros(int arreglo[], int longitud) {
    for (int i = 0; i < longitud; i++) {
        if (arreglo[i] != 0) {
            return 0;  // No todos los elementos son cero
        }
    }
    return 1;  // Todos los elementos son cero
}
int main(){
    // //Caso 1
    int RecursosDisponibles[3] = {3,1,4};
    int RecursosAsignados[4][3] = {{1,2,4},{0,2,5},{4,1,3},{6,1,0}};
    int RecursosTotalesNecesarios[4][3] = {{5,3,5},{2,3,6},{7,2,4},{7,3,4}};
    // //Caso 2
    // int RecursosDisponibles[3] = {0,1,1};
    // int RecursosAsignados[4][3] = {{1,0,0},{6,1,3},{2,1,1},{0,0,2}};
    // int RecursosTotalesNecesarios[4][3] = {{3,2,2},{6,1,3},{3,1,4},{4,2,2}};
    // //Caso 3
    // int RecursosDisponibles[3] = {8,8,7};
    // int RecursosAsignados[4][3] = {{7,7,10},{10,16,2},{8,8,12},{18,7,0}};
    // int RecursosTotalesNecesarios[4][3] = {{10,14,15},{11,20,4},{9,9,18},{22,13,1}};
    // //Caso 4
    // int RecursosDisponibles[3] = {0,2,2};
    // int RecursosAsignados[4][3] = {{4,0,2},{10,2,2},{4,2,2},{0,0,4}};
    // int RecursosTotalesNecesarios[4][3] = {{6,4,4},{12,2,6},{6,2,8},{8,4,4}};

    int SecuenciaSegura[NUMERO_PROCESOS];
    int StatusProcesos[NUMERO_PROCESOS] = {0,0,0,0};
    int Indice = 0,i,j,k,l;

    for(i=0;i<NUMERO_PROCESOS;i++){
        for (j=0;j<NUMERO_PROCESOS;j++){
            if(StatusProcesos[j]==0){
                int RecursosInsuficientes = 0;
                for(k=0;k<TIPOS_RECURSOS;k++){
                    if(RecursosTotalesNecesarios[j][k] - RecursosAsignados[j][k] > RecursosDisponibles[k]){
                        RecursosInsuficientes = 1;
                        break;
                    }
                }
                if(RecursosInsuficientes==0){
                    SecuenciaSegura[Indice++] = j;
                    for(l=0;l<TIPOS_RECURSOS;l++){
                        RecursosDisponibles[l]+=RecursosAsignados[j][k];
                    }
                    StatusProcesos[j]=1;
                }
            }
        }
    }

    if(todosCeros(SecuenciaSegura,NUMERO_PROCESOS)==1)
        printf("No hay suficientes recursos para realizar una secuencia segura\n");
    else{
        printf("La secuencia segura es: ");
        for (i = 0; i < NUMERO_PROCESOS - 1; i++) {
            printf("P%d -> ", SecuenciaSegura[i] + 1);
        }
        printf("P%d\n", SecuenciaSegura[NUMERO_PROCESOS - 1] + 1);
    }
    return 0;
}
