#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack{
    stack_elem elem;
    struct _s_stack *next;
};

stack stack_empty(){
    stack res = NULL;
    return res;
}

stack stack_push(stack s, stack_elem e){
    stack new = malloc(sizeof(stack));
    new->elem = e;
    new->next = s;
    s = new;
    return s;
}

stack stack_pop(stack s){
    stack p;
    p = s;
    s = s->next;
    free(p);
    return(s);
}

unsigned int stack_size(stack s){
    unsigned int res = 0;
    stack p;
    p = s;
    while(p!=NULL){
        p=p->next;
        res += 1;
    }
    return res;

}

stack_elem stack_top(stack s){
    assert(s!=NULL);
    return s->elem;
}

bool stack_is_empty(stack s){
    return (s==NULL);
}

stack_elem *stack_to_array(stack s){
    stack_elem *res;
    stack p = s;
    unsigned int length = stack_size(s);
    res = (stack_elem*)calloc(length, sizeof(stack_elem));
    for(int i = length-1;i>=0;i--){
        res[i] = p->elem;
        p = p->next;
    }
    
    return res;
}

stack stack_destroy(stack s){
    if(!stack_is_empty(s)){
        stack p,q;
        p = s;
        while(p->next!=NULL){
            q = p;
            p = p->next;
            free(q);
        }
        free(p);
    }  
    return s;  
}