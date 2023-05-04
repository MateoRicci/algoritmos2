/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

unsigned int array_from_stdin(int array[], unsigned int max_size) {
    //your code here!!!

    unsigned int size;

    printf("Ingrese el largo del arreglo a completar: \n");

    fscanf(stdin, "%u", &size);

    if (size>max_size){
        printf("ERROR: size over the limit\n");
        exit(EXIT_FAILURE);
    }

    for(unsigned int i = 0;i<size;i++){
        printf("Ingrese un valor para la posicion %d: \n", i);
        fscanf(stdin, "%d", &array[i]);
    }


    return size;
}

unsigned int array_from_stdin2(int array[], unsigned int max_size) {
    //your code here!!!

    unsigned int size;
    int aux = 1;
    unsigned int i= 0;

    while(i<max_size && aux == 1){
        printf("Ingrese un valor para la posicion %d: \n", i);
        aux = fscanf(stdin, "%d", &array[i]);
        size = i;

        i++;
        if (size == max_size){
            printf("Se ha alcanzado el tamano maximo para el arreglo\n");
        }
    }

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


int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    /*Example using CRTL + D*/

    length = array_from_stdin2(array, MAX_SIZE);
    
    array_dump(array, length);

    return EXIT_SUCCESS;
}
