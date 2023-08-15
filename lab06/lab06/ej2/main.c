#include "string.h"
#include <stdio.h>

int main(void){
    string palabra1 = string_create("palabra_lar"); //palabra mas larga
    string palabra2 = string_create("palabra_c"); //palabra mas corta
    string copia = string_clone(palabra1);
    if (string_less(palabra2,palabra1)){
        printf("La funcion less cumple su tarea correctamente\n");
        printf("arreglo mas pequeño es:\n");
        string_dump(palabra2,stdout);
        printf("\n");
    }
    if (string_eq(palabra1,copia)){
        printf("La funcion eq cumple su tarea correctamente\n");
    }
    return 0;
}