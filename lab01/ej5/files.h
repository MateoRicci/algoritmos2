#ifndef _FILESH
#define _FILESH
#include <stdio.h>
#include <stdlib.h>

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

#endif