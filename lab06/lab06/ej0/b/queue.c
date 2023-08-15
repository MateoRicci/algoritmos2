#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    unsigned int size; //este nos dira el size total de nuestra cola
    struct s_node *first; //Este nos indica el primero de la cola (Esto nos indica que siempre va a haber al menos un elemento)
};

struct s_node {
    queue_elem elem; 
    struct s_node *next; //podemos hacer que apunte el first de next
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL; //Invariante representativa 
}

queue queue_empty(void) {
    queue q=NULL;
    q = malloc(sizeof(struct s_queue)); //Para guardar valores dentro de un puntero a algo, necesitamos primero reservar el espacio 

    q->size = 0; 
    q->first = NULL;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
        
    if (q->first==NULL) {  //q->first -> n1 = NULL
        q->first = new_node; //apunta a el nuevo nodo 
    } else {
        struct s_node *p = q->first;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = new_node;
    }
    q->size++;
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}

unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q->size; 
    return size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;

}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

queue queue_disscard(queue q, unsigned int n){
    
    assert(n < queue_size(q));

    unsigned int contador = 0u;
    struct s_node *ap = q->first;
    
    if (n == 0){
         queue_dequeue(q);
    } else {
        while(contador < n-1){
            ap = ap->next;
            contador++;
        }  

        struct s_node *nodeElim; //creo el nodo para eliminar 
        nodeElim = ap->next; 
        ap->next = nodeElim->next; 
        ap = ap->next;
        destroy_node(nodeElim);
        q->size--;
    }

    return q;
    
}
//PRE: {q --> queue && n < queue_size(q)}
