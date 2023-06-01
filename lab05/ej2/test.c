#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(){

    stack s = stack_empty();
    stack_elem e = 10;
    s = stack_push(s,e);

    s = stack_pop(s);
    // si, funciona bien

    s = stack_push(s,e);
    // si, se puede volver a agregar elementos

    printf("%u\n", stack_top(s));

    s = stack_pop(s);

    stack_elem *array = stack_to_array(s);

    printf("%d\n", array[0]);
    // imprime 0 pero devuleve NULL

    

    s = stack_push(s,10);
    s = stack_push(s,20);
    s = stack_push(s,30);
    s = stack_push(s,40);
    s = stack_push(s,50);

    array = stack_to_array(s);


    for(unsigned int i = 0 ; i<stack_size(s);i++){
        printf("%d\n", array[i]);
    }


    s = stack_destroy(s);

    return EXIT_SUCCESS;
}