#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    //your code here!!!
    FILE *file = fopen(filepath, "r");

    unsigned int size;

    if (file == NULL){
        printf("ERROR: null file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%u", &size);

    if (size>max_size){
        printf("ERROR: size over the limit\n");
        exit(EXIT_FAILURE);
    }

    unsigned int i = 0;
    while(i<size){
        int aux = fscanf(file, "%d", &array[i]);
        if(aux!=1){
            printf("ERROR: invalid length\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    fclose(file);

    return size;
}
void array_dump(int a[], unsigned int length) {
    //your code here!!!
     
    if (length>0){   
        printf("[");
        for (unsigned int i=0; i<length-1;i++){
            printf(" %d,",a[i]);
        }
        printf(" %d",a[length-1]);
        printf("]\n");
    }
    else{
        printf("[");
        printf("]\n");
    }
}

bool array_is_sorted(int a[], unsigned int length){
    bool res = true;

    if(length>1){
        for(unsigned int i = 0; i<length-1;i++){
            res = res && a[i] <= a[i+1];
        }
    }

    return res;
}