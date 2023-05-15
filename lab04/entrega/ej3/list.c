#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
//constructor

struct _node{
    list_elem elem;
    struct _node *next;
};


list empty(){
    list l = NULL;
    return l;
}

list addl(list l, list_elem e){
    list new = malloc(sizeof(list));
    new->elem = e;
    new->next = l;
    l = new;
    return l;
}

// destroy

void destroy(list l){
    if(l!=NULL){
        list p,q;
        p = l;
        while(p->next!=NULL){
            q = p;
            p = p->next;
            free(q);
        }
        free(p);
    }    
}

// operations

bool is_empty(list l){
    return(l==NULL);
}

list_elem head(list l){
    assert(!is_empty(l));
    return l->elem;
}

list tail(list l){
    assert(!is_empty(l));
    list p;
    p = l;
    l = l->next;
    free(p);
    return(l);

}

list addr(list l, list_elem elem){
    list p, q = malloc(sizeof(list));
    
    p = l;
    q->elem = elem;
    q->next = NULL;
    if (is_empty(l)){
        l = q;
    }
    else{
        while(p->next!=NULL){
            p=p->next;
        }
        p->next = q;
    }
    return l;
}

unsigned int length(list l){
    unsigned int res = 0;
    list p;
    p=l;
    while(p!=NULL){
        p=p->next;
        res += 1;
    }
    return res;
}

list concat(list l, list l0){
    list p;
    p = l;
    while (p->next!=NULL){
        p=p->next;
    }
    p->next = l0;

    return l;
}

list_elem index(list l, unsigned int n){
    assert(length(l) >= n);
    unsigned int aux = 0;
    list_elem res;
    list p = l;
    while(aux<n){
        p=p->next;
        aux+=1;
    }
    res = p->elem;
    return res;
}

list take(list l, unsigned int n){
    unsigned int i = 0;
    list p = l,q, j=l;
    while(i<n){
        p=p->next;
        i++;
        j=j->next;
    }
    while(p->next!=NULL){
            q = p;
            p = p->next;
            free(q);
    }
    j->next = NULL;
    free(p);
    return l;
}

list drop(list l, unsigned int n){
    unsigned int i = 0;
    list p;
    while(i<n){
        p=l;
        l=l->next;
        free(p);
        i++;
    }
    return l;
}

list copy_list(list l){
    list copy = NULL,p;
    p = l;
    if(is_empty(l)){
        return copy;
    }
    else{
        copy = addr(copy, l->elem);
        p = p->next;
        while(p!=NULL){
            copy = addr(copy,p->elem);
            p = p->next;
        }
        return copy;
    }

}
