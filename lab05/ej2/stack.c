#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invariante(stack s){
    return (s->size <= s->capacity);
}

stack stack_empty(){
    stack s = NULL;
    s = malloc (sizeof (struct _s_stack));
    s->elems = malloc(sizeof(stack_elem));
    s->size = 0;
    s->capacity = 1;
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(invariante(s));
    if(s->size == s->capacity){
        s->capacity = s->capacity*2;
        s->elems = realloc(s->elems, s->capacity*sizeof(stack_elem));
    }
    s->elems[s->size] = e;
    s->size += 1;

    assert(invariante(s));
    return s;
}

stack stack_pop(stack s){
    assert(invariante(s));
    s->elems[s->size-1] = 0;
    s->size -= 1;
    assert(invariante(s));
    return s;
}

unsigned int stack_size(stack s){
    assert(invariante(s));
    return s->size;
}

stack_elem stack_top(stack s){
    assert(invariante(s));
    return (s != NULL ? s->elems[s->size-1] : 0);
}

bool stack_is_empty(stack s){
    assert(invariante(s));
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s){
    assert(invariante(s));
    stack_elem *s_array = NULL;
    s_array = (stack_elem*)calloc(stack_size(s), sizeof(stack_elem));
    if (!stack_is_empty(s)){
        for (size_t i = 0; i < stack_size(s); i++){
        s_array[i] = s->elems[i];
        }
    }
    assert(invariante(s));
    return s_array;
}

stack stack_destroy(stack s){
    assert(invariante(s));
    free(s->elems);
    s->elems = NULL;
    free(s);
    s = NULL;
    return s;
}