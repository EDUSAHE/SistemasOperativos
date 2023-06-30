#include <stdio.h>
#define MAX_COLA 4 // tamaño máximo de la cola

// definición de la estructura cola
struct Cola {
    int elementos[MAX_COLA]; // arreglo para almacenar los elementos de la cola
    int frente, final; // índices del elemento al frente y al final de la cola
};

// función para inicializar la cola
void inicializarCola(struct Cola* cola) {
    cola->frente = 0;
    cola->final = 0;
}

// función para insertar un elemento en la cola
void insertar(struct Cola* cola, int elemento) {
    if (cola->final < MAX_COLA) { // si la cola no está llena
        cola->elementos[cola->final++] = elemento; // insertar el elemento y actualizar el índice final
    }
}

// función para eliminar un elemento de la cola
int eliminar(struct Cola* cola) {
    if (cola->frente < cola->final) { // si la cola no está vacía
        int elemento = cola->elementos[cola->frente++]; // obtener el elemento al frente y actualizar el índice frente
        return elemento;
    }
    return -1; // en caso contrario, retornar un valor especial para indicar que la cola está vacía
}

// función para verificar si la cola está vacía
int estaVacia(struct Cola* cola) {
    return cola->frente == cola->final;
}

// función para imprimir los elementos de la cola
void imprimirCola(struct Cola* cola) {
    printf("Elementos de la cola:\n");
    for (int i = cola->frente; i < cola->final; i++) {
        printf("%d ", cola->elementos[i]);
    }
    printf("\n");
}

// ejemplo de uso de la cola
int main() {
    struct Cola cola;
    inicializarCola(&cola);
    insertar(&cola, 1);
    insertar(&cola, 2);
    insertar(&cola, 3);
    insertar(&cola, 4);
    imprimirCola(&cola);
    eliminar(&cola);
    eliminar(&cola);
    imprimirCola(&cola);
    insertar(&cola, 5);
    insertar(&cola, 6);
    imprimirCola(&cola);
    return 0;
}
