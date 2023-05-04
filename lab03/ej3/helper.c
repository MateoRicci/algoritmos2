#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

void dump_char(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

void dump_int(unsigned int a[], unsigned int length) {
    for (unsigned int j=0u; j < length; j++) {
        printf("%d ", a[j]);
    }
    printf("\n\n");
}


void array_copy(char array[], char array_to_copy[], char* punteros[], unsigned int length){
    for (unsigned int i = 0;i<length;i++){
        punteros[i]=&array_to_copy[i];
        *punteros[i]=array[i];
    }
}

void swap_char(char array[], unsigned int i, unsigned int j){
    char aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

void swap_nums(unsigned int array[], unsigned int i, unsigned int j){
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

void sorting(unsigned int indexes[], char letters[], unsigned int length){
    for(unsigned int i = 1; i<length;i++){
        for(unsigned int j = i;j>0;j--){
            if(indexes[j-1] > indexes[j]){
                swap_nums(indexes,j,j-1);
                swap_char(letters,j,j-1);
            }
        }
        
    }

}