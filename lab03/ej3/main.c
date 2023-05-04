#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "helper.h"
#define MAX_SIZE 1000

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    
    FILE *file = fopen(path, "r");

    unsigned int length = 0;
    int aux;
    for(unsigned int i = 0;feof(file)==0;i++){
        if (i >= max_size){
            printf("La cantidad de lineas del archivo supera el maximo\n");
            EXIT_FAILURE;
        }
        aux = fscanf(file, "%u -> *%c*\n", &indexes[i], &letters[i]);
        if(aux != 2){
            printf("Error leyendo el archivo\n");
            EXIT_FAILURE;
        }
 
        length++;
    }


    fclose(file);

    return length;
}

int main(int argc, char *argv[]) {
    //FILE *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 

    char *filepath = NULL;
    filepath = parse_filepath(argc, argv);
    
    length = data_from_file(filepath, indexes, letters, MAX_SIZE);

    char *punteros[length];

    array_copy(letters, sorted, punteros, length);

    sorting(indexes,sorted,length);

    dump_char(sorted, length);

    return EXIT_SUCCESS;
}

